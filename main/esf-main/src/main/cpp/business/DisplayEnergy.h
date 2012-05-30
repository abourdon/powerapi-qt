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
#ifndef DISPLAYENERGY_H_
#define DISPLAYENERGY_H_
#include <esf-core/event/EventListener.h>
#include <esf-cpu-formula/api/CPUEnergy.h>
#include <esf-network-formula/api/NetworkEnergy.h>
#include <sof/util/logging/Logger.h>
#include <QtCore>

using namespace sof::util::logging;

class DisplayEnergy: public EventListener<CPUEnergy>, public EventListener<
		NetworkEnergy> {
public:
	static Logger &logger;

	static const QString DEFAULT_OUTPUT_FILE;

	DisplayEnergy();
	virtual ~DisplayEnergy();

	void eventUpdated(const CPUEnergy &cpuEnergyComputed);
	void eventUpdated(const NetworkEnergy &networkEnergyComputed);

private:
	QString outputFile;

	void displayEnergy(const CPUEnergy &energy);
	void writeEnergy(const CPUEnergy &energy);

	void displayEnergy(const NetworkEnergy &energy);
	void writeEnergy(const NetworkEnergy &energy);
};

#endif /* DISPLAYENERGY_H_ */
