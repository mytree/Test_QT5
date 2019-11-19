
#pragma once

class C0602_DateTimeEdit : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char **ppArgs) {
		QApplication app(nArgNum, ppArgs);

		QDateTime datetime;
		QDateTimeEdit *dateTimeEdit = new QDateTimeEdit(0);
		dateTimeEdit->setDateTime(datetime.currentDateTime());
		dateTimeEdit->show();
		
		return app.exec();
	}
};