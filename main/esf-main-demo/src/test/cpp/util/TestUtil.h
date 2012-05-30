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
#ifndef TESTUTIL_H_
#define TESTUTIL_H_
#include <QtCore>

#define PROJECT_TESTING_BINARY_DIR "/home/abourdon/dev/esf/esf-lib/main/esf-main-demo-build/testing_launchers"

class TestUtil {
public:
	static const QString getAbsoluteTestingPath();
};

inline const QString TestUtil::getAbsoluteTestingPath() {
	return PROJECT_TESTING_BINARY_DIR;
}

#endif /* TESTUTIL_H_ */
