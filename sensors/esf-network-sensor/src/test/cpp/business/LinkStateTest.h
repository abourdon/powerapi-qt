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
#ifndef LINKSTATETEST_H_
#define LINKSTATETEST_H_
#include <cxxtest/TestSuite.h>
#include <sof/util/logging/Logger.h>
#include "../../../main/cpp/api/LinkState.h"

using namespace CxxTest;
using sof::util::logging::Logger;

class LinkStateTest: public TestSuite {
public:
	static Logger &logger;

	LinkStateTest();
	virtual ~LinkStateTest();

	void setUp();
	void tearDown();

	void testGetCurrentLinkStateNow();
	void testGetCurrentLinkStateNowWithUnknownInterface();

	void testGetPowerConsumption();
	void testGetPowerConsumptionWithUnknownInterface();
	void testGetPowerConsumptionWithUnknownLinkState();
private:
	LinkState *linkState;
};

#endif /* LINKSTATETEST_H_ */
