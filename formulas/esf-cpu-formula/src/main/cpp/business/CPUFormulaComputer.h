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
#ifndef CPUFORMULACOMPUTER_H_
#define CPUFORMULACOMPUTER_H_
#include <QtCore>
#include <esf-core/event/EventListenerList.h>
#include <esf-cpu-sensor/api/CPUSensorService.h>
#include <sof/util/logging/Logger.h>
#include "../api/CPUEnergy.h"

using namespace sof::util::logging;

class CPUFormulaComputer: public QThread, public EventListenerList<CPUEnergy> {
Q_OBJECT
public:
	static Logger &logger;

	CPUFormulaComputer(pid_t pid, int duration,
			CPUSensorService *cpuSensorService);
	virtual ~CPUFormulaComputer();

	void setCPUSensorService(CPUSensorService *cpuSensorService);

	void startComputation();
	void stopComputation();
	bool isComputing();
private:
	pid_t pid;
	int duration;
	int cpuNumberOfCores;
	bool computing;
	CPUSensorService *cpuSensorService;

	CPUEnergy *cpuEnergy;
	QFuture<void> execution;

	void computeCPUFormula();

	double pidCPUUsage(double pidElapsedTimeBefore, double pidElapsedTimeAfter,
			double elapsedTimeBefore, double elapsedTimeAfter);
	double totalPowerConsumed(QHash<int, int> timeInFrequency,float tdpMax
			, float voltageMax, double frequencyMax);
};

#endif /* CPUFORMULACOMPUTER_H_ */
