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
#ifndef SERVICESTATETEST_H_
#define SERVICESTATETEST_H_
#include <cxxtest/TestSuite.h>
#include "../../../main/cpp/bundle/ServiceState.h"

using namespace CxxTest;

class ServiceStateTest: public TestSuite {
public:
	ServiceStateTest();
	virtual ~ServiceStateTest();

	void setUp();
	void tearDown();

	void testIsAlive();

private:
	ServiceState *serviceState;
};

#endif /* SERVICESTATETEST_H_ */
