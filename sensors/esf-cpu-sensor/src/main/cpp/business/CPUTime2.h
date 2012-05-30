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
/**
 * CPU time implementation using the /proc filesystem
 */
#ifndef CPUTIME2_H_
#define CPUTIME2_H_
#include <sof/util/logging/Logger.h>
#include <QtCore>

using sof::util::logging::Logger;

class CPUTime2 {
public:
	static Logger &logger;

	CPUTime2();
	virtual ~CPUTime2();

	double getElapsedTimeNow();
	double getElapsedTimeNow(pid_t pid);

    QString getGlobalCpuStatFile() const;
    void setGlobalCpuStatFile(QString globalCPUStatFile);

    QString getPidCpuStatFile() const;
    void setPidCpuStatFile(QString pidCPUStatFile);

private:
	QString globalCPUStatFile;
	QString pidCPUStatFile;
};

#endif /* CPUTIME2_H_ */
