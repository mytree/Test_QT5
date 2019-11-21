
#pragma once

class Ex02_0203_Buttons : public QWidget {
private:
	QPushButton *okBtn;
	QPushButton *applyBtn;

public:
	Ex02_0203_Buttons(QWidget *parent = 0) : QWidget(parent) {
		QVBoxLayout *vbox = new QVBoxLayout(this);
		QHBoxLayout *hbox = new QHBoxLayout();

		okBtn = new QPushButton("OK", this);
		applyBtn = new QPushButton("Apply", this);

		hbox->addWidget(okBtn, 1, Qt::AlignRight);
		hbox->addWidget(applyBtn, 0);

		vbox->addStretch(1);
		vbox->addLayout(hbox);
	}
};


class Ex02_0203_Test_Buttons : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char **ppArgs) {

		QApplication app(nArgNum, ppArgs);

		Ex02_0203_Buttons window;

		window.resize(290, 170);
		window.setWindowTitle("Buttons");
		window.show();

		int nRet = app.exec();

		return nRet;
	}
};
