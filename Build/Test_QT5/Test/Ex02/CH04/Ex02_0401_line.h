
#pragma once

class Ex02_0401_line : public QWidget {
public:
	Ex02_0401_line(QWidget *parent = 0) : QWidget(parent) {

	}
protected:
	void paintEvent(QPaintEvent *pEvent) {
		Q_UNUSED(pEvent);

		QPainter qp(this);
		drawLines(&qp);
	}
	void drawLines(QPainter *qp) {
		QPen pen(Qt::black, 2, Qt::SolidLine);
		qp->setPen(pen);
		qp->drawLine(20, 40, 250, 40);

		pen.setStyle(Qt::DashLine);
		qp->setPen(pen);
		qp->drawLine(20, 80, 250, 80);

		pen.setStyle(Qt::DashDotLine);
		qp->setPen(pen);
		qp->drawLine(20, 120, 250, 120);

		pen.setStyle(Qt::DotLine);
		qp->setPen(pen);
		qp->drawLine(20, 160, 250, 160);

		pen.setStyle(Qt::DashDotDotLine);
		qp->setPen(pen);
		qp->drawLine(20, 200, 250, 200);

		QVector<qreal> dashes;
		qreal space = 4;

		dashes << 1 << space << 5 << space;

		pen.setStyle(Qt::CustomDashLine);
		pen.setDashPattern(dashes);

		qp->setPen(pen);
		qp->drawLine(20, 240, 250, 240);
	}
};

class Ex02_0401_line_test : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char **ppArgs) {
		QApplication app(nArgNum, ppArgs);

		Ex02_0401_line window;

		window.resize(280, 270);
		window.setWindowTitle("Lines");
		window.show();

		return app.exec();
	}
};
