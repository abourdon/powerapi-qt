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
#include "CPUTime.h"
#include <sof/util/logging/LoggerFactory.h>
#include <QtCore>

const QString CPUTime::DEFAULT_CGROUP_REPOSITORY("/sys/fs/cgroup");

Logger &CPUTime::logger(LoggerFactory::getLogger("CPUTime2"));

CPUTime::CPUTime() :
		cgroupRepository(DEFAULT_CGROUP_REPOSITORY) {
	setCgroupRepository(DEFAULT_CGROUP_REPOSITORY);
}

CPUTime::~CPUTime() {
}

double CPUTime::getElapsedTimeNow() {
	QFile cpuacctUsageFile(getCgroupRepository().append("/cpuacct.usage"));
	if (!cpuacctUsageFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
		logger.log(Logger::LOG_ERROR,
				"unable to find cpuacct.usage cgroup file");
		return 0.0;
	}
	QTextStream cpuacctUsageStream(&cpuacctUsageFile);
	return cpuacctUsageStream.readLine().toDouble();
}

QString CPUTime::getCgroupRepository() const {
	return cgroupRepository.path();
}

void CPUTime::setCgroupRepository(QString cgroupRepository) {
	QDir newCGroupRepository(cgroupRepository);
	if (!newCGroupRepository.exists()) {
		logger.log(Logger::LOG_ERROR, "\"%1\" is not a valid cgroup repository",
				cgroupRepository.toStdString());
		return;
	}
	if (!newCGroupRepository.exists("cpuacct.usage")) {
		logger.log(
				Logger::LOG_ERROR,
				"cannot find cpu resources. Please make sure that cgroup repository is mounted with cpu and cpuacct options");
		return;
	}
	this->cgroupRepository.setPath(cgroupRepository);
}

double CPUTime::getElapsedTimeNow(pid_t pid) {
	QString pidStr(QString::number(pid));
	if (!cgroupRepository.exists(pidStr)) {
		cgroupRepository.mkdir(pidStr);
		QDir pidDir(cgroupRepository.filePath(pidStr));
		QFile taskFile(pidDir.filePath("tasks"));
		if (!taskFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
			logger.log(Logger::LOG_ERROR,
					"unable to open tasks cgroup file for pid %1", pid);
		}
		QTextStream taskStream(&taskFile);
		taskStream << pidStr << "\n";
		taskFile.close();
		return 0.0;
	}
	QDir pidCGroupcpuacctUsageDir(cgroupRepository.filePath(pidStr));
	QFile pidCGroupcpuacctUsageFile(
			pidCGroupcpuacctUsageDir.filePath("cpuacct.usage"));
	if (!pidCGroupcpuacctUsageFile.open(
			QIODevice::ReadOnly | QIODevice::Text)) {
		logger.log(Logger::LOG_ERROR,
				"unable to find cpuacct.usage cgroup file for pid %1", pid);
		logger.log(Logger::LOG_ERROR, "(using \"%1\" file)",
				pidCGroupcpuacctUsageFile.fileName().toStdString());
		return 0.0;
	}

	QTextStream pidCGroupcpuacctUsageStream(&pidCGroupcpuacctUsageFile);
	return pidCGroupcpuacctUsageStream.readLine().toDouble();
}

