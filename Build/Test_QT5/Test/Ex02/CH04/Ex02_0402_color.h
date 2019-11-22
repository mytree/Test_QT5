
#pragma once

class Ex02_0402_color : public QWidget {
public:
	Ex02_0402_color(QWidget *parent = 0) : QWidget(parent) {

	}
protected:
	void paintEvent(QPaintEvent *pEvent) {
		Q_UNUSED(pEvent);

		doPainting();
	}
	void doPainting() {
		QPainter painter(this);
		painter.setPen(QColor("#d4d4d4"));

		painter.setBrush(QBrush("#c56c00"));
		painter.drawRect(10, 15, 90, 60);

		painter.setBrush(QBrush("#1ac500"));
		painter.drawRect(130, 15, 90, 60);

		painter.setBrush(QBrush("#539e47"));
		painter.drawRect(250, 15, 90, 60);

		painter.setBrush(QBrush("#004fc5"));
		painter.drawRect(10, 105, 90, 60);

		painter.setBrush(QBrush("#c50024"));
		painter.drawRect(130, 105, 90, 60);

		painter.setBrush(QBrush("#9e4757"));
		painter.drawRect(250, 105, 90, 60);

		painter.setBrush(QBrush("#5f3b00"));
		painter.drawRect(10, 195, 90, 60);

		painter.setBrush(QBrush("#4c4c4c"));
		painter.drawRect(130, 195, 90, 60);

		painter.setBrush(QBrush("#785f36"));
		painter.drawRect(250, 195, 90, 60);
	}
};

class Ex02_0402_color_test : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char **ppArgs) {
		QApplication app(nArgNum, ppArgs);

		Ex02_0402_color window;

		window.resize(360, 280);
		window.setWindowTitle("Colours");
		window.show();

		return app.exec();
	}
};
