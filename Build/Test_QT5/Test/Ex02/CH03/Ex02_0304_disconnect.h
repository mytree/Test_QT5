
#pragma once

#include "../../TestBase.h"

class Ex02_0304_disconnect : public QWidget {
	Q_OBJECT
public:
	Ex02_0304_disconnect(QWidget* parent = 0) : QWidget(parent) {
		QHBoxLayout *hbox = new QHBoxLayout(this);
		hbox->setSpacing(5);

		clickBtn = new QPushButton("Click", this);
		hbox->addWidget(clickBtn, 0, Qt::AlignLeft | Qt::AlignTop);

		QCheckBox *cb = new QCheckBox("Connect", this);
		cb->setCheckState(Qt::Checked);
		hbox->addWidget(cb, 0, Qt::AlignLeft | Qt::AlignTop);

		connect(clickBtn, &QPushButton::clicked, this, &Ex02_0304_disconnect::onClick);
		connect(cb, &QCheckBox::stateChanged, this, &Ex02_0304_disconnect::onCheck);
	}

private slots:
	void onClick() {
		QTextStream out(stdout);
		out << "Button clicked" << endl;
	}
	void onCheck(int state) {
		if (state == Qt::Checked) {
			connect(clickBtn, &QPushButton::clicked, this, &Ex02_0304_disconnect::onClick);
		}
		else {
			disconnect(clickBtn, &QPushButton::clicked, this, &Ex02_0304_disconnect::onClick);
		}

	}

private:
	QPushButton *clickBtn;
};

class Ex02_0304_disconnect_test : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char **ppArgs) {
		QApplication app(nArgNum, ppArgs);

		Ex02_0304_disconnect window;

		window.resize(250, 150);
		window.setWindowTitle("Disconnect");
		window.show();


		return app.exec();

	}
};
