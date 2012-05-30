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
#include "../api/LinkState.h"

using sof::util::logging::LoggerFactory;

const QString LinkState::ACTIVE_1000_STR("1000Mbs active");
const QString LinkState::ACTIVE_100_STR("100Mbs active");
const QString LinkState::ACTIVE_10_STR("10Mbs active");
const QString LinkState::IDLE_1000_STR("1000Mbs idle");
const QString LinkState::IDLE_100_STR("100Mbs idle");
const QString LinkState::IDLE_10_STR("10Mbs idle");
const QString LinkState::DISCONNECTED_CABLE_STR("Disconnected cable");
const QString LinkState::DISCONNECTED_LAN_STR("Disconnected LAN");
const QString LinkState::UNKNOWN_STR("Unknown");

const QString LinkState::SYS_CLASS_INTERFACE_DIRECTORY("/sys/class/net/%1");

Logger &LinkState::logger(LoggerFactory::getLogger("LinkState"));

QString LinkState::toString(State state) {
	switch (state) {
	case ACTIVE_1000:
		return ACTIVE_1000_STR;
	case ACTIVE_100:
		return ACTIVE_100_STR;
	case ACTIVE_10:
		return ACTIVE_10_STR;
	case IDLE_1000:
		return IDLE_1000_STR;
	case IDLE_100:
		return IDLE_100_STR;
	case IDLE_10:
		return IDLE_10_STR;
	case DISCONNECTED_CABLE:
		return DISCONNECTED_CABLE_STR;
	case DISCONNECTED_LAN:
		return DISCONNECTED_LAN_STR;
	default:
		return QString::null;
	}
}

LinkState::LinkState() {
}

LinkState::~LinkState() {
}

LinkState::State LinkState::getCurrentLinkStateNow(
		const NetworkInterface & networkInterface) {
	QDir sysClassInterfaceDir(
			SYS_CLASS_INTERFACE_DIRECTORY.arg(networkInterface.getName()));
	QFileInfoList sysClassInterfaceDirEntries(
			sysClassInterfaceDir.entryInfoList());
	if (sysClassInterfaceDirEntries.isEmpty()) {
		logger.log(Logger::LOG_ERROR,
				"unable to read sys class interface directory (%1)",
				sysClassInterfaceDir.path().toStdString());
		return UNKNOWN;
	}

	QString operstate(getCurrentOperstateNow(sysClassInterfaceDir));
	if (operstate.isNull() || (operstate != "up" && operstate != "down")) {
		logger.log(Logger::LOG_ERROR,
				"unable to determine operstate for interface '%1'",
				networkInterface.getName().toStdString());
		return UNKNOWN;
	}
	if (operstate == "down") {
		return DISCONNECTED_CABLE;
	}

	switch (getCurrentSpeedNow(sysClassInterfaceDir)) {
	case 1000:
		return ACTIVE_1000;
	case 100:
		return ACTIVE_100;
	case 10:
		return ACTIVE_10;
	case -1:
	default:
		return UNKNOWN;
	}
}

QString LinkState::getCurrentOperstateNow(const QDir &sysClassInterfaceDir) {
	QString operstateFileName(sysClassInterfaceDir.filePath("operstate"));
	QFile operstateFile(operstateFileName);
	if (!operstateFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
		return QString::null;
	}

	QTextStream operstateFileStream(&operstateFile);
	return operstateFileStream.readAll().trimmed();
}

int LinkState::getCurrentSpeedNow(const QDir &sysClassInterfaceDir) {
	QString speedFileName(sysClassInterfaceDir.filePath("speed"));
	QFile speedFile(speedFileName);
	if (!speedFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
		return -1;
	}

	QTextStream speedFileStream(&speedFile);
	return speedFileStream.readAll().trimmed().toInt();
}

float LinkState::getPowerConsumption(const NetworkInterface & networkInterface,
		const LinkState::State & state) {
	QSqlDatabase database(
			ESFDataBase::getInstance()->getNewDatabaseConnection());

	// First step, get database NIC's id
	if (!database.open()) {
		logger.log(Logger::LOG_ERROR, "unable to open database");
		return -1;
	}
	QSqlQuery query(database);
	query.prepare(
			"SELECT id FROM NIC WHERE vendorId = :vendorId AND deviceId = :deviceId");
	query.bindValue(":vendorId", networkInterface.getVendorId());
	query.bindValue(":deviceId", networkInterface.getDeviceId());
	if (!query.exec() || !query.next()) {
		database.close();
		ESFDataBase::getInstance()->removeDatabaseConnection(database);
		logger.log(Logger::LOG_ERROR,
				"No NIC with vendorId '%1' and deviceId '%2' found",
				networkInterface.getVendorId(), networkInterface.getDeviceId());
		return -1;
	}
	int nicId(query.value(0).toInt());

	// Next, get powerConsumption relatively to the link state
	query.clear();
	query.prepare(
			"SELECT powerConsumption FROM NICPower WHERE nicId = :nicId AND linkState = :linkState");
	query.bindValue(":nicId", nicId);
	query.bindValue(":linkState", LinkState::toString(state));
	if (!query.exec() || !query.next()) {
		database.close();
		ESFDataBase::getInstance()->removeDatabaseConnection(database);
		logger.log(Logger::LOG_ERROR,
				"No power consumption for nicId '%1' and linkState '%2' found",
				QString::number(nicId).toStdString(),
				LinkState::toString(state).toStdString());
		return -1;
	}
	float powerConsumption(query.value(0).toFloat());

	database.close();
	ESFDataBase::getInstance()->removeDatabaseConnection(database);

	return powerConsumption;
}

