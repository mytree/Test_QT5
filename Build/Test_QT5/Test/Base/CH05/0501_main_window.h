
#pragma once

#include "../../TestBase.h"

class C0501_QtEditor : public QMainWindow {
	Q_OBJECT

public:
	C0501_QtEditor();

	public slots:
	int newFile();

};

class C0501_MainWindow : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char** ppArgs) {
		QApplication app(nArgNum, ppArgs);

		C0501_QtEditor *qteditor = new C0501_QtEditor();
		qteditor->show();

		return app.exec();
	}
};
