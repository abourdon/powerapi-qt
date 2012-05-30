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
#ifndef LINKSTATE_H_
#define LINKSTATE_H_
#include <sof/util/logging/Logger.h>
#include <QtCore>
#include <QtSql>
#include "../api/NetworkInterface.h"

using sof::util::logging::Logger;

class LinkState {
public:
	static Logger &logger;

	static const QString ACTIVE_1000_STR;
	static const QString ACTIVE_100_STR;
	static const QString ACTIVE_10_STR;
	static const QString IDLE_1000_STR;
	static const QString IDLE_100_STR;
	static const QString IDLE_10_STR;
	static const QString DISCONNECTED_LAN_STR;
	static const QString DISCONNECTED_CABLE_STR;
	static const QString UNKNOWN_STR;

	enum State {
		ACTIVE_1000,
		ACTIVE_100,
		ACTIVE_10,
		IDLE_1000,
		IDLE_100,
		IDLE_10,
		DISCONNECTED_LAN,
		DISCONNECTED_CABLE,
		UNKNOWN
	};

	static const QString SYS_CLASS_INTERFACE_DIRECTORY;

	static QString toString(LinkState::State state);

	LinkState();
	virtual ~LinkState();

	LinkState::State getCurrentLinkStateNow(
			const NetworkInterface &networkInterface);

	float getPowerConsumption(const NetworkInterface & networkInterface,
			const LinkState::State & state);

private:
	QString getCurrentOperstateNow(const QDir &sysClassInterfaceDir);
	int getCurrentSpeedNow(const QDir &sysClassInterfaceDir);
};

#endif /* LINKSTATE_H_ */
