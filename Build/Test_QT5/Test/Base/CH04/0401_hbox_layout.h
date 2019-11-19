
#pragma once

/*

*/

class C0401_HBoxLayout : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char** ppArgs) {
		QApplication app(nArgNum, ppArgs);

		QWidget window;

		QHBoxLayout *HBoxLayout = new QHBoxLayout();
		HBoxLayout->setMargin(0);

		QPushButton *PushButton_1 = new QPushButton();
		PushButton_1->setText("Button1");
		HBoxLayout->addWidget(PushButton_1);

		QPushButton *PushButton_2 = new QPushButton();
		PushButton_2->setText("Button2");
		HBoxLayout->addWidget(PushButton_2);

		QPushButton *PushButton_3 = new QPushButton();
		PushButton_3->setText("Button3");
		HBoxLayout->addWidget(PushButton_3);

		window.setLayout(HBoxLayout);
		window.show();

		return app.exec();
	}
};
