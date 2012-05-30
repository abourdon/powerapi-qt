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
#ifndef CPUVOLTAGE_H_
#define CPUVOLTAGE_H_
#include <sof/util/logging/Logger.h>
#include <QtCore>
#include <QtSql>

using sof::util::logging::Logger;

class CPUVoltage {
public:
	static Logger &logger;

	CPUVoltage();
	virtual ~CPUVoltage();

	float getVoltage(int frequency);

private:
	QHash<int, float> voltages;
	int processorId;
};

#endif /* CPUVOLTAGE_H_ */
