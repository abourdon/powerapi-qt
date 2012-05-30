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
#include "NetworkInterfaceList.h"

using sof::util::logging::LoggerFactory;

const QString NetworkInterfaceList::SYS_CLASS_NET_DIRECTORY("/sys/class/net");

Logger &NetworkInterfaceList::logger(
		LoggerFactory::getLogger("NetworkInterfaceList"));

NetworkInterfaceList::NetworkInterfaceList() :
		knownNIC(new QHash<QString, NetworkInterface *>()) {
}

NetworkInterfaceList::~NetworkInterfaceList() {
	foreach (QString key, knownNIC->keys()) {
		delete knownNIC->value(key);
	}
	delete knownNIC;
}

QSet<NetworkInterface *> NetworkInterfaceList::getCurrentNetworkInterfaces() {
	QDir sysClassNetDir(SYS_CLASS_NET_DIRECTORY);
	QFileInfoList interfaces(sysClassNetDir.entryInfoList());

	QSet<NetworkInterface *> result;
	foreach (QFileInfo interface, interfaces) {
		// Vendor part
		QString interfaceVendorFileName(
				interface.absoluteFilePath() + "/device/vendor");
		QFile interfaceVendorFile(interfaceVendorFileName);
		if (!interfaceVendorFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
			logger.log(Logger::LOG_TRACE,
					"unable to find specification file for '%1' interface",
					interface.baseName().toStdString());
			continue;
		}
		QTextStream interfaceVendorStream(&interfaceVendorFile);
		QString vendor(interfaceVendorStream.readLine());
		if (vendor == QString::null) {
			logger.log(Logger::LOG_TRACE,
					"unable to find vendor value for '%1' interface",
					interface.baseName().toStdString());
			continue;
		}

		// Device part
		QString interfaceDeviceFileName(
				interface.absoluteFilePath() + "/device/device");
		QFile interfaceDeviceFile(interfaceDeviceFileName);
		if (!interfaceDeviceFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
			logger.log(Logger::LOG_TRACE,
					"unable to find specification file for '%1' interface",
					interface.baseName().toStdString());
			continue;
		}
		QTextStream interfaceDeviceStream(&interfaceDeviceFile);
		QString device(interfaceDeviceStream.readLine());
		if (device == QString::null) {
			logger.log(Logger::LOG_TRACE,
					"unable to find device value for '%1' interface",
					interface.baseName().toStdString());
			continue;
		}

		bool ok;
		int vendorInt(vendor.toInt(&ok, 16));
		int deviceInt(device.toInt(&ok, 16));
		NetworkInterface *networkInterface = new NetworkInterface(
				interface.baseName());
		networkInterface->setVendorId(vendorInt);
		networkInterface->setDeviceId(deviceInt);
		networkInterface->setType(
				getNetworkInterfaceControllerType(vendorInt, deviceInt));
		networkInterface->setModelName(
				getNetworkInterfaceControllerName(vendorInt, deviceInt));

		// Ethernet support so far
		if (networkInterface->getType() == NetworkInterface::ETHERNET) {
			result.insert(networkInterface);
		}
	}

	return result;
}

NetworkInterface *NetworkInterfaceList::newNIC(int vendorId, int deviceId) {
	QString key(toKnownNICKey(vendorId, deviceId));
	if (knownNIC->contains(key)) {
		logger.log(Logger::LOG_DEBUG,
				"NIC with vendorId '%1' and deviceId '%2' already known ",
				vendorId, deviceId);
		return knownNIC->value(key);
	}

	QSqlDatabase database(
			ESFDataBase::getInstance()->getNewDatabaseConnection());
	if (!database.open()) {
		logger.log(Logger::LOG_ERROR, "unable to open database");
		ESFDataBase::getInstance()->removeDatabaseConnection(database);
		return NULL;
	}
	QSqlQuery query(database);
	query.prepare(
			"SELECT type, name FROM NIC WHERE vendorId = :vendorId AND deviceId = :deviceId");
	query.bindValue(":vendorId", vendorId);
	query.bindValue(":deviceId", deviceId);

	if (!query.exec() || !query.next()) {
		database.close();
		ESFDataBase::getInstance()->removeDatabaseConnection(database);

		logger.log(Logger::LOG_ERROR,
				"No NIC with vendorId '%1' and deviceId '%2' found", vendorId,
				deviceId);
		return NULL;
	}

	QString type(query.value(0).toString());
	QString name(query.value(1).toString());

	database.close();
	ESFDataBase::getInstance()->removeDatabaseConnection(database);

	NetworkInterface *result = new NetworkInterface("n/a");
	result->setModelName(name);
	if (type == "ethernet") {
		result->setType(NetworkInterface::ETHERNET);
	} else if (type == "wireless") {
		result->setType(NetworkInterface::WIRELESS);
	} else {
		result->setType(NetworkInterface::UNKNOWN);
	}
	return result;
}

QString NetworkInterfaceList::toKnownNICKey(int vendorId, int deviceId) {
	return QString("%1%2").arg(QString::number(vendorId)).arg(
			QString::number(deviceId));
}

QString NetworkInterfaceList::getNetworkInterfaceControllerName(int vendorId,
		int deviceId) {
	QString knownNICKey(toKnownNICKey(vendorId, deviceId));
	if (!knownNIC->contains(knownNICKey)) {
		NetworkInterface *result = newNIC(vendorId, deviceId);
		return result == 0 ? "Unknown" : result->getModelName();
	}
	return knownNIC->value(knownNICKey)->getModelName();
}

NetworkInterface::TYPE NetworkInterfaceList::getNetworkInterfaceControllerType(
		int vendorId, int deviceId) {
	QString knownNICKey(toKnownNICKey(vendorId, deviceId));
	if (!knownNIC->contains(knownNICKey)) {
		NetworkInterface *result = newNIC(vendorId, deviceId);
		return result == 0 ? NetworkInterface::UNKNOWN : result->getType();
	}
	return knownNIC->value(knownNICKey)->getType();
}
