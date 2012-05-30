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
#ifndef THREADEDLAUNCHER_H_
#define THREADEDLAUNCHER_H_
#include <QtCore>

class ThreadedLauncher: public QThread {
Q_OBJECT
public:
	ThreadedLauncher();
	virtual ~ThreadedLauncher();

	void run();

	int getArgc() const;
	char **getArgv() const;

	void setArgc(int argc);
	void setArgv(char **argv);

public slots:
	void launch();
private:
	int argc;
	char **argv;
};

#endif /* THREADEDLAUNCHER_H_ */
