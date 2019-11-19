
#pragma once

/*

*/

class C0406_Splitter : public ITestObject {
public:
	class CTestWindow : public QWidget {
	private:
		QLabel		*Label_1;
		QLabel		*Label_2;
		QLabel		*Label_3;
		QSplitter	*Splitter;
	public:
		CTestWindow() {
			Label_1 = new QLabel("Button1");
			Label_2 = new QLabel("Button2");
			Label_3 = new QLabel("Button3");
			Splitter = new QSplitter();
			Splitter->addWidget(Label_1);
			Splitter->addWidget(Label_2);
			Splitter->addWidget(Label_3);
		}
	};
	virtual int OnTest(int nArgNum, char** ppArgs) {
		QApplication app(nArgNum, ppArgs);

		//CTestWindow win;
		//win.show();

		QLabel *Label_1 = new QLabel("Button1");
		QLabel *Label_2 = new QLabel("Button2");
		QLabel *Label_3 = new QLabel("Button3");
		QSplitter *Splitter = new QSplitter();
		Splitter->addWidget(Label_1);
		Splitter->addWidget(Label_2);
		Splitter->addWidget(Label_3);
		Splitter->show();

		return app.exec();
	}
};
