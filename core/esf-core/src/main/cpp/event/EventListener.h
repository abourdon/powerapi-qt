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
#ifndef EVENTLISTENER_H_
#define EVENTLISTENER_H_
#include <QtCore>

template<class T>
class EventListener {
public:
	EventListener() : id(this) {
	}

	virtual ~EventListener() {
	}

	virtual void eventUpdated(const T &) {
		// Need to be overloaded
	}

	template<class U>
	friend bool operator==(const EventListener<U> &first,
			const EventListener<U> &second);

	template<class U>
	friend uint qHash(const EventListener<U> &key);

private:
	EventListener *id;
};

template<class T>
inline bool operator==(const EventListener<T> &first,
		const EventListener<T> &second) {
	return first.id == second.id;
}

template<class T>
inline uint qHash(const EventListener<T> &key) {
	return qHash(QString::number((uint) key.id));
}

#endif /* EVENTLISTENER_H_ */
