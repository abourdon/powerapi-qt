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
#ifndef CPUSENSORSERVICEIMPL_H_
#define CPUSENSORSERVICEIMPL_H_
#include "../api/CPUSensorService.h"
#include "CPUFrequency.h"
#include "CPUTransition.h"
#include "CPUTime2.h"
#include "CPUVoltage.h"

class CPUSensorServiceImpl: public CPUSensorService {
public:
	CPUSensorServiceImpl();
	virtual ~CPUSensorServiceImpl();

	QHash<int, int> getTimeInFrequencyNow();

	double getElapsedTimeNow();

	double getElapsedTimeNow(pid_t pid);

	long getTotalTransitionsNow();

	float getVoltage(int frequency);

	int getFrequencyMax();

	float getVoltageMax();

	float getTDPMax();

	int getNumberOfCores();

private:
	CPUTime2 *cpuTime;
	CPUFrequency *cpuFrequency;
	CPUTransition *cpuTransition;
	CPUVoltage *cpuVoltage;
};

#endif /* CPUSENSORSERVICEIMPL_H_ */
