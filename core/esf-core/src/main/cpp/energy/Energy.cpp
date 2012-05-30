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
#include "Energy.h"

Energy::Energy(pid_t pid) :
		pid(pid) {
}

Energy::~Energy() {
}

pid_t Energy::getPid() const {
	return pid;
}

void Energy::setPid(pid_t pid) {
	this->pid = pid;
}

Energy::Energy() :
		pid(-1) {
}

Energy::Energy(const Energy & energy) {
	pid = energy.pid;
}

