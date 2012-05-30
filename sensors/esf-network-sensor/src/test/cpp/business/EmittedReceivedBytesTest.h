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
#ifndef EMITTEDRECEIVEDBYTESTEST_H_
#define EMITTEDRECEIVEDBYTESTEST_H_
#include <cxxtest/TestSuite.h>
#include <QtCore>
#include "../../../main/cpp/business/EmittedReceivedBytes.h"

using namespace CxxTest;

class EmittedReceivedBytesTest: public TestSuite {
public:
	static const QString TEST_PROC_STAT_FILE_NAME;

	EmittedReceivedBytesTest();
	virtual ~EmittedReceivedBytesTest();

	void setUp();
	void tearDown();

	void testGetEmittedReceivedNumberOfBytesNow();
	void testGetEmittedReceivedNumberOfBytesNowWrongFileName();

private:
	EmittedReceivedBytes *emittedReceivedBytes;
};

#endif /* EMITTEDRECEIVEDBYTESTEST_H_ */
