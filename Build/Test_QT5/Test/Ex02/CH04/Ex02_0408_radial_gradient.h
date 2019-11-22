
#pragma once

class Ex02_0408_radial_gradient : public QWidget {
public:
	Ex02_0408_radial_gradient(QWidget *parent = 0) : QWidget(parent) {

	}
protected:
	void paintEvent(QPaintEvent *pEvent) {
		Q_UNUSED(pEvent);

		doPainting();
	}
	void doPainting() {
		QPainter painter(this);

		int h = height();
		int w = width();

		QRadialGradient grad1(w / 2, h / 2, 80);

		grad1.setColorAt(0, QColor("#032E91"));
		grad1.setColorAt(0.3, Qt::white);
		grad1.setColorAt(1, QColor("#032E91"));

		painter.fillRect(0, 0, w, h, grad1);
	}
};

class Ex02_0408_radial_gradient_test : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char **ppArgs) {
		QApplication app(nArgNum, ppArgs);

		Ex02_0408_radial_gradient window;

		window.resize(350, 280);
		window.setWindowTitle("Shapes");
		window.show();

		return app.exec();
	}
};
