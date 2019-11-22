
#pragma once

class Ex02_0406_shape : public QWidget {
public:
	Ex02_0406_shape(QWidget *parent = 0) : QWidget(parent) {

	}
protected:
	void paintEvent(QPaintEvent *pEvent) {
		Q_UNUSED(pEvent);

		doPainting();
	}
	void doPainting() {
		QPainter painter(this);

		painter.setRenderHint(QPainter::Antialiasing);
		painter.setPen(QPen(QBrush("#888"), 1));
		painter.setBrush(QBrush(QColor("#888")));

		QPainterPath path1;

		path1.moveTo(5, 5);
		path1.cubicTo(40, 5, 50, 50, 99, 99);
		path1.cubicTo(5, 99, 50, 50, 5, 5);
		painter.drawPath(path1);

		painter.drawPie(130, 20, 90, 60, 30 * 16, 120 * 16);
		painter.drawChord(240, 30, 90, 60, 0, 16 * 180);
		painter.drawRoundRect(20, 120, 80, 50);

		QPolygon polygon({ QPoint(130, 140), QPoint(180, 170), QPoint(180, 140),
			QPoint(220, 110), QPoint(140, 100) });

		painter.drawPolygon(polygon);

		painter.drawRect(250, 110, 60, 60);

		QPointF baseline(20, 250);
		QFont font("Georgia", 55);
		QPainterPath path2;
		path2.addText(baseline, font, "Q");
		painter.drawPath(path2);

		painter.drawEllipse(140, 200, 60, 60);
		painter.drawEllipse(240, 200, 90, 60);
	}
};

class Ex02_0406_shape_test : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char **ppArgs) {
		QApplication app(nArgNum, ppArgs);

		Ex02_0406_shape window;

		window.resize(350, 280);
		window.setWindowTitle("Shapes");
		window.show();

		return app.exec();
	}
};
