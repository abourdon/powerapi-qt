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
#include <sof/instantiation/ObjectCreator.h>
#include <esf-core/bundle/ESFBundleUtil.h>
#include <esf-network-sensor/api/NetworkSensorService.h>
#include "../business/NetworkFormulaServiceImpl.h"
#include "NetworkFormulaActivator.h"

const QString NetworkFormulaActivator::CLASS_NAME("NetworkFormulaActivator");

NetworkFormulaActivator::NetworkFormulaActivator() {
	qRegisterMetaType<NetworkEnergy>();
}

NetworkFormulaActivator::~NetworkFormulaActivator() {
}

void NetworkFormulaActivator::start(IBundleContext::ConstPtr context) {
	networkFormulaService = new NetworkFormulaServiceImpl();
	Properties props;
	props.put(ESFBundleUtil::INSTANCE_NAME.toStdString(),
			ESFBundleUtil::FIRST_INSTANCE.toStdString());
	networkFormulaServiceRegistration = context->registerService(
			NetworkFormulaService::CLASS_NAME.toStdString(),
			networkFormulaService, props);

	networkSensorServiceTracker = new ServiceTracker(context,
			NetworkSensorService::CLASS_NAME.toStdString(), this);
	networkSensorServiceTracker->startTracking();
}

void NetworkFormulaActivator::stop(IBundleContext::ConstPtr context) {
	networkSensorServiceTracker->stopTracking();
	delete networkSensorServiceTracker;

	networkFormulaServiceRegistration->unregister();
	delete networkFormulaServiceRegistration;

	networkFormulaService->stopService();
	delete networkFormulaService;
}

bool NetworkFormulaActivator::addingService(const ServiceReference & ref) {
	if (ref.getServiceName()
			== NetworkSensorService::CLASS_NAME.toStdString()) {
		Properties properties(ref.getServiceProperties());
		if (properties.get(ESFBundleUtil::INSTANCE_NAME.toStdString())
				== ESFBundleUtil::FIRST_INSTANCE.toStdString()) {
			((NetworkFormulaServiceImpl *) networkFormulaService)->setNetworkSensorService(
					(NetworkSensorService *) ref.getService());
			networkFormulaService->startService();
			return true;
		}
	}
	return false;
}

void NetworkFormulaActivator::removedService(const ServiceReference & ref) {
	if (ref.getServiceName()
			== NetworkSensorService::CLASS_NAME.toStdString()) {
		Properties properties(ref.getServiceProperties());
		if (properties.get(ESFBundleUtil::INSTANCE_NAME.toStdString())
				== ESFBundleUtil::FIRST_INSTANCE.toStdString()) {
			networkFormulaService->stopService();
		}
	}
}

REGISTER_BUNDLE_ACTIVATOR_CLASS(
		NetworkFormulaActivator::CLASS_NAME.toStdString(),
		NetworkFormulaActivator)
