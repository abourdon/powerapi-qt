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
#ifndef NETWORKINTERFACELIST_H_
#define NETWORKINTERFACELIST_H_
#include <sof/util/logging/Logger.h>
#include <QtSql>
#include "../api/NetworkInterface.h"

using sof::util::logging::Logger;

class NetworkInterfaceList {
public:
	static Logger &logger;

	static const QString SYS_CLASS_NET_DIRECTORY;

	NetworkInterfaceList();
	virtual ~NetworkInterfaceList();

	QSet<NetworkInterface *> getCurrentNetworkInterfaces();

	NetworkInterface::TYPE getNetworkInterfaceControllerType(int vendorId, int deviceId);
	QString getNetworkInterfaceControllerName(int vendorId, int deviceId);
private:
	QHash<QString, NetworkInterface *> *knownNIC;

	NetworkInterface *newNIC(int vendorId, int deviceId);
	QString toKnownNICKey(int vendorId, int deviceId);
};

#endif /* NETWORKINTERFACELIST_H_ */
