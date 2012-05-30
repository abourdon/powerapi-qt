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
#include "ResultStorageTest.h"
#include <esf-cpu-formula/api/CPUEnergy.h>
#include <sof/util/logging/LoggerFactory.h>

ResultStorageTest::ResultStorageTest() :
		resultStorage(0) {
}

ResultStorageTest::~ResultStorageTest() {
}

void ResultStorageTest::setUp() {
	resultStorage = new ResultStorage();
}

void ResultStorageTest::tearDown() {
	delete resultStorage;
}

void ResultStorageTest::testStoreCPUEnergy() {
	CPUEnergy cpuEnergy(1234, 1);
	resultStorage->storeEnergy(cpuEnergy);

	QDir esfLibOutputDir(resultStorage->getEsfLibOutputDir());
	TS_ASSERT(esfLibOutputDir.cd(QString::number(1234)));

	QFile file(esfLibOutputDir.absoluteFilePath("cpu"));
	TS_ASSERT(file.open(QIODevice::ReadOnly | QIODevice::Text));

	QTextStream fileStream(&file);
	TS_ASSERT_EQUALS(1, fileStream.readAll().toDouble());
}

void ResultStorageTest::testStoreNetworkEnergy() {
	NetworkEnergy networkEnergy(1234, 1);
	resultStorage->storeEnergy(networkEnergy);

	QDir esfLibOutputDir(resultStorage->getEsfLibOutputDir());
	TS_ASSERT(esfLibOutputDir.cd(QString::number(1234)));

	QFile file(esfLibOutputDir.absoluteFilePath("network"));
	TS_ASSERT(file.open(QIODevice::ReadOnly | QIODevice::Text));

	QTextStream fileStream(&file);
	TS_ASSERT_EQUALS(1, fileStream.readAll().toDouble());
}
