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
#include <sof/util/logging/LoggerFactory.h>
#include "EmittedReceivedBytes.h"

using sof::util::logging::LoggerFactory;

const QString EmittedReceivedBytes::DEFAULT_PROC_STAT_FILE_NAME(
		"/proc/%1/stat");

Logger &EmittedReceivedBytes::logger(
		LoggerFactory::getLogger("EmittedReceivedBytes"));

EmittedReceivedBytes::EmittedReceivedBytes() :
		statFileName(DEFAULT_PROC_STAT_FILE_NAME) {
}

EmittedReceivedBytes::~EmittedReceivedBytes() {
}

QString EmittedReceivedBytes::getStatFileName() const {
	return statFileName;
}

void EmittedReceivedBytes::setStatFileName(const QString & procNetDevFile) {
	this->statFileName = procNetDevFile;
}

NetworkInterfaceBytes EmittedReceivedBytes::getEmittedReceivedNumberOfBytesNow(
		pid_t pid, const NetworkInterface &networkInterface) {
	NetworkInterfaceBytes result(networkInterface.getName());
	QFile statFile(statFileName.arg(pid));
	if (!statFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
		logger.log(Logger::LOG_ERROR, "unable to read stat file");
		return result;
	}

	QTextStream statFileStream(&statFile);

	// Skip the first line
	statFileStream.readLine();

	// TODO get the real received/transmit bytes according to the specified network interface
	// (cause now, we cannot know what interface is used)
	QStringList values(
			statFileStream.readLine().split(QRegExp("\\s+"),
					QString::SkipEmptyParts));

	long emittedBytes = values[5].toLong() + values[9].toLong()
			+ values[12].toLong();
	result.setEmittedBytes(emittedBytes);

	long receivedBytes = values[7].toLong() + values[11].toLong()
			+ values[13].toLong();
	result.setReceivedBytes(receivedBytes);

	return result;
}

