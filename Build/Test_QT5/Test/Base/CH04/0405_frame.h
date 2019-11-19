
#pragma once

/*

*/

class C0405_Frame : public ITestObject {
public:
	class CTestWindow : public QWidget {
	private:
		QFrame *PlainLine;
		QFrame *RaisedLine;
		QFrame *SunkenLine;
	public:
		CTestWindow() {
			PlainLine = new QFrame(this);
			PlainLine->setGeometry(QRect(0, 0, 270, 16));
			PlainLine->setFrameShadow(QFrame::Plain);
			PlainLine->setLineWidth(2);
			PlainLine->setFrameShape(QFrame::HLine);
			PlainLine->setFrameStyle(QFrame::HLine | QFrame::Sunken);
			PlainLine->setFrameShape(QFrame::HLine);
			
			RaisedLine = new QFrame(this);
			RaisedLine->setGeometry(QRect(0, 10, 270, 16));
			RaisedLine->setFrameShadow(QFrame::Raised);
			RaisedLine->setLineWidth(2);
			RaisedLine->setFrameShape(QFrame::HLine);
			RaisedLine->setFrameStyle(QFrame::HLine | QFrame::Sunken);
			RaisedLine->setFrameShape(QFrame::HLine);
			
			SunkenLine = new QFrame(this);
			SunkenLine->setGeometry(QRect(0, 20, 270, 16));
			SunkenLine->setFrameShadow(QFrame::Sunken);
			SunkenLine->setLineWidth(2);
			SunkenLine->setFrameShape(QFrame::HLine);
			SunkenLine->setFrameStyle(QFrame::HLine | QFrame::Sunken);
			SunkenLine->setFrameShape(QFrame::HLine);
		}
	};
	virtual int OnTest(int nArgNum, char** ppArgs) {
		QApplication app(nArgNum, ppArgs);

		CTestWindow win;
		win.show();

		return app.exec();
	}
};
