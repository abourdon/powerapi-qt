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
#ifndef CPUSENSORACTIVATOR_H_
#define CPUSENSORACTIVATOR_H_
#include <sof/framework/IBundleActivator.h>
#include <sof/framework/IBundleContext.h>
#include <sof/framework/IServiceRegistration.h>
#include <QtCore>
#include "../api/CPUSensorService.h"

using namespace sof::framework;

class CPUSensorActivator: public IBundleActivator {
public:
	static const QString CLASS_NAME;
	static const QString BUNDLE_NAME;

	CPUSensorActivator();
	virtual ~CPUSensorActivator();

	void start(IBundleContext::ConstPtr context);
	void stop(IBundleContext::ConstPtr context);

	QMutex getCpuSensorServiceMutex() const;
	void setCpuSensorServiceMutex(QMutex cpuSensorServiceMutex);
private:
	CPUSensorService *cpuSensorService;
	IServiceRegistration *cpuSensorServiceRegistration;
};

#endif /* CPUSENSORACTIVATOR_H_ */
