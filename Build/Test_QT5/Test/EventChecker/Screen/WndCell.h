
#pragma once

#include "../../TestBase.h"
#include "../ECType.h"

class CWndCellEvent {
public:
	virtual void OnWndCellPaint(QPainter &qp) {}
	virtual void OnWndCellMouseMove(QPoint &mousePos, Qt::MouseButton &nMouseType) {}
	//virtual void OnWndCellMouseDown(QPoint &mousePos, Qt::MouseButton &nMouseType) {}
	//virtual void OnWndCellMouseUp(QPoint &mousePos, Qt::MouseButton &nMouseType) {}
	//virtual void OnWndCellDoubleClick(QPoint &mousePos, Qt::MouseButton &nMouseType) {}
};

class CWndCell : public QLabel {
	Q_OBJECT

private:
	std::mutex					m_propMutex;
	ECDrawInfo					m_drawInfo;
	CWndCellEvent*				m_pEvent;

public:
	CWndCell(QWidget *parent = nullptr, CWndCellEvent* pEvent = nullptr);
	void SetFrameRectColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);
	void SetTitleTopText(QString strText, Qt::AlignmentFlag nAlign = Qt::AlignmentFlag::AlignLeft);
	void SetTitleBottomText(QString strText, Qt::AlignmentFlag nAlign = Qt::AlignmentFlag::AlignLeft);

	ECDrawInfo GetDrawInfo();
	bool SetDrawInfo(ECDrawInfo& di);

	bool AddAreaPoint(int nAreaIdx, QPoint areaPoint, bool bClosed = false);	//!< ������ �����ϴ� ���� ���� �߰�
	bool ClearArea(int nAreaIdx);												//!< ���� ���� ����
	void ClearAllArea();

	//!	@brief	���� �ε��� �� ���� ����
	//!	@param	nAreaIdx		[in] ���� �ε���(0���� ����)
	//!	@param	areaColor		[in] ���� ����
	void SetAreaColor(int nAreaIdx, QColor &areaColor);

protected:
	inline void setText(const QString &atext) = delete;

private:
	virtual void resizeEvent(QResizeEvent *event) override;
	virtual void paintEvent(QPaintEvent *event) override;
	virtual void mouseMoveEvent(QMouseEvent *event) override;

	void paintTitleTop(QPainter &qp, QRect rtArea, QString strTitle, Qt::AlignmentFlag nAlign);
	void paintTitleBottom(QPainter &qp, QRect rtArea, QString strTitle, Qt::AlignmentFlag nAlign);
	void paintArea(QPainter &qp, QRect rtArea, ECDrawInfo& di);
};
