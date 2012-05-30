/*******************************************************************************
 * Copyright (c) 2012 Aurelien Bourdon.
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the GNU Lesser Public License v2.1
 * which accompanies this distribution, and is available at
 * http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
 * 
 * Contributors:
 *     Aurelien Bourdon - initial API and implementation
 ******************************************************************************/
#include <sof/util/logging/LoggerFactory.h>
#include "../api/CPUFormulaService.h"
#include "CPUFormulaComputer.h"

Logger &CPUFormulaComputer::logger(
		LoggerFactory::getLogger("CPUFormulaComputer"));

QHash<int, int> operator-(const QHash<int, int> &toReduce
		, const QHash<int, int> &hash) {
	QHash<int, int> result;
	for (QHash<int, int>::const_iterator toReduceIterator(
			toReduce.constBegin()); toReduceIterator != toReduce.constEnd();
			toReduceIterator++) {
		result.insert(toReduceIterator.key(),
				toReduceIterator.value() - hash.value(toReduceIterator.key()));
	}
	return result;
}

CPUFormulaComputer::CPUFormulaComputer(pid_t pid, int duration,
		CPUSensorService *cpuSensorService) :
		pid(pid), duration(duration), computing(false), cpuSensorService(
				cpuSensorService), cpuNumberOfCores(1) {
	cpuEnergy = new CPUEnergy(pid, duration);
}

CPUFormulaComputer::~CPUFormulaComputer() {
	stopComputation();
	delete cpuEnergy;
}

double CPUFormulaComputer::pidCPUUsage(double pidElapsedTimeBefore,
		double pidElapsedTimeAfter, double elapsedTimeBefore,
		double elapsedTimeAfter) {
	double pidCPUUsage = (pidElapsedTimeAfter - pidElapsedTimeBefore)
			/ ((elapsedTimeAfter - elapsedTimeBefore) / cpuNumberOfCores);

	return qMax(0.0, (qMin(pidCPUUsage, 1.0)));
}

double CPUFormulaComputer::totalPowerConsumed(QHash<int, int> timeInFrequency
		, float tdpMax, float voltageMax, double frequencyMax) {
	// Frequency in MHz
	frequencyMax /= 1000;
	double totalPowerByFrequency = 0;
	double totalTime = 0;
	for (QHash<int, int>::const_iterator timeInFrequencyIterator(
			timeInFrequency.constBegin());
			timeInFrequencyIterator != timeInFrequency.constEnd();
			timeInFrequencyIterator++) {

		QMutexLocker locker(
				CPUFormulaService::cpuFormulaServiceState.getLock());
		if (!CPUFormulaService::cpuFormulaServiceState.isAlive()) {
			logger.log(Logger::LOG_DEBUG,
					"CPU formula service state changed: dummy value returned");
			return -1;
		}
		double voltage = cpuSensorService->getVoltage(
				timeInFrequencyIterator.key());
		locker.unlock();

		// TDP = TDPmax * (f / fmax) * (v / vmax)²
		totalPowerByFrequency += 0.7 * tdpMax
				* (((double) timeInFrequencyIterator.key()) / 1000
						/ frequencyMax)
				* ((voltage / voltageMax) * (voltage / voltageMax))
				* timeInFrequencyIterator.value();
		totalTime += timeInFrequencyIterator.value();

	}
	return totalPowerByFrequency / totalTime / cpuNumberOfCores;
}

void CPUFormulaComputer::startComputation() {
	execution = QtConcurrent::run(this, &CPUFormulaComputer::computeCPUFormula);
}

void CPUFormulaComputer::stopComputation() {
	removeEventListeners();
	execution.cancel();
	execution.waitForFinished();
}

void CPUFormulaComputer::setCPUSensorService(
		CPUSensorService *cpuSensorService) {
	this->cpuSensorService = cpuSensorService;
}

void CPUFormulaComputer::computeCPUFormula() {
	QMutexLocker locker(CPUFormulaService::cpuFormulaServiceState.getLock());
	if (!CPUFormulaService::cpuFormulaServiceState.isAlive()) {
		return;
	}
	cpuNumberOfCores = cpuSensorService->getNumberOfCores();
	float tdpMax = cpuSensorService->getTDPMax();
	float voltageMax = cpuSensorService->getVoltageMax();
	double frequencyMax = cpuSensorService->getFrequencyMax();

	double elapsedTimeBefore = cpuSensorService->getElapsedTimeNow();
	double pidElapsedTimeBefore = cpuSensorService->getElapsedTimeNow(pid);
	QHash<int, int> timeInFrequencyBefore(
			cpuSensorService->getTimeInFrequencyNow());
	locker.unlock();

	forever {
		msleep(duration);

		locker.relock();
		if (!CPUFormulaService::cpuFormulaServiceState.isAlive()) {
			return;
		}
		double elapsedTimeAfter = cpuSensorService->getElapsedTimeNow();
		double pidElapsedTimeAfter = cpuSensorService->getElapsedTimeNow(pid);
		QHash<int, int> timeInFrequencyAfter(
				cpuSensorService->getTimeInFrequencyNow());
		locker.unlock();

		double cpuUsage = pidCPUUsage(pidElapsedTimeBefore, pidElapsedTimeAfter,
				elapsedTimeBefore, elapsedTimeAfter);
		double powerConsumed = totalPowerConsumed(
				timeInFrequencyAfter - timeInFrequencyBefore, tdpMax,
				voltageMax, frequencyMax);
		double pidCPUEnergy = cpuUsage * powerConsumed;

		cpuEnergy->setPercentageUsage(cpuUsage * 100);
		cpuEnergy->setWatt(pidCPUEnergy);

		fireEvent(*cpuEnergy);

		elapsedTimeBefore = elapsedTimeAfter;
		pidElapsedTimeBefore = pidElapsedTimeAfter;
		timeInFrequencyAfter = timeInFrequencyBefore;
	}
}
