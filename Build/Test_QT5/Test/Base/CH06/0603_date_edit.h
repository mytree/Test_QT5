
#pragma once

class C0603_DateEdit : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char **ppArgs) {
		QApplication app(nArgNum, ppArgs);

		QDate date;
		QDateEdit *dateEdit = new QDateEdit(0);
		dateEdit->setDate(date.currentDate());
		dateEdit->show();
		
		return app.exec();
	}
};