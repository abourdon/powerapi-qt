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
#include "../api/NetworkInterface.h"

uint qHash(const NetworkInterface &networkInterface) {
	return qHash(networkInterface.getName());
}

NetworkInterface::NetworkInterface(QString name) :
		name(name) {
}

NetworkInterface::~NetworkInterface() {
}

bool NetworkInterface::operator ==(
		const NetworkInterface & networkInterface) const {
	return name == networkInterface.name;
}

QString NetworkInterface::getModelName() const {
	return modelName;
}

QString NetworkInterface::getName() const {
	return name;
}

void NetworkInterface::setModelName(QString modelName) {
	this->modelName = modelName;
}

NetworkInterface::TYPE NetworkInterface::getType() const {
	return type;
}

void NetworkInterface::setType(NetworkInterface::TYPE type) {
	this->type = type;
}

int NetworkInterface::getDeviceId() const {
	return deviceId;
}

int NetworkInterface::getVendorId() const {
	return vendorId;
}

void NetworkInterface::setDeviceId(int deviceId) {
	this->deviceId = deviceId;
}

void NetworkInterface::setVendorId(int vendorId) {
	this->vendorId = vendorId;
}

