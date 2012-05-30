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
#include "../api/NetworkEnergy.h"

NetworkEnergy::NetworkEnergy(pid_t pid, double watt) :
		pid(pid), watt(watt) {
}

NetworkEnergy::NetworkEnergy(const NetworkEnergy & networkEnergy) {
	pid = networkEnergy.pid;
	watt = networkEnergy.watt;
}

NetworkEnergy::~NetworkEnergy() {
}

pid_t NetworkEnergy::getPID() const {
	return pid;
}

double NetworkEnergy::getWatt() const {
	return watt;
}

void NetworkEnergy::setPID(pid_t pid) {
	this->pid = pid;
}

bool NetworkEnergy::operator ==(const NetworkEnergy & networkEnergy) {
	return pid == pid && watt == watt;
}

void NetworkEnergy::setWatt(double watt) {
	this->watt = watt;
}

NetworkInterfaceBytes NetworkEnergy::getErBytes() const {
	return erBytes;
}

void NetworkEnergy::setErBytes(NetworkInterfaceBytes erBytes) {
	this->erBytes = erBytes;
}

