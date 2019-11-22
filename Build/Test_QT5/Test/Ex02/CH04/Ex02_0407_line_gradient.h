
#pragma once

class Ex02_0407_line_gradient : public QWidget {
public:
	Ex02_0407_line_gradient(QWidget *parent = 0) : QWidget(parent) {

	}
protected:
	void paintEvent(QPaintEvent *pEvent) {
		Q_UNUSED(pEvent);

		doPainting();
	}
	void doPainting() {
		QPainter painter(this);

		QLinearGradient grad1(0, 20, 0, 110);

		grad1.setColorAt(0.1, Qt::black);
		grad1.setColorAt(0.5, Qt::yellow);
		grad1.setColorAt(0.9, Qt::black);

		painter.fillRect(20, 20, 300, 90, grad1);

		QLinearGradient grad2(0, 55, 250, 0);

		grad2.setColorAt(0.2, Qt::black);
		grad2.setColorAt(0.5, Qt::red);
		grad2.setColorAt(0.8, Qt::black);

		painter.fillRect(20, 140, 300, 100, grad2);
	}
};

class Ex02_0407_line_gradient_test : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char **ppArgs) {
		QApplication app(nArgNum, ppArgs);

		Ex02_0407_line_gradient window;

		window.resize(350, 280);
		window.setWindowTitle("Shapes");
		window.show();

		return app.exec();
	}
};
