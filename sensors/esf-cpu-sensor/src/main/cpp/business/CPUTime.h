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
#ifndef CPUTIME2_H_
#define CPUTIME2_H_
#include <QString>
#include <QDir>
#include <sof/util/logging/Logger.h>

using namespace sof::util::logging;

class CPUTime {
public:
	static Logger &logger;

	static const QString DEFAULT_CGROUP_REPOSITORY;

	CPUTime();
	virtual ~CPUTime();

	double getElapsedTimeNow();
	double getElapsedTimeNow(pid_t pid);

	QString getCgroupRepository() const;
	void setCgroupRepository(QString cgroupRepository);

private:
	QDir cgroupRepository;
};

#endif /* CPUTIME2_H_ */
