
#pragma once

#include <QtWidgets/QWidget>
#include <QtWidgets/QMenu>
#include "WndCell.h"

class CWndCell;
class CWndScreenInner : public QWidget {
	Q_OBJECT

	class CCellEventHandler;
private:
	int					m_nChIdx;					//!< 채널 인덱스( 0 부터 시작 )
	int					m_nDetectAreaNum;			//!< 검지영역 개수
	int					m_nCurAreaIdx;				//!< 현재 설정 중인 검지영역 인덱스(0 ~ AreaNum-1)
	CWndCell			*m_pCell;
	CCellEventHandler	*m_pEventHandler;
	QMenu				m_menu;						//!< 메뉴
	//QMenu				m_submenu_detect_area;
	QAction				*m_pAct_Area[10];			//!< 메뉴 항목에 해당하는 동작 관리
	QPoint				m_prevPos, m_curPos;		//!< 영역 설정 좌표

public:
	CWndScreenInner(QWidget *pParent = nullptr, int nAreaNum = 2);
	virtual ~CWndScreenInner();

	bool SetChImage(int nChIdx, QPixmap *pBuf);
	int GetChIdx();

	bool SetDrawInfo(CWndCell& wndCell);

protected:
	virtual void resizeEvent(QResizeEvent *pEvent) override;
	virtual void mousePressEvent(QMouseEvent *pEvent) override;
	virtual void mouseReleaseEvent(QMouseEvent *pEvent) override;
	virtual void mouseDoubleClickEvent(QMouseEvent *pEvent) override;

protected slots:
	void customMenuRequested(QPoint pos);

private:
	void OnLButtonDown(QPoint mousePos);
	void OnLButtonUp(QPoint mousePos);
	void OnLButtonDoubleClick(QPoint mousePos);
	void OnMouseMove(QPoint mousePos, Qt::MouseButton nMouseType);
	void OnPaint(QPainter& qp);

	void SetUI_DetectArea(bool bIsBegin);
};

