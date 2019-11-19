
#pragma once

class C0303_LCD_Number : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char** ppArgs) {
		QApplication app(nArgNum, ppArgs);

		QLCDNumber *lcd = new QLCDNumber();
		lcd->setDecMode();
		lcd->setSegmentStyle(QLCDNumber::Flat);
		lcd->display(2006);
		lcd->show();

		return app.exec();
	}
};