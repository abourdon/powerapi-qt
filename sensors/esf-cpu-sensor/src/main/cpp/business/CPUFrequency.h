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
#ifndef CPUFREQUENCY_H_
#define CPUFREQUENCY_H_
#include <QtCore>
#include <sof/util/logging/Logger.h>

using namespace sof::util::logging;

class CPUFrequency {
public:
	static Logger &logger;

	CPUFrequency();
	virtual ~CPUFrequency();

	QHash<int, int> getTimeInFrequencyNow();

	QString getTimeInStateFileName() const;
	void setTimeInStateFileName(QString timeInStateFileName);

private:
	static void addTo(QHash<int, int> &out, const QHash<int, int> &in);

	QHash<int, int> getTimeInFrequencyNow(int cpu);

	QString timeInStateFileName;
};

#endif /* CPUFREQUENCY_H_ */
