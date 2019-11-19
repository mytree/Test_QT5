
#pragma once

/*

*/

class C0306_LineEdit : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char** ppArgs) {
		QApplication app(nArgNum, ppArgs);

		QLineEdit *LE = new QLineEdit(0);
		LE->setEchoMode(QLineEdit::Password);
		LE->show();

		return app.exec();
	}
};