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
#ifndef CPUINSPECTOR_H_
#define CPUINSPECTOR_H_
#include <QtCore>
#include <esf-cpu-formula/api/CPUFormulaService.h>
#include <esf-network-formula/api/NetworkFormulaService.h>

class EnergyInspector: public QThread {
public:
	static QList<int> getPids();

	EnergyInspector();
	virtual ~EnergyInspector();

	void setCPUFormulaService(CPUFormulaService * cpuFormulaService);
	void setNetworkFormulaService(
			NetworkFormulaService * networkFormulaService);

	void inspectCPU();
	void inspectNetwork();
private:
	static QMutex pidsMutext;
	static QList<int> pids;

	CPUFormulaService *cpuFormulaService;
	NetworkFormulaService *networkFormulaService;
};

#endif /* ENERGYINSPECTOR_H_ */
