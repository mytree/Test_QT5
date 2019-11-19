
#pragma once

class C0202_Hello2 : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char** ppArgs) {
		QApplication a(nArgNum, ppArgs);
		QLabel *hello = new QLabel("<font color=blue>Hello<i>Qt!</i>""</font>", 0);
		hello->resize(75, 35);
		hello->show();
		return a.exec();
	}
};
