
#pragma once

class Ex02_0301_click : public QWidget {
public:
	Ex02_0301_click(QWidget* parent = 0) : QWidget(parent) {
		QHBoxLayout *hbox = new QHBoxLayout(this);
		hbox->setSpacing(5);

		QPushButton *quitBtn = new QPushButton("Quit", this);
		hbox->addWidget(quitBtn, 0, Qt::AlignLeft | Qt::AlignTop);

		connect(quitBtn, &QPushButton::clicked, qApp, &QApplication::quit);
	}
};

class Ex02_0301_click_test : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char **ppArgs) {
		QApplication app(nArgNum, ppArgs);

		Ex02_0301_click window;

		window.resize(250, 150);
		window.setWindowTitle("Click");
		window.show();

		return app.exec();

	}
};
