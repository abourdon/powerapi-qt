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
#ifndef NETWORKFORMULASERVICEIMPL_H_
#define NETWORKFORMULASERVICEIMPL_H_
#include <sof/util/logging/Logger.h>
#include <esf-core/event/EventListener.h>
#include <esf-network-sensor/api/NetworkSensorService.h>
#include "../api/NetworkFormulaService.h"
#include "NetworkFormulaComputer.h"

using sof::util::logging::Logger;

class NetworkFormulaServiceImpl: public NetworkFormulaService,
		public EventListener<NetworkEnergy> {
public:
	static Logger &logger;

	NetworkFormulaServiceImpl();
	virtual ~NetworkFormulaServiceImpl();

	NetworkEnergy getNetworkEnergy(pid_t pid, long duration);

	void startService();
	void stopService();

	void setNetworkSensorService(NetworkSensorService *networkSensorService);

	void eventUpdated(const NetworkEnergy &networkEnergy);
private:
	NetworkSensorService *networkSensorService;

	QHash<pid_t, NetworkFormulaComputer *> *computers;
	QHash<pid_t, NetworkEnergy *> *results;

	QMutex computersMutex;
	QMutex resultsMutex;
};

#endif /* NETWORKFORMULASERVICEIMPL_H_ */
