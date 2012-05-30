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
#include "CPUFrequencyTest.h"
#include "../util/TestUtil.h"
#include "../../../main/cpp/business/CPUSpecifications.h"

static const QString TIME_IN_STATE_TEST("business/time_in_state_cpu_%1");

CPUFrequencyTest::CPUFrequencyTest() :
		cpuFrequency(0) {
	QDir::setCurrent(TestUtil::getAbsoluteTestingPath());
}

CPUFrequencyTest::~CPUFrequencyTest() {
}

void CPUFrequencyTest::setUp() {
	cpuFrequency = new CPUFrequency();
	cpuFrequency->setTimeInStateFileName(TIME_IN_STATE_TEST);
}

void CPUFrequencyTest::tearDown() {
	delete cpuFrequency;
}

void CPUFrequencyTest::testGetTimeInFrequencyNow() {
	QHash<int, int> timeInFrequency(cpuFrequency->getTimeInFrequencyNow());

	TS_ASSERT_EQUALS(CPUSpecifications::getInstance()->getNumberOfCores(),
			timeInFrequency.size());

	TS_ASSERT_EQUALS(
			1 * CPUSpecifications::getInstance()->getNumberOfCores() * 10 / CPUSpecifications::getInstance()->getTimeUnit(),
			timeInFrequency.value(1));
	TS_ASSERT_EQUALS(
			2 * CPUSpecifications::getInstance()->getNumberOfCores() * 10 / CPUSpecifications::getInstance()->getTimeUnit(),
			timeInFrequency.value(2));
	TS_ASSERT_EQUALS(
			3 * CPUSpecifications::getInstance()->getNumberOfCores() * 10 / CPUSpecifications::getInstance()->getTimeUnit(),
			timeInFrequency.value(3));
	TS_ASSERT_EQUALS(
			4 * CPUSpecifications::getInstance()->getNumberOfCores() * 10 / CPUSpecifications::getInstance()->getTimeUnit(),
			timeInFrequency.value(4));
}

