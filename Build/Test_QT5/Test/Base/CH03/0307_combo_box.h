
#pragma once

/*

*/

class C0307_ComboBox : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char** ppArgs) {
		QApplication app(nArgNum, ppArgs);

		QComboBox *CB = new QComboBox();
		CB->addItem("KDE");
		CB->addItem("Gnome");
		CB->addItem("FVWM");
		CB->addItem("CDE");
		CB->setEditable(true);
		CB->setCurrentIndex(1);
		CB->show();

		return app.exec();
	}
};