
#pragma once

#include "../../TestBase.h"

class QtTabDialog : public QDialog {
	Q_OBJECT
public:
	QtTabDialog(QWidget *parent = 0);

private:
	QTabWidget		*tabwidget;
	QWidget			*tab_1;
	QWidget			*tab_2;
	QWidget			*tab_3;
};

class C0502_TableDialog : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char **ppArgs) {

		QApplication app(nArgNum, ppArgs);

		QtTabDialog dlg;
		dlg.show();

		return app.exec();

	}
};