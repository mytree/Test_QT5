
#pragma once

class C0803_PainterPath : public QWidget {
private:
	QPainter *paint;

public:
	C0803_PainterPath() {
		resize(200, 200);
	}
	void paintEvent(QPaintEvent *pEvent) {
		
		QPainterPath path1;
		path1.setFillRule(Qt::OddEvenFill);		// Default Value
		path1.moveTo(0.0, 100.0);
		path1.cubicTo(21.0, 10.0, 14.0, 52.0, 100.0, 100.0);
		path1.closeSubpath();
		path1.moveTo(20.0, 30.0);
		path1.lineTo(20.0, 80.0);
		path1.lineTo(80.0, 80.0);
		path1.lineTo(80.0, 30.0);
		path1.lineTo(20.0, 30.0);

		QPainterPath path2;
		path2.setFillRule(Qt::WindingFill);
		path2.addRect(120.0, 120.0, 60.0, 60.0);
		path2.addEllipse(100.0, 100.0, 70.0, 70.0);

		paint = new QPainter();
		paint->begin(this);

		paint->setBrush(Qt::blue);
		paint->drawPath(path1);
		paint->setBrush(Qt::green);
		paint->drawPath(path2);

		paint->end();
	}
};

class C0803_TestPainterPath : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char **ppArgs) {
		QApplication app(nArgNum, ppArgs);

		C0803_PainterPath p;
		p.show();

		return app.exec();
	}
};