
#pragma once

#include <QtWidgets/QWidget>
#include <QtWidgets/QMenu>
#include "WndCell.h"

class CWndCell;
class CWndScreenInner : public QWidget {
	Q_OBJECT

	class CCellEventHandler;
private:
	int					m_nChIdx;					//!< ä�� �ε���( 0 ���� ���� )
	int					m_nDetectAreaNum;			//!< �������� ����
	int					m_nCurAreaIdx;				//!< ���� ���� ���� �������� �ε���(0 ~ AreaNum-1)
	CWndCell			*m_pCell;
	CCellEventHandler	*m_pEventHandler;
	QMenu				m_menu;						//!< �޴�
	//QMenu				m_submenu_detect_area;
	QAction				*m_pAct_Area[10];			//!< �޴� �׸� �ش��ϴ� ���� ����
	QPoint				m_prevPos, m_curPos;		//!< ���� ���� ��ǥ

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

