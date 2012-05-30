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
#include <esf-cpu-sensor/api/CPUSensorService.h>
#include "CPUFormulaActivator.h"
#include "../business/CPUFormulaServiceImpl.h"

const QString CPUFormulaActivator::CLASS_NAME("CPUFormulaActivator");

CPUFormulaActivator::CPUFormulaActivator() {
	qRegisterMetaType<CPUEnergy>();
}

CPUFormulaActivator::~CPUFormulaActivator() {
}

void CPUFormulaActivator::start(IBundleContext::ConstPtr context) {
	cpuFormulaService = new CPUFormulaServiceImpl();
	Properties props;
	props.put(ESFBundleUtil::INSTANCE_NAME.toStdString(),
			ESFBundleUtil::FIRST_INSTANCE.toStdString());
	cpuFormulaServiceRegistration = context->registerService(
			CPUFormulaService::CLASS_NAME.toStdString(), cpuFormulaService,
			props);

	cpuSensorServiceTracker = new ServiceTracker(context,
			CPUSensorService::CLASS_NAME.toStdString(), this);
	cpuSensorServiceTracker->startTracking();
}

void CPUFormulaActivator::stop(IBundleContext::ConstPtr context) {
	cpuSensorServiceTracker->stopTracking();
	delete cpuSensorServiceTracker;

	cpuFormulaServiceRegistration->unregister();
	delete cpuFormulaServiceRegistration;

	cpuFormulaService->stopService();
	delete cpuFormulaService;
}

bool CPUFormulaActivator::addingService(const ServiceReference &ref) {
	if (ref.getServiceName() == CPUSensorService::CLASS_NAME.toStdString()) {
		Properties properties(ref.getServiceProperties());
		if (properties.get(ESFBundleUtil::INSTANCE_NAME.toStdString())
				== ESFBundleUtil::FIRST_INSTANCE.toStdString()) {
			((CPUFormulaServiceImpl *) cpuFormulaService)->setCPUSensorService(
					(CPUSensorService *) ref.getService());
			cpuFormulaService->startService();
			return true;
		}
	}
	return false;
}

void CPUFormulaActivator::removedService(const ServiceReference &ref) {
	if (ref.getServiceName() == CPUSensorService::CLASS_NAME.toStdString()) {
		Properties properties(ref.getServiceProperties());
		if (properties.get(ESFBundleUtil::INSTANCE_NAME.toStdString())
				== ESFBundleUtil::FIRST_INSTANCE.toStdString()) {
			cpuFormulaService->stopService();
		}
	}

}

REGISTER_BUNDLE_ACTIVATOR_CLASS( CPUFormulaActivator::CLASS_NAME.toStdString(),
		CPUFormulaActivator)
