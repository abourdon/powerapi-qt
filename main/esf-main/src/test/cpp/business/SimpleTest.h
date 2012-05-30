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
#ifndef SIMPLETEST_H_
#define SIMPLETEST_H_
#include <cxxtest/TestSuite.h>

using namespace CxxTest;

class SimpleTest: public TestSuite {
public:
	SimpleTest();
	virtual ~SimpleTest();

	void testSimple();
};

#endif /* SIMPLETEST_H_ */
