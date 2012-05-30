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
#ifndef CPUFORMULASERVICEIMPL_H_
#define CPUFORMULASERVICEIMPL_H_
#include <sof/util/logging/Logger.h>
#include <esf-core/event/EventListener.h>
#include <esf-cpu-sensor/api/CPUSensorService.h>
#include "../api/CPUFormulaService.h"
#include "../api/CPUEnergy.h"
#include "CPUFormulaComputer.h"

using sof::util::logging::Logger;

class CPUFormulaServiceImpl: public CPUFormulaService, public EventListener<
		CPUEnergy> {
public:
	static Logger &logger;

	CPUFormulaServiceImpl();
	virtual ~CPUFormulaServiceImpl();

	CPUEnergy getCPUEnergy(pid_t pid, int duration);

	void startService();
	void stopService();

	void setCPUSensorService(CPUSensorService *cpuSensorService);

	void eventUpdated(const CPUEnergy &cpuEnergy);
private:
	CPUSensorService *cpuSensorService;

	QHash<pid_t, CPUFormulaComputer *> *computers;
	QHash<pid_t, CPUEnergy *> *results;

	QMutex computersMutex;
	QMutex resultsMutex;
};

#endif /* CPUFORMULASERVICEIMPL_H_ */
