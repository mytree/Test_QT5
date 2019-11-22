
#pragma once

class Ex02_0404_transparent : public QWidget {
public:
	Ex02_0404_transparent(QWidget *parent = 0) : QWidget(parent) {

	}
protected:
	void paintEvent(QPaintEvent *pEvent) {
		Q_UNUSED(pEvent);

		doPainting();
	}
	void doPainting() {
		QPainter painter(this);
		for (int i = 1; i <= 11; i++) {
			painter.setOpacity(i*0.1);
			painter.fillRect(50 * i, 20, 40, 40, Qt::darkGray);
		}
	}
};

class Ex02_0404_transparent_test : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char **ppArgs) {
		QApplication app(nArgNum, ppArgs);

		Ex02_0404_transparent window;

		window.resize(630, 90);
		window.setWindowTitle("Transparent rectangles");
		window.show();

		return app.exec();
	}
};
