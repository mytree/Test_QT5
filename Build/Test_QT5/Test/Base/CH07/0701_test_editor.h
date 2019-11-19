
#pragma once

#include "../../TestBase.h"

/*
	�����ϱ� ���� ���� �� ��
		��Ȯ�� ������ ��
		QMDIArea ���� �߸��� SubWindow �� �ִ� ������ ����
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
