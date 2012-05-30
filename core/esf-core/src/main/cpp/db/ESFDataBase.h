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
#ifndef ESFDATABASE_H_
#define ESFDATABASE_H_
#include <sof/util/logging/Logger.h>
#include <QtCore>
#include <QtSql>

using sof::util::logging::Logger;

class ESFDataBase {
public:
	static Logger &logger;

	static const QString APPLICATION_NAME;
	static const QString ORGANIZATION_NAME;

	static const QString INI_ESF_DATABASE_SQL_TYPE;
	static const QString INI_ESF_DATABASE_HOSTNAME;
	static const QString INI_ESF_DATABASE_DATABASE_NAME;
	static const QString INI_ESF_DATABASE_USER_NAME;
	static const QString INI_ESF_DATABASE_PASSWORD;

	static ESFDataBase *getInstance();

	ESFDataBase();
	virtual ~ESFDataBase();

	QSqlDatabase getNewDatabaseConnection();
	void removeDatabaseConnection(const QSqlDatabase &databaseConnection);

	QString getDatabaseName();
	QString getHostName();
	QString getPassword();
	QString getSqlType();
	QString getUserName();

private:
	static ESFDataBase *instance;
	static QMutex lock;

	QSettings settings;

	QList<QString> databaseConnections;

	QString sqlType;
	QString hostName;
	QString databaseName;
	QString userName;
	QString password;
};

#endif /* ESFDATABASE_H_ */
