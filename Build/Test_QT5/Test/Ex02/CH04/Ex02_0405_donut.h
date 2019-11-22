
#pragma once

class Ex02_0405_donut : public QWidget {
public:
	Ex02_0405_donut(QWidget *parent = 0) : QWidget(parent) {

	}
protected:
	void paintEvent(QPaintEvent *pEvent) {
		Q_UNUSED(pEvent);

		doPainting();
	}
	void doPainting() {
		QPainter painter(this);

		painter.setPen(QPen(QBrush("#535353"), 0.5));
		painter.setRenderHint(QPainter::Antialiasing);

		int h = height();
		int w = width();

		painter.translate(QPoint(w / 2, h / 2));

		for (qreal rot = 0; rot < 360.0; rot += 5.0) {
			painter.drawEllipse(-125, -40, 250, 80);
			painter.rotate(5.0);
		}
	}
};

class Ex02_0405_donut_test : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char **ppArgs) {
		QApplication app(nArgNum, ppArgs);

		Ex02_0405_donut window;

		window.resize(350, 280);
		window.setWindowTitle("Donut");
		window.show();

		return app.exec();
	}
};
