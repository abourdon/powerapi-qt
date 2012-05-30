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
#ifndef CPUENERGY_H_
#define CPUENERGY_H_
#include <sys/types.h>
#include <QtCore>

class CPUEnergy {
public:
	CPUEnergy();
	CPUEnergy(pid_t pid, double watt);
	CPUEnergy(const CPUEnergy &cpuEnergy);
	virtual ~CPUEnergy();

	bool operator==(const CPUEnergy &cpuEnergy);
	bool operator==(const CPUEnergy *cpuEnergy);

	pid_t getPID() const;
	void setPID(pid_t pid);

	double getWatt() const;
	void setWatt(double watt);

	double getPercentageUsage() const;
	void setPercentageUsage(double percentageUsage);
private:
	pid_t pid;
	double watt;
	double percentageUsage;
};

Q_DECLARE_METATYPE(CPUEnergy)

#endif /* CPUENERGY_H_ */
