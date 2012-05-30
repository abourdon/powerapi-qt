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
#ifndef CPUTRANSITION_H_
#define CPUTRANSITION_H_
#include <QtCore>
#include <sof/util/logging/Logger.h>

using namespace sof::util::logging;

class CPUTransition {
public:
	static Logger &logger;

	CPUTransition();
	virtual ~CPUTransition();

	long getTotalTransitionsNow();

	QString getTotalTransFile() const;
	void setTotalTransFile(QString totalTransFile);

private:
	long getTotalTransitionsNow(int cpu);

	QString totalTransFile;
};

#endif /* CPUTRANSITION_H_ */
