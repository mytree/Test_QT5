
#pragma once

class Ex02_0202_VBoxLayout : public QWidget {

public:
	Ex02_0202_VBoxLayout(QWidget *parent = 0) : QWidget(parent) {
		QVBoxLayout *vbox = new QVBoxLayout(this);
		vbox->setSpacing(1);

		QPushButton *settings = new QPushButton("Settings", this);
		settings->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		QPushButton *accounts = new QPushButton("Accounts", this);
		accounts->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		QPushButton *loans = new QPushButton("Loans", this);
		loans->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		QPushButton *cash = new QPushButton("Cash", this);
		cash->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		QPushButton *debts = new QPushButton("Debts", this);
		debts->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

		vbox->addWidget(settings);
		vbox->addWidget(accounts);
		vbox->addWidget(loans);
		vbox->addWidget(cash);
		vbox->addWidget(debts);

		setLayout(vbox);

	}
};


class Ex02_0202_Test_VBoxLayout : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char **ppArgs) {

		QApplication app(nArgNum, ppArgs);

		Ex02_0202_VBoxLayout window;

		window.resize(240, 230);
		window.setWindowTitle("VerticalBox");
		window.show();

		int nRet = app.exec();

		return nRet;
	}
};
