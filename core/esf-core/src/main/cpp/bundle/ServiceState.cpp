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
#include "ServiceState.h"

using sof::util::logging::LoggerFactory;

Logger &ServiceState::logger(LoggerFactory::getLogger("ServiceState"));

ServiceState::ServiceState() :
		alive(false) {
	lock = new QMutex();
}

ServiceState::~ServiceState() {
	delete lock;
}

bool ServiceState::isAlive() const {
	if (lock->tryLock()) {
		logger.log(Logger::LOG_DEBUG,
				"be careful, your isAlive() call is not thread safe");
	}
	return alive;
}

void ServiceState::setAlive(bool alive) {
	if (!lock->tryLock()) {
		this->alive = alive;
	} else {
		logger.log(Logger::LOG_DEBUG,
				"be careful, your setAlive(bool) call is not thread safe");
	}
}

QMutex *ServiceState::getLock() {
	return lock;
}

