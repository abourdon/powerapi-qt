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
#ifndef EVENTLISTENERLIST_H_
#define EVENTLISTENERLIST_H_
#include "EventListener.h"

template<class T>
class EventListenerList {
public:
	EventListenerList() :
			listeners() {
	}

	virtual ~EventListenerList() {
		listeners.clear();
	}

	void addEventListener(EventListener<T> *listener) {
		listeners.insert(listener);
	}

	void removeEventListener(EventListener<T> *listener) {
		listeners.remove(listener);
	}

	void removeEventListeners() {
		listeners.clear();
	}

	void fireEvent(const T &event) {
		foreach(EventListener<T> *listener, listeners) {
			listener->eventUpdated(event);
		}
	}

private:
	QSet<EventListener<T> *> listeners;
};

#endif /* EVENTLISTENERLIST_H_ */
