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
#include "CPUTime2Test.h"
#include "../util/TestUtil.h"
#include <QtCore>

static const QString GLOBAL_CPU_STAT_FILE_TEST("business/proc_stat");
static const QString PID_CPU_STAT_FILE_TEST("business/proc_stat_pid_%1");

CPUTime2Test::CPUTime2Test() {
	QDir::setCurrent(TestUtil::getAbsoluteTestingPath());
}

CPUTime2Test::~CPUTime2Test() {
}

void CPUTime2Test::setUp() {
	cpuTime2 = new CPUTime2();
}

void CPUTime2Test::tearDown() {
	delete cpuTime2;
}

void CPUTime2Test::testGetElapsedTimeNow() {
	cpuTime2->setGlobalCpuStatFile(GLOBAL_CPU_STAT_FILE_TEST);
	TS_ASSERT_DELTA(1646578, cpuTime2->getElapsedTimeNow(), 0.0001);
}

void CPUTime2Test::testGetElapsedTimeNowPID() {
	cpuTime2->setPidCpuStatFile(PID_CPU_STAT_FILE_TEST);
	TS_ASSERT_DELTA(4155, cpuTime2->getElapsedTimeNow(1234), 0.0001);
}
