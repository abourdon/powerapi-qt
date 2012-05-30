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
#include "../api/CPUEnergy.h"

CPUEnergy::CPUEnergy() :
		pid(0), watt(0) {
}

CPUEnergy::CPUEnergy(pid_t pid, double watt) :
		pid(pid), watt(watt) {
}

CPUEnergy::CPUEnergy(const CPUEnergy & cpuEnergy) :
		pid(cpuEnergy.pid), watt(cpuEnergy.watt) {
}

CPUEnergy::~CPUEnergy() {
}

bool CPUEnergy::operator ==(const CPUEnergy & cpuEnergy) {
	return pid == cpuEnergy.pid && watt == cpuEnergy.watt;
}

bool CPUEnergy::operator ==(const CPUEnergy * cpuEnergy) {
	return pid == cpuEnergy->pid && watt == cpuEnergy->watt;
}

pid_t CPUEnergy::getPID() const {
	return pid;
}

void CPUEnergy::setPID(pid_t pid) {
	this->pid = pid;
}

double CPUEnergy::getWatt() const {
	return watt;
}

void CPUEnergy::setWatt(double watt) {
	this->watt = watt;
}

double CPUEnergy::getPercentageUsage() const {
	return percentageUsage;
}

void CPUEnergy::setPercentageUsage(double percentageUsage) {
	this->percentageUsage = percentageUsage;
}

