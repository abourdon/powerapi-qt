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
#include <sof/util/logging/LoggerFactory.h>
#include <sof/instantiation/ObjectCreator.h>
#include <esf-core/bundle/ESFBundleUtil.h>
#include "ESFMainActivator.h"

const QString ESFMainActivator::CLASS_NAME("ESFMainActivator");

Logger &ESFMainActivator::logger(LoggerFactory::getLogger("ESFMainActivator"));

ESFMainActivator::ESFMainActivator() :
		cpuFormulaService(0), cpuFormulaServiceTracker(0) {
	resultStorage = new ResultStorage();
	energyInspector = new EnergyInspector();
}

ESFMainActivator::~ESFMainActivator() {
	delete resultStorage;
	delete energyInspector;
}

void ESFMainActivator::start(IBundleContext::ConstPtr context) {
	startCPUFormulaService(context);
	startNetworkFormulaService(context);
}

void ESFMainActivator::startCPUFormulaService(
		IBundleContext::ConstPtr context) {
	cpuFormulaServiceTracker = new ServiceTracker(context,
			CPUFormulaService::CLASS_NAME.toStdString(), this);
	cpuFormulaServiceTracker->startTracking();
}

void ESFMainActivator::startNetworkFormulaService(
		IBundleContext::ConstPtr context) {
	networkFormulaServiceTracker = new ServiceTracker(context,
			NetworkFormulaService::CLASS_NAME.toStdString(), this);
	networkFormulaServiceTracker->startTracking();
}

void ESFMainActivator::stop(IBundleContext::ConstPtr context) {
	stopCPUFormulaService(context);
	stopNetworkFormulaService(context);
}

void ESFMainActivator::stopCPUFormulaService(IBundleContext::ConstPtr context) {
	cpuFormulaService->removeEventListener(resultStorage);
	cpuFormulaServiceTracker->stopTracking();
	delete cpuFormulaServiceTracker;
}

void ESFMainActivator::stopNetworkFormulaService(
		IBundleContext::ConstPtr context) {
	networkFormulaService->removeEventListener(resultStorage);
	networkFormulaServiceTracker->stopTracking();
	delete networkFormulaServiceTracker;
}

bool ESFMainActivator::addingService(const ServiceReference & ref) {
	if (addingCPUFormulaService(ref)) {
		QtConcurrent::run(energyInspector, &EnergyInspector::inspectCPU);
		return true;
	}
	if (addingNetworkFormulaService(ref)) {
		QtConcurrent::run(energyInspector, &EnergyInspector::inspectNetwork);
		return true;
	}
	return false;
}

bool ESFMainActivator::addingCPUFormulaService(const ServiceReference &ref) {
	if (ref.getServiceName() == CPUFormulaService::CLASS_NAME.toStdString()) {
		Properties properties(ref.getServiceProperties());
		if (properties.get(ESFBundleUtil::INSTANCE_NAME.toStdString())
				== ESFBundleUtil::FIRST_INSTANCE.toStdString()) {
			cpuFormulaService = (CPUFormulaService *) ref.getService();
			cpuFormulaService->addEventListener(resultStorage);
			energyInspector->setCPUFormulaService(cpuFormulaService);
			return true;
		}
	}
	return false;
}

bool ESFMainActivator::addingNetworkFormulaService(
		const ServiceReference &ref) {
	if (ref.getServiceName()
			== NetworkFormulaService::CLASS_NAME.toStdString()) {
		Properties properties(ref.getServiceProperties());
		if (properties.get(ESFBundleUtil::INSTANCE_NAME.toStdString())
				== ESFBundleUtil::FIRST_INSTANCE.toStdString()) {
			networkFormulaService = (NetworkFormulaService *) ref.getService();
			networkFormulaService->addEventListener(resultStorage);
			energyInspector->setNetworkFormulaService(networkFormulaService);
			return true;
		}
	}
	return false;
}

void ESFMainActivator::removedService(const ServiceReference & ref) {
	removedCPUFormulaService(ref);
	removedNetworkFormulaService(ref);
}

void ESFMainActivator::removedCPUFormulaService(const ServiceReference &ref) {
	if (ref.getServiceName() == CPUFormulaService::CLASS_NAME.toStdString()) {
		Properties properties(ref.getServiceProperties());
		if (properties.get(ESFBundleUtil::INSTANCE_NAME.toStdString())
				== ESFBundleUtil::FIRST_INSTANCE.toStdString()) {
			cpuFormulaService->removeEventListener(resultStorage);
		}
	}
}

void ESFMainActivator::removedNetworkFormulaService(
		const ServiceReference &ref) {
	if (ref.getServiceName()
			== NetworkFormulaService::CLASS_NAME.toStdString()) {
		Properties properties(ref.getServiceProperties());
		if (properties.get(ESFBundleUtil::INSTANCE_NAME.toStdString())
				== ESFBundleUtil::FIRST_INSTANCE.toStdString()) {
			networkFormulaService->removeEventListener(resultStorage);
		}
	}
}

REGISTER_BUNDLE_ACTIVATOR_CLASS(ESFMainActivator::CLASS_NAME.toStdString(),
		ESFMainActivator)
