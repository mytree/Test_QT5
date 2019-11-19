
#pragma once

/*

*/

class C0404_StackedLayout : public ITestObject {
public:
	class STACKEDLAYOUT : public QWidget {
	private:
		QHBoxLayout		*HBoxLayout;
		QStackedLayout	*StackedLayout;
		QDial			*Dial;
		QLabel			*Label_1;
		QLabel			*Label_2;
		QLabel			*Label_3;

	public:
		STACKEDLAYOUT() {
			Dial = new QDial();
			Dial->setRange(0, 2);
			Dial->setNotchesVisible(true);
			
			Label_1 = new QLabel("Stack 1");
			Label_2 = new QLabel("Stack 2");
			Label_3 = new QLabel("Stack 3");

			StackedLayout = new QStackedLayout();
			StackedLayout->addWidget(Label_1);
			StackedLayout->addWidget(Label_2);
			StackedLayout->addWidget(Label_3);

			HBoxLayout = new QHBoxLayout();
			HBoxLayout->addWidget(Dial);
			HBoxLayout->addLayout(StackedLayout);

			setLayout(HBoxLayout);

			connect(Dial, SIGNAL(valueChanged(int)), StackedLayout, SLOT(setCurrentIndex(int)));
		}
	};
	virtual int OnTest(int nArgNum, char** ppArgs) {
		QApplication app(nArgNum, ppArgs);

		STACKEDLAYOUT StackedLayoutWindow;
		StackedLayoutWindow.show();

		return app.exec();
	}
};
