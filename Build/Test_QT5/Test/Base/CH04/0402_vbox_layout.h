
#pragma once

/*

*/

class C0402_VBoxLayout : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char** ppArgs) {
		QApplication app(nArgNum, ppArgs);

		QWidget window;

		QVBoxLayout *VBoxLayout = new QVBoxLayout();
		VBoxLayout->setSpacing(6);

		QPushButton *PushButton_1 = new QPushButton();
		PushButton_1->setText("Button1");
		VBoxLayout->addWidget(PushButton_1);

		QPushButton *PushButton_2 = new QPushButton();
		PushButton_2->setText("Button2");
		VBoxLayout->addWidget(PushButton_2);

		QPushButton *PushButton_3 = new QPushButton();
		PushButton_3->setText("Button3");
		VBoxLayout->addWidget(PushButton_3);

		window.setLayout(VBoxLayout);
		window.show();

		return app.exec();
	}
};
