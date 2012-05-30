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
#include <esf-core/collection/CollectionUtil.h>
#include <esf-network-sensor/api/NetworkInterface.h>
#include <esf-network-sensor/api/NetworkInterfaceBytes.h>
#include "NetworkFormulaComputer.h"
#include "../api/NetworkFormulaService.h"

using sof::util::logging::LoggerFactory;

Logger &NetworkFormulaComputer::logger(
		LoggerFactory::getLogger("NetworkFormulaComputer"));

NetworkInterfaceBytes operator-(const NetworkInterfaceBytes &first,
		const NetworkInterfaceBytes &second) {
	return NetworkInterfaceBytes(first.getInterfaceName(),
			first.getEmittedBytes() - second.getEmittedBytes(),
			first.getReceivedBytes() - second.getReceivedBytes());
}

float NetworkFormulaComputer::powerComputation(float basePower, long duration,
		LinkState::State linkState,
		const NetworkInterfaceBytes &networkInterfaceBytes) {
	// First, we have to convert base power according to the current duration
	// (Note that duration unit is ms)
	float realBasePower(basePower * duration / 1000);

	// Next, we have to compute the real consumed power according to the specific link state
	// Note that all active link state unit is Mb/s
	long linkStateRatio = 1;
	switch (linkState) {
	case LinkState::ACTIVE_1000:
		linkStateRatio = 1000000000;
		break;
	case LinkState::ACTIVE_100:
		linkStateRatio = 100000000;
		break;
	case LinkState::ACTIVE_10:
		linkStateRatio = 10000000;
		break;
	}

	return realBasePower * networkInterfaceBytes.getReceivedBytes()
			/ linkStateRatio
			+ networkInterfaceBytes.getEmittedBytes() / linkStateRatio / 2;
}

NetworkFormulaComputer::NetworkFormulaComputer(pid_t pid, long duration,
		NetworkSensorService *networkSensorService) :
		pid(pid), duration(duration), networkSensorService(
				networkSensorService), networkEnergy(NULL), currentNetworkInterfaces(
				NULL) {
	networkEnergy = new NetworkEnergy(pid);
}

NetworkFormulaComputer::~NetworkFormulaComputer() {
	stopComputation();
	delete networkEnergy;

	CollectionUtil::deleteHash(currentNetworkInterfaces);
}

QHash<QString, NetworkInterface *> *NetworkFormulaComputer::getCurrentNetworkInterfaces() {
	if (currentNetworkInterfaces == NULL) {
		QSet<NetworkInterface *> networkInterfaces(
				networkSensorService->getCurrentNetworkInterfaces());
		currentNetworkInterfaces = new QHash<QString, NetworkInterface *>();
		foreach (NetworkInterface *networkInterface, networkInterfaces) {
			currentNetworkInterfaces->insert(networkInterface->getName(),
					networkInterface);
		}
	}
	return currentNetworkInterfaces;
}

void NetworkFormulaComputer::setNetworkSensorService(
		NetworkSensorService *networkSensorService) {
	this->networkSensorService = networkSensorService;
}

void NetworkFormulaComputer::startComputation() {
	execution = QtConcurrent::run(this,
			&NetworkFormulaComputer::computeNetworkFormula);
	logger.log(Logger::LOG_DEBUG, "Computing process started for pid %1: %2",
			QString::number(pid).toStdString(),
			QString::number(execution.isStarted()).toStdString());
}

void NetworkFormulaComputer::stopComputation() {
	removeEventListeners();
	execution.cancel();
	execution.waitForFinished();
}

void NetworkFormulaComputer::computeNetworkFormula() {
	logger.log(Logger::LOG_DEBUG,
			"computeNetworkFormula(%1): 1: stand for locker", pid);
	QMutexLocker locker(
			NetworkFormulaService::networkFormulaServiceState.getLock());
	if (!NetworkFormulaService::networkFormulaServiceState.isAlive()) {
		return;
	}

	// For now, we only compute formula for a single Ethernet interface
	NetworkInterface interface("n/a");
	for (QHash<QString, NetworkInterface *>::const_iterator iterator(
			getCurrentNetworkInterfaces()->constBegin());
			iterator != getCurrentNetworkInterfaces()->constEnd(); iterator++) {
		if (iterator.value()->getType() == NetworkInterface::ETHERNET) {
			interface = *iterator.value();
		}
	}

	NetworkInterfaceBytes oldERBytes(
			networkSensorService->getEmittedReceivedNumberOfBytesNow(pid,
					interface));
	locker.unlock();

	forever {
		msleep(duration);

		logger.log(Logger::LOG_DEBUG,
				"computeNetworkFormula(%1): 2: stand for locker", pid);
		locker.relock();
		if (!NetworkFormulaService::networkFormulaServiceState.isAlive()) {
			return;
		}

		NetworkInterfaceBytes newERBytes(
				networkSensorService->getEmittedReceivedNumberOfBytesNow(pid,
						interface));
		NetworkInterfaceBytes deltaERBytes = newERBytes - oldERBytes;
		LinkState::State state(
				networkSensorService->getLinkStateNow(interface));
		float basePower(
				networkSensorService->getPowerConsumption(interface, state));
		locker.unlock();

		networkEnergy->setWatt(
				powerComputation(basePower, duration, state, deltaERBytes));
		networkEnergy->setErBytes(deltaERBytes);
		fireEvent(*networkEnergy);

		oldERBytes = newERBytes;
	}
}
