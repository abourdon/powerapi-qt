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
#include <Qt>
#include <QtCore>
#include <QtSql>
#include <iostream>
#include <sof/framework/Launcher.h>
#include <sof/framework/ServiceTracker.h>
#include <sof/instantiation/unix/SharedLibLoader.h>
#include <sof/instantiation/NullCreator.h>
#include <sof/util/logging/Logger.h>
#include <sof/util/threading/SingleThreaded.h>
#include <sof/config/ConfigFileReader.h>
#include <esf-core/bundle/ServiceState.h>
#include <esf-core/db/ESFDataBase.h>
#include <esf-cpu-sensor/business/CPUFrequency.h>
#include <esf-cpu-sensor/business/CPUSpecifications.h>
#include <esf-cpu-sensor/business/CPUTime.h>
#include <esf-cpu-sensor/business/CPUTransition.h>
#include <esf-cpu-sensor/business/CPUVoltage.h>
#include <esf-cpu-formula/business/CPUFormulaComputer.h>
#include <esf-cpu-formula/business/CPUFormulaServiceImpl.h>
#include <esf-network-sensor/api/LinkState.h>
#include <esf-network-sensor/business/EmittedReceivedBytes.h>
#include <esf-network-sensor/business/NetworkInterfaceList.h>
#include <esf-network-sensor/business/NetworkSensorServiceImpl.h>
#include <esf-network-formula/business/NetworkFormulaComputer.h>
#include <esf-network-formula/business/NetworkFormulaServiceImpl.h>
#include <esf-main/business/DisplayEnergy.h>
#include <esf-main/business/ResultStorage.h>
#include <esf-main/control/ESFMainActivator.h>

using namespace std;
using namespace sof::config;
using namespace sof::framework;
using namespace sof::util::logging;
using namespace sof::util::threading;
using namespace sof::instantiation::unix_;

Logger &logger(LoggerFactory::getLogger("Main"));

Logger::LogLevel noLog(Logger::LOG_NOLOG);
Logger::LogLevel debugLog(Logger::LOG_DEBUG);

bool cleanOutputDir() {
	QSettings settings("inria-adam", "esf");
	QString esfOutputDirPath(
			settings.value("ResultStorage/output",
					QVariant::fromValue(QString("/tmp/esf_output_lib"))).toString());
	return system("rm -rf /tmp/esf_output_lib") == 0;
}

void initLoggers() {
	QThreadPool::globalInstance()->setMaxThreadCount(1000);

	LoggerFactory::setLogLevel(noLog);

	ServiceState::logger.setLogLevel(noLog);
	ESFDataBase::logger.setLogLevel(noLog);

	CPUFrequency::logger.setLogLevel(noLog);
	CPUSpecifications::logger.setLogLevel(noLog);
	CPUTime::logger.setLogLevel(noLog);
	CPUTransition::logger.setLogLevel(noLog);
	CPUVoltage::logger.setLogLevel(noLog);
	CPUFormulaComputer::logger.setLogLevel(noLog);
	CPUFormulaServiceImpl::logger.setLogLevel(noLog);

	LinkState::logger.setLogLevel(noLog);
	EmittedReceivedBytes::logger.setLogLevel(noLog);
	NetworkInterfaceList::logger.setLogLevel(noLog);
	NetworkSensorServiceImpl::logger.setLogLevel(noLog);
	NetworkFormulaServiceImpl::logger.setLogLevel(noLog);
	NetworkFormulaComputer::logger.setLogLevel(noLog);

	DisplayEnergy::logger.setLogLevel(noLog);
	ResultStorage::logger.setLogLevel(noLog);
	ESFMainActivator::logger.setLogLevel(noLog);

	logger.setLogLevel(debugLog);
}

void launchSOF() {
	vector<BundleConfiguration> configuration(
			ConfigFileReader::readFromFile("bundles.sof"));

	Launcher<SingleThreaded, SharedLibLoader> launcher;
	launcher.setLogLevel(noLog);
	launcher.start(configuration);
	launcher.startAdministrationBundle();
}

int main(int argc, char* argv[]) {
	QCoreApplication app(argc, argv);

	initLoggers();

	if (!cleanOutputDir()) {
		logger.log(Logger::LOG_ERROR, "unable to delete output directory");
	}

	launchSOF();

	return app.exec();
}
