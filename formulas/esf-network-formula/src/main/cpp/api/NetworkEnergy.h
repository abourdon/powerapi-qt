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
#ifndef NETWORKENERGY_H_
#define NETWORKENERGY_H_
#include <sys/types.h>
#include <QtCore>
#include <esf-network-sensor/api/NetworkInterfaceBytes.h>

class NetworkEnergy {
public:
	NetworkEnergy(pid_t pid = -1, double watt = -1);
	NetworkEnergy(const NetworkEnergy &networkEnergy);
	virtual ~NetworkEnergy();

	bool operator==(const NetworkEnergy &networkEnergy);

	pid_t getPID() const;
	void setPID(pid_t pid);

	double getWatt() const;
	void setWatt(double watt);

    NetworkInterfaceBytes getErBytes() const;
    void setErBytes(NetworkInterfaceBytes erBytes);
private:
	pid_t pid;
	double watt;
	NetworkInterfaceBytes erBytes;
};

Q_DECLARE_METATYPE(NetworkEnergy)

#endif /* NETWORKENERGY_H_ */
