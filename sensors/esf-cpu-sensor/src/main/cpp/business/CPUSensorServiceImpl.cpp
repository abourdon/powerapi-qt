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
#include "CPUSensorServiceImpl.h"
#include "CPUSpecifications.h"

const QString CPUSensorService::CLASS_NAME("CPUSensorService");

CPUSensorServiceImpl::CPUSensorServiceImpl() :
		cpuTime(new CPUTime2()), cpuFrequency(new CPUFrequency()), cpuTransition(
				new CPUTransition()), cpuVoltage(new CPUVoltage()) {
}

CPUSensorServiceImpl::~CPUSensorServiceImpl() {
	delete cpuTime;
	delete cpuFrequency;
	delete cpuTransition;
	delete cpuVoltage;
}

QHash<int, int> CPUSensorServiceImpl::getTimeInFrequencyNow() {
	return cpuFrequency->getTimeInFrequencyNow();
}

double CPUSensorServiceImpl::getElapsedTimeNow() {
	return cpuTime->getElapsedTimeNow();
}

double CPUSensorServiceImpl::getElapsedTimeNow(pid_t pid) {
	return cpuTime->getElapsedTimeNow(pid);
}

long CPUSensorServiceImpl::getTotalTransitionsNow() {
	return cpuTransition->getTotalTransitionsNow();
}

float CPUSensorServiceImpl::getVoltage(int frequency) {
	return cpuVoltage->getVoltage(frequency);
}

int CPUSensorServiceImpl::getFrequencyMax() {
	return CPUSpecifications::getInstance()->getFrequencyMax();
}

float CPUSensorServiceImpl::getVoltageMax() {
	return CPUSpecifications::getInstance()->getVoltageMax();
}

float CPUSensorServiceImpl::getTDPMax() {
	return CPUSpecifications::getInstance()->getTDPMax();
}

int CPUSensorServiceImpl::getNumberOfCores() {
	return CPUSpecifications::getInstance()->getNumberOfCores();
}

