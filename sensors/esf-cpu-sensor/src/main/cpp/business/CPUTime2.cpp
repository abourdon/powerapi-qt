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
#include "CPUTime2.h"
#include <sof/util/logging/LoggerFactory.h>

using sof::util::logging::LoggerFactory;

static const QString DEFAULT_GLOBAL_CPU_STAT_FILE("/proc/stat");
static const QString DEFAULT_PID_CPU_STAT_FILE("/proc/%1/stat");

Logger &CPUTime2::logger = LoggerFactory::getLogger("CPUTime2");

CPUTime2::CPUTime2() :
		globalCPUStatFile(DEFAULT_GLOBAL_CPU_STAT_FILE), pidCPUStatFile(
				DEFAULT_PID_CPU_STAT_FILE) {
}

CPUTime2::~CPUTime2() {
}

QString CPUTime2::getGlobalCpuStatFile() const {
	return globalCPUStatFile;
}

QString CPUTime2::getPidCpuStatFile() const {
	return pidCPUStatFile;
}

void CPUTime2::setGlobalCpuStatFile(QString globalCPUStatFile) {
	this->globalCPUStatFile = globalCPUStatFile;
}

double CPUTime2::getElapsedTimeNow() {
	double elapsedTimeNow = 0.0;

	QFile cpuStatFile(getGlobalCpuStatFile());
	if (!cpuStatFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
		logger.log(Logger::LOG_ERROR, "Unable to open global cpu stat file");
		return elapsedTimeNow;
	}

	QTextStream cpuStateStream(&cpuStatFile);
	QString cpuStateLine = cpuStateStream.readLine();
	if (cpuStateLine.isNull() || !cpuStateLine.startsWith("cpu")) {
		logger.log(Logger::LOG_ERROR, "Unable to read global cpu stat file");
		return elapsedTimeNow;
	}
	QStringList items = cpuStateLine.split(QRegExp("\\s+"));
	foreach (const QString &item, items) {
		bool ok = false;
		long itemTime(item.toLong(&ok));
		if (ok) {
			elapsedTimeNow += itemTime;
		}
	}

	return elapsedTimeNow;
}

double CPUTime2::getElapsedTimeNow(pid_t pid) {
	double elapsedTimeNow = 0.0;

	QFile cpuStatFile(getPidCpuStatFile().arg(pid));
	if (!cpuStatFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
		logger.log(Logger::LOG_ERROR, "Unable to open cpu stat file for pid %1",
				pid);
		return elapsedTimeNow;
	}

	QTextStream cpuStateStream(&cpuStatFile);
	QString cpuStateLine = cpuStateStream.readLine();
	if (cpuStateLine.isNull()) {
		logger.log(Logger::LOG_ERROR, "Unable to read cpu stat file for pid %1",
				pid);
		return elapsedTimeNow;
	}

	QStringList items = cpuStateLine.split(QRegExp("\\s+"));
	// User time
	elapsedTimeNow += items[13].toLong();
	// System time
	elapsedTimeNow += items[14].toLong();
	// Block IO waiting time
	elapsedTimeNow += items[41].toLong();

	return elapsedTimeNow;
}

void CPUTime2::setPidCpuStatFile(QString pidCPUStatFile) {
	this->pidCPUStatFile = pidCPUStatFile;
}
