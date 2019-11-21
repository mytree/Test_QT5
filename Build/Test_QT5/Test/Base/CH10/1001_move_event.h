
#pragma once

#include "../../TestBase.h"

class C1001_MoveEvent : public QWidget {
	Q_OBJECT

private:
	QLabel		*pLB_mouse;
	
public:
	C1001_MoveEvent() {
		resize(500, 500);
		pLB_mouse = new QLabel("Mouse & Key Event Test", this);	pLB_mouse->resize(300, 30);
		//pLB_mouse = new QLabel("Hello World.", this);	pLB_mouse->resize(300, 30);

		setMouseTracking(true);
	}

private:
	//!	@brief	마우스 이동 시 이벤트 처리
	virtual void mouseMoveEvent(QMouseEvent *pEvent) {
		QPoint mousePos = pEvent->pos();
		QString strText = QString("Mouse Moved Pos(%1,%2)").arg(mousePos.x()).arg(mousePos.y());
		pLB_mouse->setText(strText);
	}

	//!	@brief	마우스 눌렀다가 떼었을 때 이벤트 처리
	virtual void mouseReleaseEvent(QMouseEvent *pEvent) {
		QPoint mousePos = pEvent->pos();
		//Qt::MouseButtons btns = pEvent->buttons();
		Qt::MouseButton btn = pEvent->button();
		QString strText = QString("Mouse Released Pos(%1, %2) Type(%3)").arg(mousePos.x()).arg(mousePos.y()).arg(btn);
		pLB_mouse->setText(strText);
	}

	virtual void keyReleaseEvent(QKeyEvent *pEvent) {
		QString strText = QString("Key Released. Code(%1)").arg(pEvent->nativeVirtualKey());
		pLB_mouse->setText(strText);
	}
};

class C1001_TestMoveEvent : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char **ppArgs) {
		QApplication app(nArgNum, ppArgs);
		C1001_MoveEvent *moveEvent = new C1001_MoveEvent();
		moveEvent->show();
		return app.exec();
	}
};