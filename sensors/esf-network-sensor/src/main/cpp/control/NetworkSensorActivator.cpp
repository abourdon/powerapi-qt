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
#include <sof/framework/Properties.h>
#include <sof/instantiation/ObjectCreator.h>
#include <esf-core/bundle/ESFBundleUtil.h>
#include "NetworkSensorActivator.h"
#include "../business/NetworkSensorServiceImpl.h"

const QString NetworkSensorActivator::CLASS_NAME("NetworkSensorActivator");

const QString NetworkSensorActivator::BUNDLE_NAME("esf_network_sensor");

NetworkSensorActivator::NetworkSensorActivator() {
}

NetworkSensorActivator::~NetworkSensorActivator() {
}

void NetworkSensorActivator::start(IBundleContext::ConstPtr context) {
	networkSensorService = new NetworkSensorServiceImpl();

	Properties props;
	props.put(ESFBundleUtil::INSTANCE_NAME.toStdString(),
			ESFBundleUtil::FIRST_INSTANCE.toStdString());

	networkSensorServiceRegistration = context->registerService(
			NetworkSensorService::CLASS_NAME.toStdString(),
			networkSensorService, props);
}

void NetworkSensorActivator::stop(IBundleContext::ConstPtr context) {
	networkSensorServiceRegistration->unregister();
	delete networkSensorServiceRegistration;
	delete networkSensorService;
}

REGISTER_BUNDLE_ACTIVATOR_CLASS(
		NetworkSensorActivator::CLASS_NAME.toStdString(),
		NetworkSensorActivator)
