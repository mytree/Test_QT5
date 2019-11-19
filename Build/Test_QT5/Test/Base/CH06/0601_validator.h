
#pragma once

/*
	QIntValidator �� ���� ������
	QDoubleValidator, QRegExpValidator �� �������� �˻簡 �̷������ ����
*/

#include "../../TestBase.h"

class C0601_Validator : public QWidget {
	Q_OBJECT
private:
	QLabel		*label_double;
	QLabel		*label_int;
	QLabel		*label_regexp;

	QLineEdit	*lineedit_double;
	QLineEdit	*lineedit_int;
	QLineEdit	*lineedit_regexp;

	QDoubleValidator		*doubleValidator;
	QIntValidator			*intValidator;
	QRegExpValidator		*regexpValidator;

public:
	C0601_Validator(QWidget *parent = 0);
};

class C0601_TestValidator : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char** ppArgs) {
		QApplication app(nArgNum, ppArgs);

		C0601_Validator *validator = new C0601_Validator();
		validator->show();

		return app.exec();
	}

};