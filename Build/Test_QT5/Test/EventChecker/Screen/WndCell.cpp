
#include "./WndCell.h"

CWndCell::DrawInfo::DrawInfo() {
	nFrameRectR = nFrameRectG = nFrameRectB = 0; nFrameRectA = 255;
	nTitleTopAlign = nTitleBottomAlign = Qt::AlignmentFlag::AlignLeft;
}

CWndCell::CWndCell(QWidget *parent) : QLabel(parent) {
}

void CWndCell::SetFrameRectColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
	std::lock_guard<std::mutex> lock(m_propMutex);
	m_drawInfo.nFrameRectR = r;
	m_drawInfo.nFrameRectG = g;
	m_drawInfo.nFrameRectB = b;
	m_drawInfo.nFrameRectA = a;
}
void CWndCell::SetTitleTopText(QString strText, Qt::AlignmentFlag nAlign) {
	std::lock_guard<std::mutex> lock(m_propMutex);
	m_drawInfo.strTitleTop = strText;
	m_drawInfo.nTitleTopAlign = nAlign;
}
void CWndCell::SetTitleBottomText(QString strText, Qt::AlignmentFlag nAlign) {
	std::lock_guard<std::mutex> lock(m_propMutex);
	m_drawInfo.strTitleBottom = strText;
	m_drawInfo.nTitleBottomAlign = nAlign;
}

CWndCell::DrawInfo CWndCell::GetDrawInfo() {
	CWndCell::DrawInfo di;
	{
		std::lock_guard<std::mutex> lock(m_propMutex);
		di = m_drawInfo;
	}
	return di;
}

bool CWndCell::SetDrawInfo(CWndCell::DrawInfo& di) {
	std::lock_guard<std::mutex> lock(m_propMutex);
	m_drawInfo.nFrameRectR = di.nFrameRectR;
	m_drawInfo.nFrameRectG = di.nFrameRectG;
	m_drawInfo.nFrameRectB = di.nFrameRectB;
	m_drawInfo.nFrameRectA = di.nFrameRectA;
	m_drawInfo.strTitleTop = di.strTitleTop;
	m_drawInfo.nTitleTopAlign = di.nTitleTopAlign;
	m_drawInfo.strTitleBottom = di.strTitleBottom;
	m_drawInfo.nTitleBottomAlign = di.nTitleBottomAlign;
	return true;
}

void CWndCell::paintEvent(QPaintEvent *pEvent) {
	Q_UNUSED(pEvent);

	// 영역 계산, 가장자리 남김
	const int BORDER_SIZE = 1;
	QRect rtDraw; rtDraw.setRect(BORDER_SIZE, BORDER_SIZE, width() - (BORDER_SIZE * 2), height() - (BORDER_SIZE * 2));
	if (rtDraw.width() <= 0 || rtDraw.height() <= 0) return;			// 가로/세로 길이 잘 못 되었으면 skip

	DrawInfo di;
	{	std::lock_guard<std::mutex> lock(m_propMutex); 	di = m_drawInfo; }

	QColor frameRectColor(di.nFrameRectR, di.nFrameRectG, di.nFrameRectB, di.nFrameRectA);			// 영역 테두리 색상
	QString strTitleTop(di.strTitleTop), strTitleBottom(di.strTitleBottom);							// 상단/하단 문자열
	Qt::AlignmentFlag nTitleTopAlign = di.nTitleTopAlign, nTitleBottomAlign = di.nTitleBottomAlign;	// 상단/하단 문자열 정렬방식

	QPainter qp(this);

	// 배경 이미지 그리기
	QPixmap* pPixmap = const_cast<QPixmap*>(pixmap());
	if (pPixmap) {
		qp.drawPixmap(rtDraw, *pPixmap);
	}

	// 영역 테두리 그리기
	qp.setPen(Qt::SolidLine);		//qp.setBrush(frameRectColor);
	qp.drawRect(rtDraw);

	paintTitleTop(qp, rtDraw, strTitleTop, nTitleTopAlign);
	paintTitleBottom(qp, rtDraw, strTitleTop, nTitleBottomAlign);
}

void CWndCell::paintTitleTop(QPainter &qp, QRect rtArea, QString strTitle, Qt::AlignmentFlag nAlign) {
	if (strTitle.size() <= 0) return;

	// 타이틀 글자 설정
	QFont fontTitle = qp.font();
	fontTitle.setPointSize(20);
	fontTitle.setBold(true);
	qp.setFont(fontTitle);
	qp.setPen(QColor(0, 0, 0));

	QFontMetrics fontMetrics(fontTitle);
	int nFontHeight = fontMetrics.height();

	QTextOption textOpt;
	textOpt.setAlignment(nAlign);

	int nTitleH = nFontHeight + 2;	// if (nTitleH < 20) nTitleH = 20;
	QRect rtTitle;
	rtTitle.setRect(rtArea.x() + 1, 1, rtArea.width(), nTitleH);
	QRect rtBlack1;	rtBlack1.setRect(rtTitle.x() - 1, rtTitle.y() - 1, rtTitle.width(), rtTitle.height());
	QRect rtBlack2;	rtBlack2.setRect(rtTitle.x() + 1, rtTitle.y() + 1, rtTitle.width(), rtTitle.height());

	qp.drawText(rtBlack1, strTitle, textOpt);
	qp.drawText(rtBlack2, strTitle, textOpt);

	qp.setPen(QColor(250, 250, 250));
	qp.drawText(rtTitle, strTitle, textOpt);
}

void CWndCell::paintTitleBottom(QPainter &qp, QRect rtArea, QString strTitle, Qt::AlignmentFlag nAlign) {
	if (strTitle.size() <= 0) return;

	// 타이틀 글자 그리기
	QFont fontTitle = qp.font();
	fontTitle.setPointSize(20);
	fontTitle.setBold(true);
	qp.setFont(fontTitle);
	qp.setPen(QColor(0, 0, 0));

	QFontMetrics fontMetrics(fontTitle);
	int nFontHeight = fontMetrics.height();

	QTextOption textOpt;
	textOpt.setAlignment(nAlign);

	int nTitleH = nFontHeight + 2;	// if (nTitleH < 20) nTitleH = 20;
	QRect rtTitle;
	rtTitle.setRect(rtArea.x() + 1, rtArea.bottom() - nTitleH + 1, rtArea.width(), nTitleH);
	QRect rtBlack1;	rtBlack1.setRect(rtTitle.x() - 1, rtTitle.y() - 1, rtTitle.width(), rtTitle.height());
	QRect rtBlack2;	rtBlack2.setRect(rtTitle.x() + 1, rtTitle.y() + 1, rtTitle.width(), rtTitle.height());

	qp.drawText(rtBlack1, strTitle, textOpt);
	qp.drawText(rtBlack2, strTitle, textOpt);

	qp.setPen(QColor(250, 250, 250));
	qp.drawText(rtTitle, strTitle, textOpt);
}

