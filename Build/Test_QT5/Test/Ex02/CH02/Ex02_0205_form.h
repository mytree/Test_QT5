
#pragma once

class Ex02_0205_Form : public QWidget {
public:
	Ex02_0205_Form(QWidget *parent = 0) : QWidget(parent) {
		QLineEdit *nameEdit = new QLineEdit(this);
		QLineEdit *addrEdit = new QLineEdit(this);
		QLineEdit *occpEdit = new QLineEdit(this);

		QFormLayout *formLayout = new QFormLayout;
		formLayout->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);
		formLayout->addRow("Name:", nameEdit);
		formLayout->addRow("Email:", addrEdit);
		formLayout->addRow("Age:", occpEdit);

		setLayout(formLayout);

	}
};


class Ex02_0205_Test_Form : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char **ppArgs) {

		QApplication app(nArgNum, ppArgs);

		Ex02_0205_Form window;

		window.setWindowTitle("FormLayout");
		window.show();

		int nRet = app.exec();

		return nRet;
	}
};
