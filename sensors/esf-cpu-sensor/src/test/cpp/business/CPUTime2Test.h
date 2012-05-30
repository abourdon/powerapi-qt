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
#ifndef CPUTIME2TEST_H_
#define CPUTIME2TEST_H_
#include <cxxtest/TestSuite.h>
#include "../../../main/cpp/business/CPUTime2.h"

using CxxTest::TestSuite;

class CPUTime2Test: public TestSuite {
public:
	CPUTime2Test();
	virtual ~CPUTime2Test();

	void setUp();
	void tearDown();

	void testGetElapsedTimeNow();
	void testGetElapsedTimeNowPID();

private:
	CPUTime2 *cpuTime2;
};

#endif /* CPUTIME2TEST_H_ */
