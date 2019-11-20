
#pragma once

#ifdef __linux__
class C0805_TestSVG : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char **ppArgs) {
		return -1;
	}
};

#else
#include <QtSvg/QSvgWidget>
#include <QtSvg/QSvgRenderer>

class C0805_SVG : public QWidget {
private:
	QSvgWidget		*svgw;

public:
	C0805_SVG(const QString fileName) {
		resize(300, 300);
		svgw = new QSvgWidget(fileName);
	}

	void paintEvent(QPaintEvent *) {
		QImage buffer = QImage(size(), QImage::Format_ARGB32_Premultiplied);
		QPainter paint(&buffer);
		paint.setViewport(0, 0, width(), height());
		paint.eraseRect(0, 0, width(), height());

		svgw->renderer()->render(&paint);
		QPainter pt(this);
		pt.drawImage(0, 0, buffer);
	}
};

class C0805_TestSVG : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char **ppArgs) {

		QApplication app(nArgNum, ppArgs);
		C0805_SVG p(ppArgs[1]);
		p.show();
		return app.exec();
	}
};

#endif
