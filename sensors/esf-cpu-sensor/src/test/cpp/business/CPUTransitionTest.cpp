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
#include "CPUTransitionTest.h"
#include "../util/TestUtil.h"
#include "../../../main/cpp/business/CPUSpecifications.h"

static const QString TOTAL_TRANS_FILE_TEST("business/total_trans_cpu_%1");

CPUTransitionTest::CPUTransitionTest() :
		cpuTransition(0) {
	QDir::setCurrent(TestUtil::getAbsoluteTestingPath());
}

CPUTransitionTest::~CPUTransitionTest() {
}

void CPUTransitionTest::setUp() {
	cpuTransition = new CPUTransition();
	cpuTransition->setTotalTransFile(TOTAL_TRANS_FILE_TEST);
}

void CPUTransitionTest::tearDown() {
	delete cpuTransition;
}

void CPUTransitionTest::testGetTotalTransitionsNow() {
	TS_ASSERT_EQUALS(10 * CPUSpecifications::getInstance()->getNumberOfCores(),
			cpuTransition->getTotalTransitionsNow());
}

