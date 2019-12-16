
#pragma once

#include "../../TestBase.h"

class CWndCell : public QLabel {
	Q_OBJECT
public:
	struct DrawInfo {
		unsigned char				nFrameRectR;
		unsigned char				nFrameRectG;
		unsigned char				nFrameRectB;
		unsigned char				nFrameRectA;
		QString						strTitleTop;
		Qt::AlignmentFlag			nTitleTopAlign;
		QString						strTitleBottom;
		Qt::AlignmentFlag			nTitleBottomAlign;

		DrawInfo();
	};

private:
	std::mutex					m_propMutex;
	DrawInfo					m_drawInfo;

public:
	CWndCell(QWidget *parent = nullptr);
	void SetFrameRectColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);
	void SetTitleTopText(QString strText, Qt::AlignmentFlag nAlign = Qt::AlignmentFlag::AlignLeft);
	void SetTitleBottomText(QString strText, Qt::AlignmentFlag nAlign = Qt::AlignmentFlag::AlignLeft);

	CWndCell::DrawInfo GetDrawInfo();
	bool SetDrawInfo(CWndCell::DrawInfo& di);

protected:
	inline void setText(const QString &atext) = delete;

private:
	virtual void paintEvent(QPaintEvent *event) override;

	void paintTitleTop(QPainter &qp, QRect rtArea, QString strTitle, Qt::AlignmentFlag nAlign);
	void paintTitleBottom(QPainter &qp, QRect rtArea, QString strTitle, Qt::AlignmentFlag nAlign);
};
