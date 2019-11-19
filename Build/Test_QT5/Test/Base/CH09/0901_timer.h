
#pragma once

#include "../../TestBase.h"

class C0901_Timer : public QWidget {
	Q_OBJECT
private:
	QLabel *clock;
	QTimer *timer;
	QTime time;

public:
	C0901_Timer(QWidget *parent = 0) : QWidget(parent) {
		clock = new QLabel(this);
		clock->resize(80, 20);
		timer = new QTimer(this);
		QObject::connect(timer, SIGNAL(timeout()), SLOT(clockTimer()));
		timer->start(1000);		// 1ÃÊ
		resize(90, 40);
	}

public slots :
	void clockTimer() {
		time = QTime::currentTime();
		QString str = time.toString();
		clock->setText(str);
	}

};

class C0901_TestTimer : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char **ppArgs) {
		QApplication app(nArgNum, ppArgs);
		C0901_Timer *timer = new C0901_Timer();
		timer->show();
		return app.exec();
	}
};