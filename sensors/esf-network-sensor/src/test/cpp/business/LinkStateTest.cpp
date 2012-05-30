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
#include "LinkStateTest.h"
#include "../../../main/cpp/api/NetworkInterface.h"

using sof::util::logging::LoggerFactory;

Logger &LinkStateTest::logger(LoggerFactory::getLogger("LinkStateTest"));

LinkStateTest::LinkStateTest() :
		linkState(0) {
}

LinkStateTest::~LinkStateTest() {
}

void LinkStateTest::setUp() {
	linkState = new LinkState();
}

void LinkStateTest::tearDown() {
	delete linkState;
}

void LinkStateTest::testGetCurrentLinkStateNow() {
	NetworkInterface networkInterface("eth0");
	logger.log(
			Logger::LOG_DEBUG,
			"current link state now for interface %1: %2",
			networkInterface.getName().toStdString(),
			LinkState::toString(
					linkState->getCurrentLinkStateNow(networkInterface)).toStdString());
}

void LinkStateTest::testGetCurrentLinkStateNowWithUnknownInterface() {
	NetworkInterface networkInterface("eth0!");
	logger.log(
			Logger::LOG_DEBUG,
			"current link state now for interface %1: %2",
			networkInterface.getName().toStdString(),
			LinkState::toString(
					linkState->getCurrentLinkStateNow(networkInterface)).toStdString());
}

void LinkStateTest::testGetPowerConsumption() {
	NetworkInterface networkInterface("n/a");
	networkInterface.setVendorId(32902);
	networkInterface.setDeviceId(4330);

	LinkState::State state(LinkState::ACTIVE_1000);

	TS_ASSERT_EQUALS(0.627f,
			linkState->getPowerConsumption(networkInterface, state));
}

void LinkStateTest::testGetPowerConsumptionWithUnknownInterface() {
	NetworkInterface networkInterface("n/a");
	networkInterface.setVendorId(0);
	networkInterface.setDeviceId(0);

	LinkState::State state(LinkState::ACTIVE_1000);

	TS_ASSERT_EQUALS(-1,
			linkState->getPowerConsumption(networkInterface, state));
}

void LinkStateTest::testGetPowerConsumptionWithUnknownLinkState() {
	NetworkInterface networkInterface("n/a");
	networkInterface.setVendorId(32902);
	networkInterface.setDeviceId(4330);

	LinkState::State state(LinkState::UNKNOWN);

	TS_ASSERT_EQUALS(-1,
			linkState->getPowerConsumption(networkInterface, state));
}

