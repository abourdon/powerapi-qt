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
#include <stdlib.h>
#include <string>
#include <iostream>

#include "sof/instantiation/ObjectCreator.h"
#include "sof/framework/IBundleActivator.h"

using namespace std;
using namespace sof::instantiation;
using namespace sof::framework;
using namespace sof::util::logging;

#define DLL extern "C" __attribute__((visibility("default")))

DLL IBundleActivator* createObject(const string &className) {
	ObjectCreator<IBundleActivator> OC_BUNDLE_ACTIVATOR;

	return OC_BUNDLE_ACTIVATOR.createObject(className);
}

