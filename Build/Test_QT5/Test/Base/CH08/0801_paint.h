
#pragma once

class C0801_Paint : public QWidget {
private:
	QPainter *paint;

public:
	C0801_Paint() {
		resize(200, 200);
	}

private:
	void paintEvent(QPaintEvent *pEvent) {
		paint = new QPainter();
		paint->begin(this);
		
		//paint->setPen(QPen(Qt::blue, 4, Qt::DashLine));	paint->drawPoint(100, 100);			// �� ���
		//paint->setPen(QPen(Qt::blue, 10, Qt::DashLine));	paint->drawLine(20, 20, 160, 160);	// �� �׸���
		//paint->setPen(QPen(Qt::blue, 5, Qt::SolidLine));	paint->drawRect(20, 20, 160, 160);	// �簢�� �׸���
		//paint->setPen(QPen(Qt::blue, 5, Qt::SolidLine));	paint->drawRoundedRect(20, 20, 160, 160, 20, 20);	// �ձ� �簢��
		//paint->setPen(QPen(Qt::blue, 5, Qt::DotLine));	paint->drawArc(20, 20, 160, 160, 30 * 16, 160 * 16);// ȣ �׸���
		//paint->setPen(QPen(Qt::blue, 5, Qt::SolidLine));	paint->drawChord(20, 20, 160, 160, 30 * 16, 150 * 16);// �� �׸���
		//paint->setPen(QPen(Qt::blue, 5, Qt::SolidLine));	paint->drawPie(20, 20, 160, 160, 50 * 16, 130 * 16); // Pie �׸���
		//paint->setPen(QPen(Qt::blue, 5, Qt::SolidLine));	paint->drawEllipse(20, 20, 140, 170);	// Ÿ�� �׸���
		//paint->setPen(QPen(Qt::blue, 5, Qt::SolidLine));	paint->drawEllipse(20, 20, 170, 170);	// Ÿ�� �׸���

		// Polygon �׸���
		QVector<QPoint> points = {
			QPoint(20, 20), QPoint(20, 90), QPoint(90, 80), QPoint(80, 160), QPoint(160, 80), QPoint(80, 20) };
		QPolygon polygon(points);
		paint->setPen(QPen(Qt::blue, 5, Qt::SolidLine));
		paint->drawPolygon(polygon, Qt::OddEvenFill);

		paint->end();
	}
};


class C0801_TestPaint : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char **ppArgs) {
		QApplication app(nArgNum, ppArgs);
		C0801_Paint p;
		p.show();
		return app.exec();
	}
};