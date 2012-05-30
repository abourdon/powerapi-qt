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
#include "DisplayEnergy.h"
#include <sof/util/logging/LoggerFactory.h>
#include <iostream>

const QString DisplayEnergy::DEFAULT_OUTPUT_FILE(
		"/home/abourdon/tmp/esf_output");

Logger &DisplayEnergy::logger(LoggerFactory::getLogger("DisplayEnergy"));

DisplayEnergy::DisplayEnergy() :
		outputFile(DEFAULT_OUTPUT_FILE) {
}

DisplayEnergy::~DisplayEnergy() {
}

void DisplayEnergy::eventUpdated(const CPUEnergy & cpuEnergyComputed) {
	writeEnergy(cpuEnergyComputed);
}

void DisplayEnergy::eventUpdated(const NetworkEnergy & networkEnergyComputed) {
	writeEnergy(networkEnergyComputed);
}

void DisplayEnergy::displayEnergy(const CPUEnergy &energy) {
	QString message("(pid, cpu usage, cpu energy): (%1, %2\%, %3W)\n");
	message = message.arg(energy.getPID(), 10, 10, QChar(' '));
	message = message.arg(energy.getPercentageUsage(), 10, 'g', 5, QChar(' '));
	message = message.arg(energy.getWatt(), 10, 'g', 5, QChar(' '));

	std::cout << message.toStdString();
}

void DisplayEnergy::displayEnergy(const NetworkEnergy & energy) {
	QString message(
			"(pid, emitted bytes, received bytes, network energy): (%1, %2, %3, %4W)\n");
	message = message.arg(energy.getPID(), 10, 10, QChar(' '));
	message = message.arg(energy.getErBytes().getEmittedBytes(), 10, 10,
			QChar(' '));
	message = message.arg(energy.getErBytes().getReceivedBytes(), 10, 10,
			QChar(' '));
	message = message.arg(energy.getWatt(), 10, 'g', 5, QChar(' '));

	std::cout << message.toStdString();
}

void DisplayEnergy::writeEnergy(const CPUEnergy &energy) {
	QFile output(outputFile);
	if (!output.open(QIODevice::Append | QIODevice::Text)) {
		logger.log(Logger::LOG_ERROR, "unable to write into \"%1\" output file",
				outputFile.toStdString());
		return;
	}

	QString message("(pid, cpu usage, cpu energy): (%1, %2\%, %3W)\n");
	message = message.arg(energy.getPID(), 10, 10, QChar(' '));
	message = message.arg(energy.getPercentageUsage(), 10, 'g', 5, QChar(' '));
	message = message.arg(energy.getWatt(), 10, 'g', 5, QChar(' '));

	QTextStream outputStream(&output);
	outputStream << message;
	output.close();
}

void DisplayEnergy::writeEnergy(const NetworkEnergy & energy) {
	QFile output(outputFile);
	if (!output.open(QIODevice::Append | QIODevice::Text)) {
		logger.log(Logger::LOG_ERROR, "unable to write into \"%1\" output file",
				outputFile.toStdString());
		return;
	}

	QString message(
			"(pid, emitted bytes, received bytes, network energy): (%1, %2, %3, %4W)\n");
	message = message.arg(energy.getPID(), 10, 10, QChar(' '));
	message = message.arg(energy.getErBytes().getEmittedBytes(), 10, 10,
			QChar(' '));
	message = message.arg(energy.getErBytes().getReceivedBytes(), 10, 10,
			QChar(' '));
	message = message.arg(energy.getWatt(), 10, 'g', 5, QChar(' '));

	QTextStream outputStream(&output);
	outputStream << message;
	output.close();
}
