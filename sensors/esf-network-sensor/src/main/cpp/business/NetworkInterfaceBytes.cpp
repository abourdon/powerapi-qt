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
#include "../api/NetworkInterfaceBytes.h"

uint qHash(const NetworkInterfaceBytes &key) {
	return qHash(key.getInterfaceName());
}

NetworkInterfaceBytes::NetworkInterfaceBytes(QString interfaceName,
		long emittedBytes, long receivedBytes) :
		interfaceName(interfaceName), emittedBytes(emittedBytes), receivedBytes(
				receivedBytes) {
}

NetworkInterfaceBytes::NetworkInterfaceBytes(
		const NetworkInterfaceBytes & networkInterfaceBytes) :
		interfaceName(networkInterfaceBytes.interfaceName), emittedBytes(
				networkInterfaceBytes.emittedBytes), receivedBytes(
				networkInterfaceBytes.receivedBytes) {
}

NetworkInterfaceBytes::~NetworkInterfaceBytes() {
}

long NetworkInterfaceBytes::getEmittedBytes() const {
	return emittedBytes;
}

QString NetworkInterfaceBytes::getInterfaceName() const {
	return interfaceName;
}

long NetworkInterfaceBytes::getReceivedBytes() const {
	return receivedBytes;
}

void NetworkInterfaceBytes::setEmittedBytes(long emittedBytes) {
	this->emittedBytes = emittedBytes;
}

void NetworkInterfaceBytes::setInterfaceName(QString interfaceName) {
	this->interfaceName = interfaceName;
}

bool NetworkInterfaceBytes::operator ==(
		const NetworkInterfaceBytes & networkInterfaceBytes) {
	return interfaceName == interfaceName;
}

void NetworkInterfaceBytes::setReceivedBytes(long receivedBytes) {
	this->receivedBytes = receivedBytes;
}

