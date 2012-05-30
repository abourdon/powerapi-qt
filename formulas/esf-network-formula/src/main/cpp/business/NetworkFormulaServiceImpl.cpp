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
#include "NetworkFormulaServiceImpl.h"
#include <sof/util/logging/LoggerFactory.h>

using sof::util::logging::LoggerFactory;

const QString NetworkFormulaService::CLASS_NAME("NetworkFormulaService");

ServiceState NetworkFormulaService::networkFormulaServiceState;

Logger &NetworkFormulaServiceImpl::logger(
		LoggerFactory::getLogger("NetworkFormulaServiceImpl"));

NetworkFormulaServiceImpl::NetworkFormulaServiceImpl() :
		networkSensorService(0), computersMutex(), resultsMutex() {
	computers = new QHash<pid_t, NetworkFormulaComputer *>();
	results = new QHash<pid_t, NetworkEnergy *>();
}

NetworkFormulaServiceImpl::~NetworkFormulaServiceImpl() {
	removeEventListeners();
	stopService();

	foreach(pid_t key, computers->keys()) {
		computers->value(key)->stopComputation();
		delete computers->value(key);
	}
	delete computers;

	foreach(pid_t key, results->keys()) {
		delete results->value(key);
	}
	delete results;
}

void NetworkFormulaServiceImpl::startService() {
	logger.log(Logger::LOG_DEBUG, "startService(): stand for locker");
	QMutexLocker locker(networkFormulaServiceState.getLock());
	networkFormulaServiceState.setAlive(true);
	locker.unlock();

	foreach(pid_t key, computers->keys()) {
		computers->value(key)->addEventListener(this);
		computers->value(key)->startComputation();
	}
}

void NetworkFormulaServiceImpl::stopService() {
	logger.log(Logger::LOG_DEBUG, "stopService(): stand for locker");
	QMutexLocker locker(networkFormulaServiceState.getLock());
	networkFormulaServiceState.setAlive(false);
	locker.unlock();

	foreach(pid_t key, computers->keys()) {
		computers->value(key)->removeEventListener(this);
		computers->value(key)->stopComputation();
	}
}

void NetworkFormulaServiceImpl::setNetworkSensorService(
		NetworkSensorService *networkSensorService) {
	this->networkSensorService = networkSensorService;

	foreach(pid_t key, computers->keys()) {
		computers->value(key)->setNetworkSensorService(networkSensorService);
	}
}

void NetworkFormulaServiceImpl::eventUpdated(
		const NetworkEnergy & networkEnergy) {
	QMutexLocker locker(&resultsMutex);
	if (results->contains(networkEnergy.getPID())) {
		results->value(networkEnergy.getPID())->setWatt(
				networkEnergy.getWatt());
	} else {
		results->insert(networkEnergy.getPID(),
				new NetworkEnergy(networkEnergy));
	}
	locker.unlock();

	fireEvent(networkEnergy);
}

NetworkEnergy NetworkFormulaServiceImpl::getNetworkEnergy(pid_t pid,
		long duration) {
	QMutexLocker computersLocker(&computersMutex);
	if (!computers->contains(pid)) {
		logger.log(Logger::LOG_DEBUG, "New computer for pid %1", pid);
		NetworkFormulaComputer *computer = new NetworkFormulaComputer(pid,
				duration, networkSensorService);
		computer->addEventListener(this);
		computers->insert(pid, computer);
		computer->startComputation();
		return NetworkEnergy(pid, 0.0);
	}
	computersLocker.unlock();

	QMutexLocker resultsLocker(&resultsMutex);
	return *results->value(pid);
}
