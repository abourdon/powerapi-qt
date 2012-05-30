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
#ifndef CPUSPECIFICATIONS_H_
#define CPUSPECIFICATIONS_H_
#include <sof/util/logging/Logger.h>
#include <QtCore>
#include <QtSql>

using sof::util::logging::Logger;

class CPUSpecifications {
public:
	static Logger &logger;

	static const QString DEFAULT_CPUINFO_FILE;

	static CPUSpecifications *getInstance();

	QString getCpuInfoFile() const;
	void setCpuInfoFile(QString cpuInfoFile);

	QString getName();

	int getNumberOfCores();

	int getTimeUnit();

	int getFrequencyMax();

	float getVoltageMax();

	float getTDPMax();

private:
	static CPUSpecifications *instance;

	CPUSpecifications();
	virtual ~CPUSpecifications();

	QString cpuInfoFile;
	QString name;
	int numberOfCores;
	int timeUnit;
	long frequencyMax;
	float voltageMax;
	float tdpMax;
};

#endif /* CPUSPECIFICATIONS_H_ */
