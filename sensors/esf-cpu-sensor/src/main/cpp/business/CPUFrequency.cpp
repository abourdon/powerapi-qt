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
#include "CPUFrequency.h"
#include <sof/util/logging/LoggerFactory.h>
#include "CPUSpecifications.h"

static const QString DEFAULT_TIME_IN_STATE_FILE(
		"/sys/devices/system/cpu/cpu%1/cpufreq/stats/time_in_state");

Logger &CPUFrequency::logger = LoggerFactory::getLogger("CPUFrequency");

CPUFrequency::CPUFrequency() :
		timeInStateFileName(DEFAULT_TIME_IN_STATE_FILE) {
}

CPUFrequency::~CPUFrequency() {
}

QHash<int, int> CPUFrequency::getTimeInFrequencyNow() {
	QHash<int, int> timeInFrequency(getTimeInFrequencyNow(0));

	for (int cpu = 1;
			cpu < CPUSpecifications::getInstance()->getNumberOfCores(); cpu++) {
		addTo(timeInFrequency, getTimeInFrequencyNow(cpu));
	}

	return timeInFrequency;
}

void CPUFrequency::addTo(QHash<int, int> & out, const QHash<int, int> & in) {
	for (QHash<int, int>::const_iterator iterator = in.constBegin();
			iterator != in.constEnd(); iterator++) {
		out[iterator.key()] += iterator.value();
	}
}

QString CPUFrequency::getTimeInStateFileName() const {
	return timeInStateFileName;
}

void CPUFrequency::setTimeInStateFileName(QString timeInStateFileName) {
	this->timeInStateFileName = timeInStateFileName;
}

QHash<int, int> CPUFrequency::getTimeInFrequencyNow(int cpu) {
	QHash<int, int> timeInFrequency;

	QFile timeInFrequencyFile(getTimeInStateFileName().arg(cpu));
	if (!timeInFrequencyFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
		logger.log(Logger::LOG_ERROR,
				"Unable to open time_in_state file for cpu %1", cpu);
		return timeInFrequency;
	}

	QTextStream timeInFrequencyIn(&timeInFrequencyFile);
	QString line;
	while (!(line = timeInFrequencyIn.readLine()).isNull()) {
		QStringList splitLine = line.split(QRegExp("\\s+"));
		timeInFrequency.insert(
				splitLine.first().toInt(),
				splitLine.last().toInt()
						/ CPUSpecifications::getInstance()->getTimeUnit());
	}

	return timeInFrequency;
}

