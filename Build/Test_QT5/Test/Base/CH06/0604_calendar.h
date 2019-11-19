
#pragma once

class C0604_Calendar : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char **ppArgs) {
		QApplication app(nArgNum, ppArgs);

		QDate date;
		QCalendarWidget *calendar = new QCalendarWidget();
		calendar->setSelectedDate(date.currentDate());
		calendar->show();
		
		return app.exec();
	}
};