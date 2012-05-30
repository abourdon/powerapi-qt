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
#ifndef NETWORKINTERFACEBYTES_H_
#define NETWORKINTERFACEBYTES_H_
#include <QtCore>

class NetworkInterfaceBytes {
public:
	NetworkInterfaceBytes(QString interfaceName = "", long emittedBytes = 0,
			long receivedBytes = 0);
	NetworkInterfaceBytes(const NetworkInterfaceBytes &networkInterfaceBytes);
	virtual ~NetworkInterfaceBytes();

	bool operator==(const NetworkInterfaceBytes &networkInterfaceBytes);

	long getEmittedBytes() const;
	void setEmittedBytes(long emittedBytes);

	QString getInterfaceName() const;
	void setInterfaceName(QString interfaceName);

	long getReceivedBytes() const;
	void setReceivedBytes(long receivedBytes);

private:
	QString interfaceName;
	long emittedBytes;
	long receivedBytes;
};

Q_DECLARE_METATYPE(NetworkInterfaceBytes)

#endif /* NETWORKINTERFACEBYTES_H_ */
