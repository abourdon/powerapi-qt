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
#include "../util/TestUtil.h"
#include "EmittedReceivedBytesTest.h"

const QString EmittedReceivedBytesTest::TEST_PROC_STAT_FILE_NAME(
		"business/stat_%1");

EmittedReceivedBytesTest::EmittedReceivedBytesTest() :
		emittedReceivedBytes(0) {
	QDir::setCurrent(TestUtil::getAbsoluteTestingPath());
}

EmittedReceivedBytesTest::~EmittedReceivedBytesTest() {
}

void EmittedReceivedBytesTest::setUp() {
	emittedReceivedBytes = new EmittedReceivedBytes();
	emittedReceivedBytes->setStatFileName(TEST_PROC_STAT_FILE_NAME);
}

void EmittedReceivedBytesTest::tearDown() {
	delete emittedReceivedBytes;
}

void EmittedReceivedBytesTest::testGetEmittedReceivedNumberOfBytesNow() {
	NetworkInterface networkInterface("eth0");
	NetworkInterfaceBytes networkInterfaceBytes(
			emittedReceivedBytes->getEmittedReceivedNumberOfBytesNow(0,
					networkInterface));

	TS_ASSERT_EQUALS(0 + 0 + 0, networkInterfaceBytes.getEmittedBytes());
	TS_ASSERT_EQUALS(96242590 + 31529 + 0,
			networkInterfaceBytes.getReceivedBytes());
}

void EmittedReceivedBytesTest::testGetEmittedReceivedNumberOfBytesNowWrongFileName() {
	emittedReceivedBytes->setStatFileName("wrong_file_%1");
	NetworkInterface networkInterface("eth0");
	NetworkInterfaceBytes networkInterfaceBytes(
			emittedReceivedBytes->getEmittedReceivedNumberOfBytesNow(0,
					networkInterface));

	TS_ASSERT_EQUALS(0, networkInterfaceBytes.getEmittedBytes());
	TS_ASSERT_EQUALS(0, networkInterfaceBytes.getReceivedBytes());
}

