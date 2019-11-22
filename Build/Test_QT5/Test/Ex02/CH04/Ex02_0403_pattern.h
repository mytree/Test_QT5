
#pragma once

class Ex02_0403_pattern : public QWidget {
public:
	Ex02_0403_pattern(QWidget *parent = 0) : QWidget(parent) {

	}
protected:
	void paintEvent(QPaintEvent *pEvent) {
		Q_UNUSED(pEvent);

		doPainting();
	}
	void doPainting() {
		QPainter painter(this);
		painter.setPen(Qt::NoPen);

		painter.setBrush(Qt::HorPattern);
		painter.drawRect(10, 15, 90, 60);

		painter.setBrush(Qt::VerPattern);
		painter.drawRect(130, 15, 90, 60);

		painter.setBrush(Qt::CrossPattern);
		painter.drawRect(250, 15, 90, 60);

		painter.setBrush(Qt::Dense7Pattern);
		painter.drawRect(10, 105, 90, 60);

		painter.setBrush(Qt::Dense6Pattern);
		painter.drawRect(130, 105, 90, 60);

		painter.setBrush(Qt::Dense5Pattern);
		painter.drawRect(250, 105, 90, 60);

		painter.setBrush(Qt::BDiagPattern);
		painter.drawRect(10, 195, 90, 60);

		painter.setBrush(Qt::FDiagPattern);
		painter.drawRect(130, 195, 90, 60);

		painter.setBrush(Qt::DiagCrossPattern);
		painter.drawRect(250, 195, 90, 60);
	}
};

class Ex02_0403_pattern_test : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char **ppArgs) {
		QApplication app(nArgNum, ppArgs);

		Ex02_0403_pattern window;

		window.resize(350, 280);
		window.setWindowTitle("Patterns");
		window.show();

		return app.exec();
	}
};
