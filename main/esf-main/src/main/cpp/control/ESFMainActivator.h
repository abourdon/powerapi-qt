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
#ifndef ESFMAINACTIVATOR_H_
#define ESFMAINACTIVATOR_H_
#include <sof/framework/IBundleActivator.h>
#include <sof/framework/IServiceTrackerCustomizer.h>
#include <sof/framework/ServiceTracker.h>
#include <sof/util/logging/Logger.h>
#include <esf-cpu-formula/api/CPUFormulaService.h>
#include <esf-network-formula/api/NetworkFormulaService.h>
#include "../business/ResultStorage.h"
#include "../business/EnergyInspector.h"

using namespace sof::framework;
using namespace sof::util::logging;

class ESFMainActivator: public IBundleActivator,
		public IServiceTrackerCustomizer {
public:
	static Logger &logger;

	static const QString CLASS_NAME;

	ESFMainActivator();
	virtual ~ESFMainActivator();

	void start(IBundleContext::ConstPtr context);
	void stop(IBundleContext::ConstPtr context);

	bool addingService(const ServiceReference &ref);
	void removedService(const ServiceReference &ref);

private:
	void startCPUFormulaService(IBundleContext::ConstPtr context);
	void startNetworkFormulaService(IBundleContext::ConstPtr context);

	void stopCPUFormulaService(IBundleContext::ConstPtr context);
	void stopNetworkFormulaService(IBundleContext::ConstPtr context);

	bool addingCPUFormulaService(const ServiceReference &ref);
	bool addingNetworkFormulaService(const ServiceReference &ref);

	void removedCPUFormulaService(const ServiceReference &ref);
	void removedNetworkFormulaService(const ServiceReference &ref);

	CPUFormulaService *cpuFormulaService;
	ServiceTracker *cpuFormulaServiceTracker;

	NetworkFormulaService *networkFormulaService;
	ServiceTracker *networkFormulaServiceTracker;

	EnergyInspector *energyInspector;

	ResultStorage *resultStorage;
};

#endif /* ESFMAINACTIVATOR_H_ */
