
#pragma once

#include "../../TestBase.h"

/*
	�����ϱ� ���� ���� �� ��
		��Ȯ�� ������ ��
		QMDIArea ���� �߸��� SubWindow �� �ִ� ������ ����
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
