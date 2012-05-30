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
#include "NetworkSensorServiceImpl.h"

using sof::util::logging::LoggerFactory;

const QString NetworkSensorService::CLASS_NAME("NetworkSensorService");

Logger &NetworkSensorServiceImpl::logger(
		LoggerFactory::getLogger("NetworkSensorServiceImpl"));

NetworkSensorServiceImpl::NetworkSensorServiceImpl() :
		networkInterfaceList(new NetworkInterfaceList()), emittedReceivedBytes(
				new EmittedReceivedBytes()), linkState(new LinkState()) {
}

NetworkSensorServiceImpl::~NetworkSensorServiceImpl() {
	delete networkInterfaceList;
	delete emittedReceivedBytes;
	delete linkState;
}

QSet<NetworkInterface *> NetworkSensorServiceImpl::getCurrentNetworkInterfaces() {
	return networkInterfaceList->getCurrentNetworkInterfaces();
}

NetworkInterfaceBytes NetworkSensorServiceImpl::getEmittedReceivedNumberOfBytesNow(
		pid_t pid, const NetworkInterface & networkInterface) {
	return emittedReceivedBytes->getEmittedReceivedNumberOfBytesNow(pid,
			networkInterface);
}

LinkState::State NetworkSensorServiceImpl::getLinkStateNow(
		const NetworkInterface & networkInterface) {
	return linkState->getCurrentLinkStateNow(networkInterface);
}

float NetworkSensorServiceImpl::getPowerConsumption(
		const NetworkInterface & networkInterface,
		const LinkState::State & state) {
	return linkState->getPowerConsumption(networkInterface, state);
}



