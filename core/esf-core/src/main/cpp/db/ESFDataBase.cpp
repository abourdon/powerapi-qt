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
#include <sof/util/logging/LoggerFactory.h>
#include "ESFDataBase.h"

using sof::util::logging::LoggerFactory;

Logger &ESFDataBase::logger(LoggerFactory::getLogger("ESFDataBase"));

const QString ESFDataBase::APPLICATION_NAME("esf");
const QString ESFDataBase::ORGANIZATION_NAME("inria-adam");

const QString ESFDataBase::INI_ESF_DATABASE_SQL_TYPE("Database/sql");
const QString ESFDataBase::INI_ESF_DATABASE_HOSTNAME("Database/hostname");
const QString ESFDataBase::INI_ESF_DATABASE_DATABASE_NAME("Database/database");
const QString ESFDataBase::INI_ESF_DATABASE_USER_NAME("Database/user");
const QString ESFDataBase::INI_ESF_DATABASE_PASSWORD("Database/password");

ESFDataBase *ESFDataBase::instance(0);

QMutex ESFDataBase::lock;

ESFDataBase::ESFDataBase() :
		settings(ORGANIZATION_NAME, APPLICATION_NAME), databaseConnections(), databaseName(
				QString::null), hostName(QString::null), password(
				QString::null), sqlType(QString::null), userName(QString::null) {
	if (getSqlType().isNull() || getSqlType().isEmpty()) {
		QString message("unable to find INI configuration file: %1/%2");
		message = message.arg(APPLICATION_NAME);
		message = message.arg(ORGANIZATION_NAME);
		logger.log(Logger::LOG_ERROR, message.toStdString());
	}
	logger.setLogLevel(Logger::LOG_NOLOG);
}

ESFDataBase::~ESFDataBase() {
	foreach(QString databaseConnection, databaseConnections) {
		removeDatabaseConnection(QSqlDatabase::database(databaseConnection));
	}
}

ESFDataBase *ESFDataBase::getInstance() {
	QMutexLocker locker(&lock);
	if (instance == 0) {
		instance = new ESFDataBase();
	}
	return instance;
}

QSqlDatabase ESFDataBase::getNewDatabaseConnection() {
	QMutexLocker locker(&lock);
	QSqlDatabase database(
			QSqlDatabase::addDatabase(getSqlType(),
					QUuid::createUuid().toString()));
	database.setHostName(getHostName());
	database.setDatabaseName(getDatabaseName());
	database.setUserName(getUserName());
	database.setPassword(getPassword());

	databaseConnections.append(database.connectionName());
	logger.log(
			Logger::LOG_DEBUG,
			"New database connection required. Number of database connections: %1",
			databaseConnections.size());

	return database;
}

void ESFDataBase::removeDatabaseConnection(
		const QSqlDatabase & databaseConnection) {
	if (databaseConnections.contains(databaseConnection.connectionName())) {
		QSqlDatabase database(
				QSqlDatabase::database(databaseConnection.connectionName()));
		if (database.isValid() && database.isOpen()) {
			database.close();
		}
		databaseConnections.removeOne(databaseConnection.connectionName());
//		QSqlDatabase::removeDatabase(databaseConnection.connectionName());
		logger.log(Logger::LOG_DEBUG,
				"Database connection removed. %1 database connections left",
				databaseConnections.size());
	}
}

QString ESFDataBase::getDatabaseName() {
	if (databaseName.isNull()) {
		databaseName =
				settings.value(INI_ESF_DATABASE_DATABASE_NAME).toString();
	}
	return databaseName;
}

QString ESFDataBase::getHostName() {
	if (hostName.isNull()) {
		hostName = settings.value(INI_ESF_DATABASE_HOSTNAME).toString();
	}
	return hostName;
}

QString ESFDataBase::getPassword() {
	if (password.isNull()) {
		password = settings.value(INI_ESF_DATABASE_PASSWORD).toString();
	}
	return password;
}

QString ESFDataBase::getSqlType() {
	if (sqlType.isNull()) {
		sqlType = settings.value(INI_ESF_DATABASE_SQL_TYPE).toString();
	}
	return sqlType;
}

QString ESFDataBase::getUserName() {
	if (userName.isNull()) {
		userName = settings.value(INI_ESF_DATABASE_USER_NAME).toString();
	}
	return userName;
}

