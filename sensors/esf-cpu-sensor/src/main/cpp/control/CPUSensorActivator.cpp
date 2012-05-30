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
#include "CPUSensorActivator.h"
#include "../business/CPUSensorServiceImpl.h"
#include <sof/framework/Properties.h>
#include <sof/instantiation/ObjectCreator.h>
#include <esf-core/bundle/ESFBundleUtil.h>

const QString CPUSensorActivator::CLASS_NAME("CPUSensorActivator");

const QString CPUSensorActivator::BUNDLE_NAME("esf_cpu_sensor");

CPUSensorActivator::CPUSensorActivator() {
}

CPUSensorActivator::~CPUSensorActivator() {
}

void CPUSensorActivator::start(IBundleContext::ConstPtr context) {
	cpuSensorService = new CPUSensorServiceImpl();

	Properties props;
	props.put(ESFBundleUtil::INSTANCE_NAME.toStdString(),
			ESFBundleUtil::FIRST_INSTANCE.toStdString());

	cpuSensorServiceRegistration = context->registerService(
			CPUSensorService::CLASS_NAME.toStdString(), cpuSensorService,
			props);
}

void CPUSensorActivator::stop(IBundleContext::ConstPtr context) {
	cpuSensorServiceRegistration->unregister();
	delete cpuSensorServiceRegistration;
	delete cpuSensorService;
}

REGISTER_BUNDLE_ACTIVATOR_CLASS( CPUSensorActivator::CLASS_NAME.toStdString(),
		CPUSensorActivator)

