
#pragma once

/*

*/

class C0310_Dial : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char** ppArgs) {
		QApplication app(nArgNum, ppArgs);

		QDial *DI = new QDial();
		DI->setNotchesVisible(true);
		DI->setNotchTarget(10);
		DI->show();

		return app.exec();
	}
};
