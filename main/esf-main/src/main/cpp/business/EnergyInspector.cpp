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
#include "EnergyInspector.h"

QMutex EnergyInspector::pidsMutext;
QList<int> EnergyInspector::pids;

EnergyInspector::EnergyInspector() {
}

EnergyInspector::~EnergyInspector() {
}

QList<int> EnergyInspector::getPids() {
	QMutexLocker locker(&pidsMutext);
	pids.clear();
	if (pids.isEmpty()) {
		QDir procDir("/proc");
		QStringList filters;
		filters << "[0-9]*";
		foreach(QFileInfo pidDir, procDir.entryInfoList(filters,
						QDir::Dirs | QDir::NoDotAndDotDot)) {
			pids += pidDir.baseName().toInt();
		}
	}
	return pids;
}

void EnergyInspector::setCPUFormulaService(
		CPUFormulaService *cpuFormulaService) {
	this->cpuFormulaService = cpuFormulaService;
}

void EnergyInspector::setNetworkFormulaService(
		NetworkFormulaService *networkFormulaService) {
	this->networkFormulaService = networkFormulaService;
}

void EnergyInspector::inspectCPU() {
	cpuFormulaService->getCPUEnergy(11767, 200);
}

void EnergyInspector::inspectNetwork() {
	networkFormulaService->getNetworkEnergy(11767, 200);
}

/*
 void EnergyInspector::inspectCPU() {
 while (true) {
 foreach(int pid, getPids()) {
 cpuFormulaService->getCPUEnergy(pid, 100);
 }

 msleep(2000);
 }
 }

 void EnergyInspector::inspectNetwork() {
 while (true) {
 foreach(int pid, getPids()) {
 networkFormulaService->getNetworkEnergy(pid, 100);
 }

 msleep(2000);
 }
 }
 */
