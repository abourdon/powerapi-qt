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
#ifndef RESULTSTORAGETEST_H_
#define RESULTSTORAGETEST_H_
#include <cxxtest/TestSuite.h>
#include "../../../main/cpp/business/ResultStorage.h"

using CxxTest::TestSuite;

class ResultStorageTest: public TestSuite {
public:
	ResultStorageTest();
	virtual ~ResultStorageTest();

	void setUp();
	void tearDown();

	void testStoreCPUEnergy();
	void testStoreNetworkEnergy();

private:
	static Logger &logger;

	ResultStorage *resultStorage;
};

#endif /* RESULTSTORAGETEST_H_ */
