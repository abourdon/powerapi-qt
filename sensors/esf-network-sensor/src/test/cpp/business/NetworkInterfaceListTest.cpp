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
#include "../../../main/cpp/api/NetworkInterface.h"
#include "NetworkInterfaceListTest.h"

using sof::util::logging::LoggerFactory;

Logger &NetworkInterfaceListTest::logger(
		LoggerFactory::getLogger("NetworkInterfaceListTest"));

NetworkInterfaceListTest::NetworkInterfaceListTest() :
		networkInterfaceList(0) {
}

NetworkInterfaceListTest::~NetworkInterfaceListTest() {
}

void NetworkInterfaceListTest::setUp() {
	networkInterfaceList = new NetworkInterfaceList();
}

void NetworkInterfaceListTest::tearDown() {
	delete networkInterfaceList;
}

void NetworkInterfaceListTest::testGetNetworkInterfaceControllerTypeEthernet() {
	int vendorId = 0x8086;
	int deviceId = 0x10ea;

	TS_ASSERT_EQUALS(
			NetworkInterface::ETHERNET,
			networkInterfaceList->getNetworkInterfaceControllerType(vendorId, deviceId));
}

void NetworkInterfaceListTest::testGetNetworkInterfaceControllerTypeUnknown() {
	int vendorId = 0x0000;
	int deviceId = 0x0000;

	TS_ASSERT_EQUALS(
			NetworkInterface::UNKNOWN,
			networkInterfaceList->getNetworkInterfaceControllerType(vendorId, deviceId));
}

void NetworkInterfaceListTest::testGetNetworkInterfaceControllerNameKnown() {
	int vendorId = 0x8086;
	int deviceId = 0x10ea;

	TS_ASSERT_EQUALS(
			"Intel 82577LM Gigabit LAN Driver",
			networkInterfaceList->getNetworkInterfaceControllerName(vendorId, deviceId).toStdString());
}

void NetworkInterfaceListTest::testGetCurrentNetworkInterfaces() {
	QSet<NetworkInterface *> networkInterfaces(
			networkInterfaceList->getCurrentNetworkInterfaces());
	logger.log(Logger::LOG_DEBUG, "%1 interface(s) found",
			networkInterfaces.size());
	foreach(NetworkInterface *networkInterface, networkInterfaces) {
		logger.log(Logger::LOG_DEBUG,
				"%1 network interface found (model name '%2')",
				networkInterface->getName().toStdString(),
				networkInterface->getModelName().toStdString());
	}
}

void NetworkInterfaceListTest::testGetNetworkInterfaceControllerNameUnknown() {
	int vendorId = 0x0000;
	int deviceId = 0x0000;

	TS_ASSERT_EQUALS(
			"Unknown",
			networkInterfaceList->getNetworkInterfaceControllerName(vendorId, deviceId).toStdString());
}

