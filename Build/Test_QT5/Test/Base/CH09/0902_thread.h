
#pragma once

#include "../../TestBase.h"

class C0902_Thread : public QThread {
	Q_OBJECT
private:
	QLabel				*m_label;
	QWaitCondition		m_waitCondition;
	QMutex				m_mutex;
	qint32				m_stopflag;

public:
	C0902_Thread(QObject *obj);
	void stop();
	void resume();
	
private:
	void run();

};

class C0902_ThreadDlg : public QWidget {
	Q_OBJECT

private:
	C0902_Thread	*thread;
	QLabel			*label;
	QPushButton		*stopButton;
	QPushButton		*resumeButton;

public:
	C0902_ThreadDlg(QWidget *parent = 0, Qt::WindowFlags fl = 0);
	~C0902_ThreadDlg();

public slots:
	void stopThread();
	void resumeThread();

};

class C0902_TestThread : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char **ppArgs) {
		QApplication app(nArgNum, ppArgs);

		C0902_ThreadDlg *thread = new C0902_ThreadDlg();
		thread->show();

		return app.exec();
	}
};