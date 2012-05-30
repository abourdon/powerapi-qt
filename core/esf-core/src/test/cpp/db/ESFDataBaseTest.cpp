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
#include "ESFDataBaseTest.h"
#include "../../../main/cpp/db/ESFDataBase.h"
#include <QtSql>

ESFDataBaseTest::ESFDataBaseTest() {
}

ESFDataBaseTest::~ESFDataBaseTest() {
}

void ESFDataBaseTest::testConnexion() {
	QSqlDatabase database(
			ESFDataBase::getInstance()->getNewDatabaseConnection());
	TS_ASSERT(database.open());
	ESFDataBase::getInstance()->removeDatabaseConnection(database);
}

