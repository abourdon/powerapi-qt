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
#include "ServiceStateTest.h"

ServiceStateTest::ServiceStateTest() :
		serviceState(0) {
}

ServiceStateTest::~ServiceStateTest() {
}

void ServiceStateTest::setUp() {
	serviceState = new ServiceState();
}

void ServiceStateTest::tearDown() {
	delete serviceState;
}

void ServiceStateTest::testIsAlive() {
	QMutexLocker locker(serviceState->getLock());
	serviceState->setAlive(true);
	TS_ASSERT(serviceState->isAlive());
	locker.unlock();

	locker.relock();
	serviceState->setAlive(false);
	TS_ASSERT(!serviceState->isAlive());
	locker.unlock();
}

