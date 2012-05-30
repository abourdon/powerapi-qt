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
#include <unistd.h>
#include "CPUSpecificationsTest.h"
#include "../util/TestUtil.h"
#include "../../../main/cpp/business/CPUSpecifications.h"

extern "C" {
extern long int sysconf(int __name) __THROW;
};

//const QString CPUSpecificationsTest::TEST_CPUINFO_FILE();

CPUSpecificationsTest::CPUSpecificationsTest() {
	QDir::setCurrent(TestUtil::getAbsoluteTestingPath());
	CPUSpecifications::getInstance()->setCpuInfoFile("business/cpuinfo");
}

CPUSpecificationsTest::~CPUSpecificationsTest() {
}

void CPUSpecificationsTest::testGetNumberOfCores() {
	TS_ASSERT_EQUALS(sysconf(_SC_NPROCESSORS_ONLN),
			CPUSpecifications::getInstance()->getNumberOfCores());
}

void CPUSpecificationsTest::testGetName() {
	TS_ASSERT_EQUALS("Intel(R) Core(TM) i7 CPU M 640 @ 2.80GHz",
			CPUSpecifications::getInstance()->getName().toStdString());
}
