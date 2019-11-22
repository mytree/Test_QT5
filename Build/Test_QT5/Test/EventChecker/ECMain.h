
#pragma once

#include "ECUIEvent.h"

class CWndScreen;
class ECMainWnd : public QWidget {
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

};