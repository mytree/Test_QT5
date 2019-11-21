
#pragma once

#include "../../TestBase.h"

class Ex02_0303_move : public QWidget {
	Q_OBJECT
public:
	Ex02_0303_move(QWidget* parent = 0) : QWidget(parent) {
	}
protected:
	void moveEvent(QMoveEvent * e) {
		int x = e->pos().x();
		int y = e->pos().y();

		QString text = QString::number(x) + "," + QString::number(y);

		setWindowTitle(text);
	}
};

class Ex02_0303_move_test : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char **ppArgs) {
		QApplication app(nArgNum, ppArgs);

		Ex02_0303_move window;

		window.resize(250, 150);
		window.setWindowTitle("Move");
		window.show();


		return app.exec();

	}
};
