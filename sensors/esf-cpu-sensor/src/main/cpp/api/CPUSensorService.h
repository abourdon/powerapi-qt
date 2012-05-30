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
#ifndef CPUSENSORSERVICE_H_
#define CPUSENSORSERVICE_H_
#include <sof/framework/IService.h>
#include <QtCore>
#include <sys/types.h>

using namespace sof::framework;

class CPUSensorService: public IService {
public:
	static const QString CLASS_NAME;

	virtual QHash<int, int> getTimeInFrequencyNow() = 0;

	virtual double getElapsedTimeNow() = 0;

	virtual double getElapsedTimeNow(pid_t pid) = 0;

	virtual long getTotalTransitionsNow() = 0;

	virtual float getVoltage(int frequency) = 0;

	virtual int getFrequencyMax() = 0;

	virtual float getVoltageMax() = 0;

	virtual float getTDPMax() = 0;

	virtual int getNumberOfCores() = 0;
};

#endif /* CPUSENSORSERVICE_H_ */
