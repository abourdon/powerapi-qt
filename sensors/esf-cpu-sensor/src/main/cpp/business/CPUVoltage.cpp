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
#include <QtSql>
#include "CPUVoltage.h"
#include "CPUSpecifications.h"

using sof::util::logging::LoggerFactory;

Logger &CPUVoltage::logger(LoggerFactory::getLogger("CPUVoltage"));

CPUVoltage::CPUVoltage() :
		voltages() {
	QSqlDatabase database(
			ESFDataBase::getInstance()->getNewDatabaseConnection());
	if (!database.open()) {
		ESFDataBase::getInstance()->removeDatabaseConnection(database);
		logger.log(Logger::LOG_ERROR, "unable to open database");
		return;
	}
	QSqlQuery query(database);
	query.prepare("SELECT id FROM Processor WHERE name = :name");
	query.bindValue(":name", CPUSpecifications::getInstance()->getName());
	if (!query.exec() || !query.next()) {
		logger.log(Logger::LOG_ERROR, "unable to get processor id");
		processorId = -1;
	} else {
		processorId = query.value(0).toInt();
	}
	ESFDataBase::getInstance()->removeDatabaseConnection(database);
	database.close();
}

CPUVoltage::~CPUVoltage() {
}

float CPUVoltage::getVoltage(int frequency) {
	if (voltages.contains(frequency)) {
		return voltages.value(frequency);
	}

	QSqlDatabase database(
			ESFDataBase::getInstance()->getNewDatabaseConnection());
	if (!database.open()) {
		ESFDataBase::getInstance()->removeDatabaseConnection(database);
		logger.log(Logger::LOG_ERROR, "unable to open database");
		return -1;
	}
	QSqlQuery query(database);
	query.prepare(
			"SELECT voltage FROM ProcessorVoltage WHERE processor = :processorId AND frequency = :frequency");
	query.bindValue(":processorId", processorId);
	query.bindValue(":frequency", frequency);
	if (!query.exec() || !query.next()) {
		ESFDataBase::getInstance()->removeDatabaseConnection(database);
		logger.log(Logger::LOG_ERROR, "unable to get voltage for frequency %1",
				frequency);
		return -1;
	}
	float voltage(query.value(0).toFloat());
	voltages.insert(frequency, voltage);
	ESFDataBase::getInstance()->removeDatabaseConnection(database);
	database.close();

	return voltage;
}

