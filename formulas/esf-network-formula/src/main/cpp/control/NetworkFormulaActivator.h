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
#ifndef NETWORKFORMULAACTIVATOR_H_
#define NETWORKFORMULAACTIVATOR_H_
#include <sof/framework/IBundleActivator.h>
#include <sof/framework/IServiceRegistration.h>
#include <sof/framework/IServiceTrackerCustomizer.h>
#include <sof/framework/ServiceTracker.h>
#include "../api/NetworkFormulaService.h"

using namespace sof::framework;

class NetworkFormulaActivator: public IBundleActivator,
		public IServiceTrackerCustomizer {
public:
	static const QString CLASS_NAME;

	NetworkFormulaActivator();
	virtual ~NetworkFormulaActivator();

	void start(IBundleContext::ConstPtr context);
	void stop(IBundleContext::ConstPtr context);

	bool addingService(const ServiceReference& ref);
	void removedService(const ServiceReference& ref);

private:
	NetworkFormulaService *networkFormulaService;
	IServiceRegistration *networkFormulaServiceRegistration;

	ServiceTracker *networkSensorServiceTracker;
};

#endif /* NETWORKFORMULAACTIVATOR_H_ */
