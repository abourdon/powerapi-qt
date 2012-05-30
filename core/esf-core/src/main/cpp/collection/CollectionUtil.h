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
#ifndef COLLECTIONUTIL_H_
#define COLLECTIONUTIL_H_
#include <QtCore>

class CollectionUtil {
public:
	template<class KEY, class VALUE> static void deleteHash(
			QHash<KEY, VALUE *> *hash) {
		if (hash != NULL) {
			foreach(const KEY &key, hash->keys()) {
				if (hash->value(key) != NULL) {
					delete hash->value(key);
				}
			}
			delete hash;
		}
	}
};

#endif /* COLLECTIONUTIL_H_ */
