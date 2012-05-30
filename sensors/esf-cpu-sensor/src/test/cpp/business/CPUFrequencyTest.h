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
#ifndef CPUFREQUENCYTEST_H_
#define CPUFREQUENCYTEST_H_
#include <cxxtest/TestSuite.h>
#include "../../../main/cpp/business/CPUFrequency.h"

using namespace CxxTest;

class CPUFrequencyTest: public TestSuite {
public:
	CPUFrequencyTest();
	virtual ~CPUFrequencyTest();

	void setUp();
	void tearDown();

	void testGetTimeInFrequencyNow();

private:
	CPUFrequency *cpuFrequency;
};

#endif /* CPUFREQUENCYTEST_H_ */
