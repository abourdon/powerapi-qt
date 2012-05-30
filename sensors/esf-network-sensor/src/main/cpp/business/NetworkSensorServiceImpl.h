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
#ifndef NETWORKSENSORSERVICEIMPL_H_
#define NETWORKSENSORSERVICEIMPL_H_
#include <sof/util/logging/Logger.h>
#include "../api/NetworkSensorService.h"
#include "NetworkInterfaceList.h"
#include "EmittedReceivedBytes.h"

using sof::util::logging::Logger;

class NetworkSensorServiceImpl: public NetworkSensorService {
public:
	static Logger &logger;

	NetworkSensorServiceImpl();
	virtual ~NetworkSensorServiceImpl();

	QSet<NetworkInterface *> getCurrentNetworkInterfaces();

	NetworkInterfaceBytes getEmittedReceivedNumberOfBytesNow(pid_t pid,
			const NetworkInterface &networkInterface);

	LinkState::State getLinkStateNow(const NetworkInterface &networkInterface);

	float getPowerConsumption(const NetworkInterface & networkInterface,
			const LinkState::State & state);

private:
	NetworkInterfaceList *networkInterfaceList;
	EmittedReceivedBytes *emittedReceivedBytes;
	LinkState *linkState;
};

#endif /* NETWORKSENSORSERVICEIMPL_H_ */
