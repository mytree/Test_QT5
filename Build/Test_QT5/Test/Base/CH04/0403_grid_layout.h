
#pragma once

/*

*/

class C0403_GridLayout : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char** ppArgs) {
		QApplication app(nArgNum, ppArgs);

		QWidget window;

		QPushButton *PushButton_1 = new QPushButton();	PushButton_1->setText("Button1");
		QPushButton *PushButton_2 = new QPushButton();	PushButton_2->setText("Button2");
		QPushButton *PushButton_3 = new QPushButton();	PushButton_3->setText("Button3");
		QPushButton *PushButton_4 = new QPushButton();	PushButton_4->setText("Button4");
		QPushButton *PushButton_5 = new QPushButton();	PushButton_5->setText("Button5");
		QPushButton *PushButton_6 = new QPushButton();	PushButton_6->setText("Button6");
		QPushButton *PushButton_7 = new QPushButton();	PushButton_7->setText("Button7");
		QPushButton *PushButton_8 = new QPushButton();	PushButton_8->setText("Button8");
		QPushButton *PushButton_9 = new QPushButton();	PushButton_9->setText("Button9");

		QGridLayout *GridLayout = new QGridLayout();
		GridLayout->addWidget(PushButton_1, 0, 0);
		GridLayout->addWidget(PushButton_2, 0, 1);
		GridLayout->addWidget(PushButton_3, 0, 2);
		GridLayout->addWidget(PushButton_4, 1, 0);
		GridLayout->addWidget(PushButton_5, 1, 1);
		GridLayout->addWidget(PushButton_6, 1, 2);
		GridLayout->addWidget(PushButton_7, 2, 0);
		GridLayout->addWidget(PushButton_8, 2, 1);
		GridLayout->addWidget(PushButton_9, 2, 2);

		window.setLayout(GridLayout);
		window.show();

		return app.exec();
	}
};
