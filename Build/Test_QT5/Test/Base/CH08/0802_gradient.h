
#pragma once

class C0802_Gradient : public QWidget {
private:
	QPainter *paint;

public:
	C0802_Gradient() {
		resize(200, 200);
	}
	void paintEvent(QPaintEvent *pEvent) {
		
		QLinearGradient gradient(0, 0, 100, 180);
		gradient.setColorAt(0.0, Qt::red);
		gradient.setColorAt(1.0, Qt::green);

		QRadialGradient gradient2(102, 102, 85);
		gradient2.setColorAt(0.0, Qt::red);
		gradient2.setColorAt(0.5, Qt::blue);
		gradient2.setColorAt(1.0, Qt::green);

		paint = new QPainter();
		paint->begin(this);

		//paint->setBrush(gradient);				// Linear Gradient
		paint->setBrush(gradient2);				// Radial Gradient
		paint->drawEllipse(20, 20, 170, 170);

		paint->end();
	}
};

class C0802_TestGradient : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char **ppArgs) {
		QApplication app(nArgNum, ppArgs);

		C0802_Gradient p;
		p.show();

		return app.exec();
	}
};