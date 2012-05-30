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
#include "CPUFormulaServiceImpl.h"

using sof::util::logging::LoggerFactory;

Logger &CPUFormulaServiceImpl::logger(
		LoggerFactory::getLogger("CPUFormulaServiceImpl"));

const QString CPUFormulaService::CLASS_NAME("CPUFormulaService");

ServiceState CPUFormulaService::cpuFormulaServiceState;

CPUFormulaServiceImpl::CPUFormulaServiceImpl() :
		cpuSensorService(0), computersMutex(), resultsMutex() {
	computers = new QHash<pid_t, CPUFormulaComputer *>();
	results = new QHash<pid_t, CPUEnergy *>();
}

CPUFormulaServiceImpl::~CPUFormulaServiceImpl() {
	removeEventListeners();
	stopService();

	foreach(pid_t key, computers->keys()) {
		computers->value(key)->stopComputation();
		delete computers->value(key);
	}
	delete computers;

	foreach(pid_t key, results->keys()) {
		delete results->value(key);
	}
	delete results;
}

void CPUFormulaServiceImpl::startService() {
	QMutexLocker locker(cpuFormulaServiceState.getLock());
	cpuFormulaServiceState.setAlive(true);
	locker.unlock();

	foreach(pid_t key, computers->keys()) {
		computers->value(key)->addEventListener(this);
		computers->value(key)->startComputation();
	}
}

void CPUFormulaServiceImpl::stopService() {
	QMutexLocker locker(cpuFormulaServiceState.getLock());
	cpuFormulaServiceState.setAlive(false);
	locker.unlock();

	foreach(pid_t key, computers->keys()) {
		computers->value(key)->removeEventListener(this);
		computers->value(key)->stopComputation();
	}
}

void CPUFormulaServiceImpl::setCPUSensorService(
		CPUSensorService *cpuSensorService) {
	this->cpuSensorService = cpuSensorService;

	foreach(pid_t key, computers->keys()) {
		computers->value(key)->setCPUSensorService(cpuSensorService);
	}
}

void CPUFormulaServiceImpl::eventUpdated(const CPUEnergy &cpuEnergy) {
	QMutexLocker locker(&resultsMutex);
	if (results->contains(cpuEnergy.getPID())) {
		results->value(cpuEnergy.getPID())->setWatt(cpuEnergy.getWatt());
	} else {
		results->insert(cpuEnergy.getPID(), new CPUEnergy(cpuEnergy));
	}
	locker.unlock();

	fireEvent(cpuEnergy);
}

CPUEnergy CPUFormulaServiceImpl::getCPUEnergy(pid_t pid, int duration) {
	QMutexLocker computersLocker(&computersMutex);
	if (!computers->contains(pid)) {
		logger.log(Logger::LOG_DEBUG, "creating the associated %1 PID computer",
				pid);
		CPUFormulaComputer *computer = new CPUFormulaComputer(pid, duration,
				cpuSensorService);
		computer->addEventListener(this);
		computers->insert(pid, computer);
		computer->startComputation();

		logger.log(Logger::LOG_DEBUG, "active thread count: %1",
				QThreadPool::globalInstance()->activeThreadCount());

		return CPUEnergy(pid, 0.0);
	}
	computersLocker.unlock();

	QMutexLocker resultsLocker(&resultsMutex);
	return *results->value(pid);
}
