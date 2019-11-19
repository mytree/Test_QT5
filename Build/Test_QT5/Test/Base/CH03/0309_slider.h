
#pragma once

/*

*/

class C0309_Slider : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char** ppArgs) {
		QApplication app(nArgNum, ppArgs);

		QSlider *SL = new QSlider(Qt::Horizontal, 0);
		SL->setTickPosition(QSlider::TicksAbove);
		SL->show();

		return app.exec();
	}
};
