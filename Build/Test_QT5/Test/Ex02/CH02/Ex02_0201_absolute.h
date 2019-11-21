
#pragma once

class Ex02_0201_Absolute : public QWidget {

public:
	Ex02_0201_Absolute(QWidget *parent = 0);
};

Ex02_0201_Absolute::Ex02_0201_Absolute(QWidget *parent) : QWidget(parent) {

	QTextEdit *ledit = new QTextEdit(this);
	ledit->setGeometry(5, 5, 200, 150);
};

class Ex02_0201_Test_Absolute : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char **ppArgs) {

		QApplication app(nArgNum, ppArgs);

		Ex02_0201_Absolute window;

		window.setWindowTitle("Absolute");
		window.show();

		int nRet = app.exec();

		return nRet;
	}
};
