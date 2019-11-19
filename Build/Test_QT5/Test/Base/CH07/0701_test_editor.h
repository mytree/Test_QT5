
#pragma once

#include "../../TestBase.h"

/*
	저장하기 정상 동작 안 함
		정확한 원인은 모름
		QMDIArea 에서 잘못된 SubWindow 를 주는 것으로 추정
*/

class C0701_Editor : public QMainWindow {
	Q_OBJECT

private:
	QMdiArea		*workspace;

public:
	C0701_Editor();

public slots:
	int newFile();
	int openFile();
	int saveFile();
	int showFileInfo();
};

class C0701_TestEditor : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char** ppArgs) {
		QApplication app(nArgNum, ppArgs);

		C0701_Editor *editor = new C0701_Editor();
		editor->show();

		return app.exec();
	}
};
