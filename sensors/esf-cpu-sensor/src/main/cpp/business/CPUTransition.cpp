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
#include "CPUTransition.h"
#include <sof/util/logging/LoggerFactory.h>
#include "../../../main/cpp/business/CPUSpecifications.h"

Logger &CPUTransition::logger(LoggerFactory::getLogger("CPUTransition"));

static const QString DEFAULT_TOTAL_TRANS_FILE(
		"/sys/devices/system/cpu/cpu%1/cpufreq/stats/total_trans");

CPUTransition::CPUTransition() :
		totalTransFile(DEFAULT_TOTAL_TRANS_FILE) {
}

CPUTransition::~CPUTransition() {
}

QString CPUTransition::getTotalTransFile() const {
	return totalTransFile;
}

long CPUTransition::getTotalTransitionsNow() {
	long totalTransitions = getTotalTransitionsNow(0);
	for (int cpu = 1;
			cpu < CPUSpecifications::getInstance()->getNumberOfCores(); cpu++) {
		totalTransitions += getTotalTransitionsNow(cpu);
	}
	return totalTransitions;
}

void CPUTransition::setTotalTransFile(QString totalTransFile) {
	this->totalTransFile = totalTransFile;
}

long CPUTransition::getTotalTransitionsNow(int cpu) {
	QString totalTransitionsName = QString(getTotalTransFile()).arg(cpu);
	QFile totalTransitionFile(totalTransitionsName);
	if (!totalTransitionFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
		logger.log(Logger::LOG_ERROR,
				"Unable to open trans_table file for cpu #%1", cpu);
		return -1;
	}

	QTextStream totalTransitionIn(&totalTransitionFile);
	return totalTransitionIn.readAll().toLong();
}

