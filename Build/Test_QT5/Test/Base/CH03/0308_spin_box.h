
#pragma once

/*

*/

class C0308_SpinBox : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char** ppArgs) {
		QApplication app(nArgNum, ppArgs);

		QSpinBox *SP = new QSpinBox();
		SP->setRange(0, 10);
		SP->setWrapping(true);
		SP->setSpecialValueText("Hi");
		SP->show();

		return app.exec();
	}
};
