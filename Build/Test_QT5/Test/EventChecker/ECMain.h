
#pragma once

#include "ECUIEvent.h"

#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxlayout>
#include <QtWidgets/QPushButton>

class CWndScreen;
class ECMainWnd : public QWidget {
	Q_OBJECT
private:
	ECUIEvent						*m_pEvent;
	QHBoxLayout						*m_pHBox;
	QVBoxLayout						*m_pVBox;
	QPushButton						*m_pDiv1;
	QPushButton						*m_pDiv4;
	QPushButton						*m_pDiv9;
	QPushButton						*m_pDiv16;
	QPushButton						*m_pDiv24;
	
	CWndScreen						*m_pWndScreen;
	ECDivTypeEnum					m_nDivType;

public:
	ECMainWnd(ECUIEvent* pEvent);
	virtual ~ECMainWnd();

protected:
	void timerEvent(QTimerEvent *pEvent);

private slots:
	void onClick_DIV_1();
	void onClick_DIV_4();
	void onClick_DIV_9();
	void onClick_DIV_16();
	void onClick_DIV_24();
};