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
#include "ResultStorage.h"

using sof::util::logging::LoggerFactory;

const QString ResultStorage::DEFAULT_ESF_LIB_OUTPUT_DIR_PATH(
		QDir::tempPath().append(QDir::separator()).append("esf_output_lib"));

const QString ResultStorage::INI_ORGANIZATION_NAME("inria-adam");
const QString ResultStorage::INI_APPLICATION_NAME("esf");
const QString ResultStorage::INI_ESF_OUTPUT_LIB_DIR_PATH(
		"ResultStorage/output");

const QString ResultStorage::GLOBAL_PID_DIR_NAME("all");

Logger &ResultStorage::logger(LoggerFactory::getLogger("ResultStorage"));

ResultStorage::ResultStorage() :
		esfLibOutputDirPath(DEFAULT_ESF_LIB_OUTPUT_DIR_PATH), esfLibOutputDirMutex(), initialized(), settings(
				INI_ORGANIZATION_NAME, INI_APPLICATION_NAME) {
	initialized = init();
	logger.log(Logger::LOG_ERROR, "init: '%1'", initialized);
	logger.log(Logger::LOG_ERROR, "dir: '%1'",
			esfLibOutputDirPath.toStdString());
}

QString ResultStorage::getEsfLibOutputDirName() const {
	return esfLibOutputDirPath;
}

void ResultStorage::setEsfLibOutputDirName(QString esfLibOutputDirName) {
	this->esfLibOutputDirPath = esfLibOutputDirName;
}

ResultStorage::~ResultStorage() {
}

bool ResultStorage::init() {
	esfLibOutputDirPath = settings.value(INI_ESF_OUTPUT_LIB_DIR_PATH,
			DEFAULT_ESF_LIB_OUTPUT_DIR_PATH).toString();

	if (!QDir::root().exists(esfLibOutputDirPath)) {
		if (!QDir::root().mkdir(esfLibOutputDirPath)) {
			logger.log(Logger::LOG_ERROR,
					"unable to create esf_lib_output directory '%1'",
					esfLibOutputDirPath.toStdString());
			return false;
		}
	}
	esfLibOutputDir = QDir(esfLibOutputDirPath);
	if (!esfLibOutputDir.isReadable()) {
		logger.log(
				Logger::LOG_ERROR,
				"unable to read esf_lib_output directory '%1' under the temporary path",
				esfLibOutputDirPath.toStdString());
		return false;
	}

	return true;
}

void ResultStorage::storeEnergy(const CPUEnergy & cpuEnergy) {
	if (!initialized) {
		return;
	}

	QMutexLocker locker(&esfLibOutputDirMutex);
	if (!createPIDDir(cpuEnergy.getPID())) {
		return;
	}

	QFile cpuPIDFile(
			esfLibOutputDir.filePath(
					QString::number(cpuEnergy.getPID()).append(
							QDir::separator()).append("cpu")));
	if (!cpuPIDFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
		logger.log(Logger::LOG_ERROR,
				"unable to open CPU energy storage file for pid '%1'",
				cpuEnergy.getPID());
		return;
	}
	QTextStream cpuPIDStream(&cpuPIDFile);
	cpuPIDStream << cpuEnergy.getWatt();
	cpuPIDFile.close();
}

void ResultStorage::storeEnergy(const NetworkEnergy & networkEnergy) {
	if (!initialized) {
		return;
	}

	QMutexLocker locker(&esfLibOutputDirMutex);
	if (!createPIDDir(networkEnergy.getPID())) {
		return;
	}

	QFile networkPIDFile(
			esfLibOutputDir.filePath(
					QString::number(networkEnergy.getPID()).append(
							QDir::separator()).append("network")));
	if (!networkPIDFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
		logger.log(Logger::LOG_ERROR,
				"unable to open network energy storage file for pid '%1'",
				networkEnergy.getPID());
		return;
	}
	QTextStream networkPIDStream(&networkPIDFile);
	networkPIDStream << networkEnergy.getWatt();
	networkPIDFile.close();
}

void ResultStorage::eventUpdated(const CPUEnergy & cpuEnergyComputed) {
	storeEnergy(cpuEnergyComputed);
	updateGlobalEnergy(cpuEnergyComputed);
}

void ResultStorage::eventUpdated(const NetworkEnergy & networkEnergyComputed) {
	storeEnergy(networkEnergyComputed);
	updateGlobalEnergy(networkEnergyComputed);
}

QDir ResultStorage::getEsfLibOutputDir() const {
	return esfLibOutputDir;
}

void ResultStorage::setEsfLibOutputDir(QDir esfLibOutputDir) {
	this->esfLibOutputDir = esfLibOutputDir;
}

bool ResultStorage::createPIDDir(const pid_t & pid) {
	if (!initialized) {
		return false;
	}

	return esfLibOutputDir.exists(QString::number(pid)) ?
			true : esfLibOutputDir.mkdir(QString::number(pid));
}

bool ResultStorage::createGlobalPIDDir() {
	if (!initialized) {
		return false;
	}

	return esfLibOutputDir.exists(GLOBAL_PID_DIR_NAME) ?
			true : esfLibOutputDir.mkdir(GLOBAL_PID_DIR_NAME);
}

void ResultStorage::updateGlobalEnergy(const CPUEnergy & cpuEnergy) {
	QMutexLocker locker(&esfLibOutputDirMutex);
	if (!createGlobalPIDDir()) {
		return;
	}

	networkEnergyList.insert(cpuEnergy.getPID(), cpuEnergy.getWatt());
	double totalCPUEnergy = 0.0;
	foreach (double cpuEnergy, networkEnergyList.values()) {
		totalCPUEnergy += cpuEnergy;
	}

	QString globalPIDDirName(GLOBAL_PID_DIR_NAME);
	QFile globalPIDFile(
			esfLibOutputDir.filePath(
					globalPIDDirName.append(QDir::separator()).append("cpu")));
	if (!globalPIDFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
		logger.log(Logger::LOG_ERROR,
				"unable to open global CPU energy storage file");
		return;
	}
	QTextStream globalPIDStream(&globalPIDFile);
	globalPIDStream << totalCPUEnergy;
	globalPIDFile.close();
}

void ResultStorage::updateGlobalEnergy(const NetworkEnergy & networkEnergy) {
	QMutexLocker locker(&esfLibOutputDirMutex);
	if (!createGlobalPIDDir()) {
		return;
	}

	networkEnergyList.insert(networkEnergy.getPID(), networkEnergy.getWatt());
	double totalNetworkEnergy = 0.0;
	foreach (double networkEnergy, networkEnergyList.values()) {
		totalNetworkEnergy += networkEnergy;
	}

	QString globalPIDDirName(GLOBAL_PID_DIR_NAME);
	QFile globalPIDFile(
			esfLibOutputDir.filePath(
					globalPIDDirName.append(QDir::separator()).append(
							"network")));
	if (!globalPIDFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
		logger.log(Logger::LOG_ERROR,
				"unable to open global Network energy storage file");
		return;
	}
	QTextStream globalPIDStream(&globalPIDFile);
	globalPIDStream << totalNetworkEnergy;
	globalPIDFile.close();
}
