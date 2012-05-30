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
#ifndef CPUFORMULASERVICE_H_
#define CPUFORMULASERVICE_H_
#include <QtCore>
#include <sof/framework/IService.h>
#include <esf-core/event/EventListenerList.h>
#include <esf-core/bundle/ServiceState.h>
#include "CPUEnergy.h"

using namespace sof::framework;

class CPUFormulaService: public IService, public EventListenerList<CPUEnergy> {
public:
	static ServiceState cpuFormulaServiceState;

	static const QString CLASS_NAME;

	virtual CPUEnergy getCPUEnergy(pid_t pid, int duration) = 0;

	virtual void startService() = 0;
	virtual void stopService() = 0;
};

#endif /* CPUFORMULASERVICE_H_ */
