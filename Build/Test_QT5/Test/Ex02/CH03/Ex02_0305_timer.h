
#pragma once

class Ex02_0305_timer : public QWidget {
public:
	Ex02_0305_timer(QWidget* parent = 0) : QWidget(parent) {
		QHBoxLayout *hbox = new QHBoxLayout(this);
		hbox->setSpacing(5);

		label = new QLabel("", this);
		hbox->addWidget(label, 0, Qt::AlignLeft | Qt::AlignTop);

		QTime qtime = QTime::currentTime();
		QString stime = qtime.toString();
		label->setText(stime);

		startTimer(1000);
	}
protected:
	void timerEvent(QTimerEvent *e) {
		Q_UNUSED(e);

		QTime qtime = QTime::currentTime();
		QString stime = qtime.toString();
		label->setText(stime);
	}

private:
	QLabel *label;

};

class Ex02_0305_timer_test : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char **ppArgs) {
		QApplication app(nArgNum, ppArgs);

		Ex02_0305_timer window;

		window.resize(250, 150);
		window.setWindowTitle("Timer");
		window.show();

		return app.exec();

	}
};
