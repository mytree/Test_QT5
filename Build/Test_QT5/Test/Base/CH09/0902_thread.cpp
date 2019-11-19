
#include "./0902_thread.h"

//-------------------------------------------------------------------------------------------------
//
//	Thread

#define STOP	0
#define PLAY	1

C0902_Thread::C0902_Thread(QObject *obj) {
	m_label = (QLabel*)obj;
	m_stopflag = PLAY;
}

void C0902_Thread::run() {
	for (int count = 0;;) {
		m_mutex.lock();
		if (m_stopflag == STOP) {
			m_waitCondition.wait(&m_mutex);
		}
		m_mutex.unlock();

		m_label->setText(QString("run %1").arg(count++));
		sleep(1);
	}
}

void C0902_Thread::stop() {
	m_stopflag = STOP;
}

void C0902_Thread::resume() {
	m_mutex.lock();
	m_stopflag = PLAY;
	m_waitCondition.wakeAll();
	m_mutex.unlock();
}

//-------------------------------------------------------------------------------------------------
//
//	C0902_ThreadDlg
//

C0902_ThreadDlg::C0902_ThreadDlg(QWidget *parent, Qt::WindowFlags fl) : QWidget(parent, fl) {
	label = new QLabel(this);
	thread = new C0902_Thread(label);
	stopButton = new QPushButton("Stop", this);
	resumeButton = new QPushButton("Resume", this);

	QHBoxLayout *hboxlayout = new QHBoxLayout();
	hboxlayout->addWidget(stopButton);
	hboxlayout->addWidget(resumeButton);

	QVBoxLayout *vboxlayout = new QVBoxLayout();
	vboxlayout->addWidget(label);
	vboxlayout->addLayout(hboxlayout);

	setLayout(vboxlayout);

	connect(stopButton, SIGNAL(clicked()), this, SLOT(stopThread()));
	connect(resumeButton, SIGNAL(clicked()), this, SLOT(resumeThread()));

	thread->start();
}

C0902_ThreadDlg::~C0902_ThreadDlg() {
	thread->wait();
}

void C0902_ThreadDlg::stopThread() {
	thread->stop();
}

void C0902_ThreadDlg::resumeThread() {
	thread->resume();
}
