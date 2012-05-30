#ifndef TESTUTIL_H_
#define TESTUTIL_H_
#include <QtCore>

#define PROJECT_TESTING_BINARY_DIR "/home/abourdon/dev/esf/esf-lib/core/esf-core-build/testing_launchers"

class TestUtil {
public:
	static const QString getAbsoluteTestingPath();
};

inline const QString TestUtil::getAbsoluteTestingPath() {
	return PROJECT_TESTING_BINARY_DIR;
}

#endif /* TESTUTIL_H_ */
