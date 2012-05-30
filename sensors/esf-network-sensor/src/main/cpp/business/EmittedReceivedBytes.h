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
#ifndef EMITTEDRECEIVEDBYTES_H_
#define EMITTEDRECEIVEDBYTES_H_
#include <sof/util/logging/Logger.h>
#include <QtCore>
#include <sys/types.h>
#include "../api/NetworkInterface.h"
#include "../api/NetworkInterfaceBytes.h"

using sof::util::logging::Logger;

class EmittedReceivedBytes {
public:
	static Logger &logger;

	static const QString DEFAULT_PROC_STAT_FILE_NAME;

	EmittedReceivedBytes();
	virtual ~EmittedReceivedBytes();

	QString getStatFileName() const;
	void setStatFileName(const QString &procNetDevFile);

	NetworkInterfaceBytes getEmittedReceivedNumberOfBytesNow(pid_t pid,
			const NetworkInterface &networkInterface);
private:
	QString statFileName;
};

#endif /* EMITTEDRECEIVEDBYTES_H_ */
