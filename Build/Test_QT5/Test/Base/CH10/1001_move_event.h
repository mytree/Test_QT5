
/*
	윈도우에서 moveEvent() 호출 안 됨
*/

#pragma once

#include "../../TestBase.h"

class C1001_MoveEvent : public QWidget {
	Q_OBJECT

private:
	QLabel		*label;

public:
	C1001_MoveEvent() {
		resize(500, 500);
		label = new QLabel("Hello World", this);
	}

private:
	void moveEvent(C1001_MoveEvent*) {
		label->setText(QString("X : %1, Y : %2").arg(pos().x()).arg(pos().y()));
	}
};

class C1001_TestMoveEvent : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char **ppArgs) {
		QApplication app(nArgNum, ppArgs);
		C1001_MoveEvent *moveEvent = new C1001_MoveEvent();
		moveEvent->show();
		return app.exec();
	}
};