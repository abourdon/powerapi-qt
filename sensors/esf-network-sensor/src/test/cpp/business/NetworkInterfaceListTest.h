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
#ifndef NETWORKINTERFACELISTTEST_H_
#define NETWORKINTERFACELISTTEST_H_
#include <cxxtest/TestSuite.h>
#include <sof/util/logging/Logger.h>
#include "../../../main/cpp/business/NetworkInterfaceList.h"

using sof::util::logging::Logger;
using namespace CxxTest;

class NetworkInterfaceListTest: public TestSuite {
public:
	static Logger &logger;

	NetworkInterfaceListTest();
	virtual ~NetworkInterfaceListTest();

	void setUp();
	void tearDown();

	void testGetCurrentNetworkInterfaces();

	void testGetNetworkInterfaceControllerTypeEthernet();
	void testGetNetworkInterfaceControllerTypeUnknown();

	void testGetNetworkInterfaceControllerNameKnown();
	void testGetNetworkInterfaceControllerNameUnknown();

private:
	NetworkInterfaceList *networkInterfaceList;
};

#endif /* NETWORKINTERFACELISTTEST_H_ */
