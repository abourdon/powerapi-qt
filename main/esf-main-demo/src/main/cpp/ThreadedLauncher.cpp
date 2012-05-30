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
#include <iostream>
#include <sof/framework/Launcher.h>
#include <sof/instantiation/unix/SharedLibLoader.h>
#include <sof/instantiation/NullCreator.h>
#include <sof/util/threading/SingleThreaded.h>
#include "ThreadedLauncher.h"

using namespace std;
using namespace sof::framework;
using namespace sof::util::threading;
using namespace sof::instantiation::unix_;

ThreadedLauncher::ThreadedLauncher() {
	connect(this, SIGNAL(started()), SLOT(launch()));
}

ThreadedLauncher::~ThreadedLauncher() {
}

void ThreadedLauncher::run() {
	exec();
}

int ThreadedLauncher::getArgc() const {
	return argc;
}

char **ThreadedLauncher::getArgv() const {
	return argv;
}

void ThreadedLauncher::setArgc(int argc) {
	this->argc = argc;
}

void ThreadedLauncher::setArgv(char **argv) {
	this->argv = argv;
}

void ThreadedLauncher::launch() {
	Logger::LogLevel logLevel = Logger::LOG_DEBUG;
	for (int i = 0; i < argc; i++) {
		string arg(argv[i]);
		if (arg == "-nolog") {
			logLevel = Logger::LOG_NOLOG;
		} else if (arg == "-errorlog") {
			logLevel = Logger::LOG_ERROR;
		} else if (arg == "-debuglog") {
			logLevel = Logger::LOG_DEBUG;
		}
	}

	BundleConfiguration esf_cpu_sensor("esf_cpu_sensor", "CPUSensorActivator",
			"/home/abourdon/dev/energymetric/sensors/esf_cpu_sensor-build",
			"libesf_cpu_sensor.so");
	BundleConfiguration esf_cpu_formula("esf_cpu_formula",
			"CPUFormulaActivator",
			"/home/abourdon/dev/energymetric/formulas/esf_cpu_formula-build",
			"libesf_cpu_formula.so");
	BundleConfiguration esf_main("esf_main", "ESFMainActivator",
			"/home/abourdon/dev/energymetric/util/esf_main-build",
			"libesf_main.so");
	vector<BundleConfiguration> configuration;
	configuration.push_back(esf_cpu_sensor);
	configuration.push_back(esf_cpu_formula);
	configuration.push_back(esf_main);

	Launcher<SingleThreaded, SharedLibLoader> launcher;
	launcher.setLogLevel(logLevel);
	launcher.start(configuration);
	launcher.startAdministrationBundle();
}
