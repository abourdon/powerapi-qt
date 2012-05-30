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
#ifndef CPUTRANSITIONTEST_H_
#define CPUTRANSITIONTEST_H_
#include <cxxtest/TestSuite.h>
#include "../../../main/cpp/business/CPUTransition.h"

using namespace CxxTest;

class CPUTransitionTest: public TestSuite {
public:
	CPUTransitionTest();
	virtual ~CPUTransitionTest();

	void setUp();
	void tearDown();

	void testGetTotalTransitionsNow();

private:
	CPUTransition *cpuTransition;
};

#endif /* CPUTRANSITIONTEST_H_ */
