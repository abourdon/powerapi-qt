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
#include <esf-core/db/ESFDataBase.h>
#include <unistd.h>
#include <QtSql>
#include "CPUSpecifications.h"

using sof::util::logging::LoggerFactory;

Logger &CPUSpecifications::logger(
		LoggerFactory::getLogger("CPUSpecifications"));

extern "C" {
extern long int sysconf(int __name) __THROW;
}

const QString CPUSpecifications::DEFAULT_CPUINFO_FILE("/proc/cpuinfo");

CPUSpecifications *CPUSpecifications::instance(0);

CPUSpecifications *CPUSpecifications::getInstance() {
	if (instance == 0) {
		instance = new CPUSpecifications();
	}
	return instance;
}

CPUSpecifications::CPUSpecifications() :
		cpuInfoFile(DEFAULT_CPUINFO_FILE), numberOfCores(
				sysconf(_SC_NPROCESSORS_ONLN)), timeUnit(10), frequencyMax(-1), voltageMax(
				-1), tdpMax(-1) {
}

CPUSpecifications::~CPUSpecifications() {
}

int CPUSpecifications::getNumberOfCores() {
	return numberOfCores;
}

int CPUSpecifications::getTimeUnit() {
	return timeUnit;
}

int CPUSpecifications::getFrequencyMax() {
	if (frequencyMax == -1) {
		QSqlDatabase database(
				ESFDataBase::getInstance()->getNewDatabaseConnection());
		if (!database.open()) {
			ESFDataBase::getInstance()->removeDatabaseConnection(database);
			logger.log(Logger::LOG_ERROR, "unable to open database");
			return -1;
		}
		QSqlQuery query(database);
		query.prepare(
				"SELECT frequencyMax FROM Processor WHERE name LIKE :name");
		query.bindValue(":name", getName());
		if (!query.exec() || !query.next()) {
			database.close();
			ESFDataBase::getInstance()->removeDatabaseConnection(database);
			logger.log(Logger::LOG_ERROR,
					"unable to get max frequency for CPU name %1",
					getName().toStdString());
			return -1;
		}
		frequencyMax = query.value(0).toInt();
		database.close();
		ESFDataBase::getInstance()->removeDatabaseConnection(database);
	}
	return frequencyMax;
}

QString CPUSpecifications::getName() {
	if (name.isEmpty()) {
		logger.log(Logger::LOG_DEBUG, cpuInfoFile.toStdString());
		QFile cpuInfo(cpuInfoFile);
		if (!cpuInfo.open(QIODevice::ReadOnly | QIODevice::Text)) {
			logger.log(Logger::LOG_ERROR, "unable to read cpuinfo file");
			return "";
		}

		QTextStream cpuInfoStream(&cpuInfo);
		QString line;
		do {
			line = cpuInfoStream.readLine();
			if (line.startsWith("model name")) {
				break;
			}
		} while (!line.isEmpty());

		if (!line.startsWith("model name")) {
			logger.log(Logger::LOG_ERROR,
					"corrupt cpuinfo file: unable to get processor model name");
			return "";
		}

		line = line.simplified();
		QStringList lines = line.split(':');
		if (lines.size() != 2) {
			logger.log(
					Logger::LOG_ERROR,
					"corrupt cpuinfo file model name line: unable to get processor model name");
		}
		name = lines[1].simplified();
	}
	return name;
}

QString CPUSpecifications::getCpuInfoFile() const {
	return cpuInfoFile;
}

void CPUSpecifications::setCpuInfoFile(QString cpuInfoFile) {
	this->cpuInfoFile = cpuInfoFile;
}

float CPUSpecifications::getVoltageMax() {
	if (voltageMax == -1) {
		QSqlDatabase database(
				ESFDataBase::getInstance()->getNewDatabaseConnection());
		if (!database.open()) {
			ESFDataBase::getInstance()->removeDatabaseConnection(database);
			logger.log(Logger::LOG_ERROR, "unable to open database");
			return -1;
		}
		QSqlQuery query(database);
		query.prepare("SELECT voltageMax FROM Processor WHERE name LIKE :name");
		query.bindValue(":name", getName());
		if (!query.exec() || !query.next()) {
			database.close();
			ESFDataBase::getInstance()->removeDatabaseConnection(database);
			logger.log(Logger::LOG_ERROR,
					"unable to get max voltage for CPU name %1",
					getName().toStdString());
			return -1;
		}
		voltageMax = query.value(0).toFloat();
		ESFDataBase::getInstance()->removeDatabaseConnection(database);
		database.close();
	}
	return voltageMax;
}

float CPUSpecifications::getTDPMax() {
	if (tdpMax == -1) {
		QSqlDatabase database(
				ESFDataBase::getInstance()->getNewDatabaseConnection());
		if (!database.open()) {
			ESFDataBase::getInstance()->removeDatabaseConnection(database);
			logger.log(Logger::LOG_ERROR, "unable to open database");
			return -1;
		}
		QSqlQuery query(database);
		query.prepare("SELECT tdpMax FROM Processor WHERE name LIKE :name");
		query.bindValue(":name", getName());
		if (!query.exec() || !query.next()) {
			ESFDataBase::getInstance()->removeDatabaseConnection(database);
			database.close();
			logger.log(Logger::LOG_ERROR,
					"unable to get max TDP for CPU name %1",
					getName().toStdString());
			return -1;
		}
		tdpMax = query.value(0).toFloat();
		ESFDataBase::getInstance()->removeDatabaseConnection(database);
		database.close();

	}
	return tdpMax;
}
