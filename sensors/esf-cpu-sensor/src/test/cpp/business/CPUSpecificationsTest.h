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
#ifndef CPUSPECIFICATIONSTEST_H_
#define CPUSPECIFICATIONSTEST_H_
#include <cxxtest/TestSuite.h>
#include <QString>

using namespace CxxTest;

class CPUSpecificationsTest: public TestSuite {
public:
	CPUSpecificationsTest();
	virtual ~CPUSpecificationsTest();

	void testGetNumberOfCores();
	void testGetName();
};

#endif /* CPUSPECIFICATIONSTEST_H_ */
