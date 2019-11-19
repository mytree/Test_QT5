
#pragma once

#include "../../TestBase.h"

/*
	저장하기 정상 동작 안 함
		정확한 원인은 모름
		QMDIArea 에서 잘못된 SubWindow 를 주는 것으로 추정
*/

class C0702_Dir : public QWidget {
	Q_OBJECT

private:
	QDir *directory;
	QListWidget *dirlist;
	QLineEdit *fileName;

public:
	C0702_Dir();

public slots:
	int itemSelected();
	int changeDir();
	int makeDir();
	int removeDir();
	int renameDir();
};

class C0702_TestDir : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char** ppArgs) {
		QApplication app(nArgNum, ppArgs);

		C0702_Dir *dir = new C0702_Dir();
		dir->show();

		return app.exec();
	}
};
