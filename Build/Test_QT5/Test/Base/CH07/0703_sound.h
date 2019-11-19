
#pragma once

#include <QtMultimedia/QSound>

class C0703_Sound : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char **ppArgs) {
		QApplication app(nArgNum, ppArgs);
		QSound *sound = new QSound("test.wav");
		sound->play();
		return app.exec();
	}
};