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
#ifndef ENERGY_H_
#define ENERGY_H_
#include <sys/types.h>
#include <QtCore>

class Energy {
public:
	Energy();
	Energy(pid_t pid);
	virtual ~Energy();
	Energy(const Energy &energy);

	pid_t getPid() const;
	void setPid(pid_t pid);

private:
	pid_t pid;
};

Q_DECLARE_METATYPE(Energy);

#endif /* ENERGY_H_ */
