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
#ifndef NETWORKSENSORSERVICE_H_
#define NETWORKSENSORSERVICE_H_
#include <sof/framework/IService.h>
#include <QtCore>
#include <sys/types.h>
#include "NetworkInterface.h"
#include "LinkState.h"
#include "NetworkInterfaceBytes.h"

using namespace sof::framework;

class NetworkSensorService: public IService {
public:
	static const QString CLASS_NAME;

	virtual QSet<NetworkInterface *> getCurrentNetworkInterfaces() = 0;

	virtual NetworkInterfaceBytes getEmittedReceivedNumberOfBytesNow(
			pid_t pid, const NetworkInterface &networkInterface) = 0;

	virtual LinkState::State getLinkStateNow(
			const NetworkInterface &networkInterface) = 0;

	virtual float getPowerConsumption(const NetworkInterface & networkInterface,
			const LinkState::State & state) = 0;
};

#endif /* NETWORKSENSORSERVICE_H_ */
