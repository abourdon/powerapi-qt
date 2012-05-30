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
#ifndef QTHREADEX_H_
#define QTHREADEX_H_
#include <QtCore>

class QThreadEx: public QThread {
protected:
	void run() {
		exec();
	}
};

#endif /* QTHREADEX_H_ */
