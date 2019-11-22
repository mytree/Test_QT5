
#pragma once

class Ex02_0409_puff : public QWidget {
private:
	int x;
	qreal opacity;
	int timerId;

public:
	Ex02_0409_puff(QWidget *parent = 0) : QWidget(parent) {
		x = 1;
		opacity = 1.0;
		timerId = startTimer(15);
	}
protected:
	void timerEvent(QTimerEvent *e) {
		Q_UNUSED(e);
		x += 1;
		repaint();
	}

	void paintEvent(QPaintEvent *pEvent) {
		Q_UNUSED(pEvent);

		doPainting();
	}
	void doPainting() {
		QPainter painter(this);
		QTextStream out(stdout);

		QString text = "ZetCode";

		painter.setPen(QPen(QBrush("#575555"), 1));

		QFont font("Courier", x, QFont::DemiBold);
		QFontMetrics fm(font);
		int textWidth = fm.width(text);

		painter.setFont(font);

		if (x > 10) {
			opacity -= 0.01;
			painter.setOpacity(opacity);
		}

		if (opacity <= 0) {
			killTimer(timerId);
			out << "timer stopped" << endl;
		}

		int h = height();
		int w = width();

		painter.translate(QPoint(w / 2, h / 2));
		painter.drawText(-textWidth / 2, 0, text);

	}
};

class Ex02_0409_puff_test : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char **ppArgs) {
		QApplication app(nArgNum, ppArgs);

		Ex02_0409_puff window;

		window.resize(350, 280);
		window.setWindowTitle("Shapes");
		window.show();

		return app.exec();
	}
};
