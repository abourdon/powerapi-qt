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
#ifndef SERVICESTATE_H_
#define SERVICESTATE_H_
#include <sof/util/logging/Logger.h>
#include <QtCore>

using sof::util::logging::Logger;

class ServiceState {
public:
	static Logger &logger;

	ServiceState();
	virtual ~ServiceState();

	bool isAlive() const;
	void setAlive(bool alive);

	QMutex *getLock();
private:
	bool alive;
	QMutex *lock;
};

#endif /* SERVICESTATE_H_ */
