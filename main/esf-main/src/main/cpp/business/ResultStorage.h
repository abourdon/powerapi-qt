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
#ifndef RESULTSTORAGE_H_
#define RESULTSTORAGE_H_
#include <esf-core/event/EventListener.h>
#include <esf-cpu-formula/api/CPUEnergy.h>
#include <esf-network-formula/api/NetworkEnergy.h>
#include <sof/util/logging/Logger.h>
#include <sys/types.h>
#include <QtCore>

using sof::util::logging::Logger;

class ResultStorage: public EventListener<CPUEnergy>, public EventListener<
		NetworkEnergy> {
public:
	static Logger &logger;

	static const QString DEFAULT_ESF_LIB_OUTPUT_DIR_PATH;
	static const QString GLOBAL_PID_DIR_NAME;

	static const QString INI_APPLICATION_NAME;
	static const QString INI_ORGANIZATION_NAME;
	static const QString INI_ESF_OUTPUT_LIB_DIR_PATH;


	ResultStorage();
	virtual ~ResultStorage();

	QString getEsfLibOutputDirName() const;
	void setEsfLibOutputDirName(QString esfLibOutputDirName);

	QDir getEsfLibOutputDir() const;
	void setEsfLibOutputDir(QDir esfLibOutputDir);

	void eventUpdated(const CPUEnergy &cpuEnergyComputed);
	void eventUpdated(const NetworkEnergy &networkEnergyComputed);

	void storeEnergy(const CPUEnergy &cpuEnergy);
	void storeEnergy(const NetworkEnergy &networkEnergy);

	void updateGlobalEnergy(const CPUEnergy &cpuEnergy);
	void updateGlobalEnergy(const NetworkEnergy &networkEnergy);

private:
	QSettings settings;
	bool initialized;

	QDir esfLibOutputDir;
	QString esfLibOutputDirPath;
	QMutex esfLibOutputDirMutex;

	bool init();
	bool createPIDDir(const pid_t &pid);
	bool createGlobalPIDDir();

	QHash<pid_t, double> cpuEnergyList;
	QHash<pid_t, double> networkEnergyList;
};

#endif /* RESULTSTORAGE_H_ */
