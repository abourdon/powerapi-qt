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
#ifndef NETWORKFORMULACOMPUTER_H_
#define NETWORKFORMULACOMPUTER_H_
#include <QtCore>
#include <esf-core/event/EventListenerList.h>
#include <esf-network-sensor/api/NetworkSensorService.h>
#include <esf-network-sensor/api/NetworkInterfaceBytes.h>
#include <sof/util/logging/Logger.h>
#include "../api/NetworkEnergy.h"

using sof::util::logging::Logger;

class NetworkFormulaComputer: public QThread, public EventListenerList<
		NetworkEnergy> {
Q_OBJECT
public:
	static Logger &logger;

	NetworkFormulaComputer(pid_t pid, long duration,
			NetworkSensorService *networkSensorService);
	virtual ~NetworkFormulaComputer();

	void setNetworkSensorService(NetworkSensorService *networkSensorService);

	QHash<QString, NetworkInterface *> *getCurrentNetworkInterfaces();

	void startComputation();
	void stopComputation();
private:
	template<class KEY, class VALUE> static void deleteHash(
			QHash<KEY, VALUE *> *hash);

	static float powerComputation(float basePower, long duration,
			LinkState::State linkState,
			const NetworkInterfaceBytes &networkInterfaceBytes);

	pid_t pid;
	long duration;
	NetworkSensorService *networkSensorService;

	NetworkEnergy *networkEnergy;
	QFuture<void> execution;

	QHash<QString, NetworkInterface *> *currentNetworkInterfaces;

	void computeNetworkFormula();
};

#endif /* NETWORKFORMULACOMPUTER_H_ */
