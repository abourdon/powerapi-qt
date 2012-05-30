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
#ifndef NETWORKINTERFACE_H_
#define NETWORKINTERFACE_H_
#include <QtCore>

class NetworkInterface {
public:
	enum TYPE {
		ETHERNET, WIRELESS, UNKNOWN
	};

	NetworkInterface(QString name);
	virtual ~NetworkInterface();

	bool operator==(const NetworkInterface &networkInterface) const;

	QString getName() const;

	int getVendorId() const;
	void setVendorId(int vendorId);

	int getDeviceId() const;
	void setDeviceId(int deviceId);

	TYPE getType() const;
	void setType(TYPE type);

	QString getModelName() const;
	void setModelName(QString modelName);

private:
	QString name;
	int vendorId;
	int deviceId;
	TYPE type;
	QString modelName;
};

#endif /* NETWORKINTERFACE_H_ */
