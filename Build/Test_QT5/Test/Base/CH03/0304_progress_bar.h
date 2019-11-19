
#pragma once

class C0304_ProgressBar : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char** ppArgs) {
		QApplication app(nArgNum, ppArgs);

		QProgressBar *Pbar = new QProgressBar();
		Pbar->setValue(2);
		Pbar->show();

		return app.exec();
	}
};