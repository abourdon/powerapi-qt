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
#ifndef NETWORKFORMULASERVICE_H_
#define NETWORKFORMULASERVICE_H_
#include <sys/types.h>
#include <QtCore>
#include <sof/framework/IService.h>
#include <esf-core/event/EventListenerList.h>
#include <esf-core/bundle/ServiceState.h>
#include "NetworkEnergy.h"

using namespace sof::framework;

class NetworkFormulaService: public IService,
		public EventListenerList<NetworkEnergy> {
public:
	static const QString CLASS_NAME;

	static ServiceState networkFormulaServiceState;

	virtual NetworkEnergy getNetworkEnergy(pid_t pid, long duration) = 0;

	virtual void startService() = 0;
	virtual void stopService() = 0;
private:
};

#endif /* NETWORKFORMULASERVICE_H_ */
