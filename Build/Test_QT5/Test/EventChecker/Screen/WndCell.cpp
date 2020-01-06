
#include "./WndCell.h"

CWndCell::CWndCell(QWidget *parent, CWndCellEvent* pEvent) : QLabel(parent), m_pEvent(pEvent) {
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

ECDrawInfo CWndCell::GetDrawInfo() {
	ECDrawInfo di;
	{
		std::lock_guard<std::mutex> lock(m_propMutex);
		di = m_drawInfo;
	}
	return di;
}

bool CWndCell::SetDrawInfo(ECDrawInfo& di) {
	std::lock_guard<std::mutex> lock(m_propMutex);
	m_drawInfo.nFrameRectR = di.nFrameRectR;
	m_drawInfo.nFrameRectG = di.nFrameRectG;
	m_drawInfo.nFrameRectB = di.nFrameRectB;
	m_drawInfo.nFrameRectA = di.nFrameRectA;
	m_drawInfo.strTitleTop = di.strTitleTop;
	m_drawInfo.nTitleTopAlign = di.nTitleTopAlign;
	m_drawInfo.strTitleBottom = di.strTitleBottom;
	m_drawInfo.nTitleBottomAlign = di.nTitleBottomAlign;

	m_drawInfo.canvasSize = di.canvasSize;
	m_drawInfo.lineList = di.lineList;
	m_drawInfo.lineColorList = di.lineColorList;
	return true;
}

//!	@brief	영역을 구성하는 정점 정보 추가
bool CWndCell::AddAreaPoint(int nAreaIdx, QPoint areaPoint, bool bClosed) {
	if (nAreaIdx < 0) return false;
	if (areaPoint.x() < 0 || areaPoint.y() < 0) return false;
	std::lock_guard<std::mutex> lock(m_propMutex);
	ECPolylineIter fIter = m_drawInfo.lineList.find(nAreaIdx);				// 영역 인덱스 검사
	if (fIter == m_drawInfo.lineList.end()) {								// 해당 영역 없으면 새로 추가
		ECPointList pointList;
		m_drawInfo.lineList.insert(std::make_pair(nAreaIdx, pointList));
		fIter = m_drawInfo.lineList.find(nAreaIdx);
	}
	fIter->second.push_back(areaPoint);										// 정점 추가
	size_t pointNum = fIter->second.size();									// 영역을 구성하는 정점 개수 조사
	const int nMaxPointNum = 30;
	if (pointNum > nMaxPointNum) {											// 일정 개수 이상일 경우
		int nDeleteNum = (bClosed) ? pointNum - nMaxPointNum - 1 : pointNum - nMaxPointNum;
		for (int nIdx = 0; nIdx < nDeleteNum; nIdx++)
			fIter->second.erase(fIter->second.begin());							// 제일 오래된 정점 제거
	}
	if (bClosed) {															// true 일 경우 처음 정점을 추가, 닫힌 polygon 을 만듦
		QPoint firstPos = *fIter->second.begin();
		fIter->second.push_back(firstPos);
	}
	return true;
}

//!	@brief	영역 정보 제거
bool CWndCell::ClearArea(int nAreaIdx) {
	std::lock_guard<std::mutex> lock(m_propMutex);
	ECPolylineIter fIter = m_drawInfo.lineList.find(nAreaIdx);				// 영역 인덱스 검사
	if (fIter == m_drawInfo.lineList.end()) {								// 해당 영역 없으면 skip
		return false;
	}
	m_drawInfo.lineList.erase(fIter);										// 검색된 목록 제거
	return true;
}

void CWndCell::ClearAllArea() {
	std::lock_guard<std::mutex> lock(m_propMutex);
	m_drawInfo.lineList.clear();
}

//!	@brief	영역 인덱스 별 색상 정의
//!	@param	nAreaIdx		[in] 영역 인덱스(0부터 시작)
//!	@param	areaColor		[in] 영역 색상
void CWndCell::SetAreaColor(int nAreaIdx, QColor &areaColor) {
	std::lock_guard<std::mutex> lock(m_propMutex);
	m_drawInfo.lineColorList[nAreaIdx] = areaColor;
}

void CWndCell::mouseMoveEvent(QMouseEvent *pEvent) {
	QPoint mousePos = pEvent->pos();
	Qt::MouseButton nMouseType = pEvent->button();
	//qDebug("[MouseMove] Pos(%d, %d) ", mousePos.x(), mousePos.y());

	if (m_pEvent) {
		m_pEvent->OnWndCellMouseMove(mousePos, nMouseType);
	}
}

//!	@brief	화면 크기 변경 시 이벤트 처리
void CWndCell::resizeEvent(QResizeEvent *pEvent) {
}

void CWndCell::paintEvent(QPaintEvent *pEvent) {
	Q_UNUSED(pEvent);

	// 영역 계산, 가장자리 남김
	const int BORDER_SIZE = 1;
	QRect rtDraw; rtDraw.setRect(BORDER_SIZE, BORDER_SIZE, width() - (BORDER_SIZE * 2), height() - (BORDER_SIZE * 2));
	if (rtDraw.width() <= 0 || rtDraw.height() <= 0) return;			// 가로/세로 길이 잘 못 되었으면 skip

	ECDrawInfo di;
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

	// 전체 영역 테두리 그리기
	qp.setPen(Qt::SolidLine);		//qp.setBrush(frameRectColor);
	qp.drawRect(rtDraw);

	// 상,하 Title 그리기
	paintTitleTop(qp, rtDraw, strTitleTop, nTitleTopAlign);
	paintTitleBottom(qp, rtDraw, strTitleTop, nTitleBottomAlign);

	// 설정영역 그리기
	paintArea(qp, pEvent->rect(), di);

	if (m_pEvent) {
		m_pEvent->OnWndCellPaint(qp);
	}
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

void CWndCell::paintArea(QPainter &qp, QRect rtArea, ECDrawInfo& di) {
	int nAreaIdx = -1, nPointNum = 0;
	int nAreaW = rtArea.width(), nAreaH = rtArea.height();							// 그리기 영역 좌표
	int nCanvasW = di.canvasSize.width(), nCanvasH = di.canvasSize.height();		// OSD 좌표 기준 크기
	bool bIsSetCanvasSize = (nCanvasW > 0 && nCanvasH > 0);							// 크기가 설정 되었는지 여부
	
	ECPolylineIter bIter = di.lineList.begin();
	ECPolylineIter eIter = di.lineList.end();
	ECPointIter eIter2, iter2;
	ECAreaColorIter colorIter;
	QPoint pos1, pos2;
	QColor lineColor, defColor = QColor(0, 0, 0);
	for (ECPolylineIter iter = bIter; iter != eIter; iter++) {
		nAreaIdx = iter->first;
		nPointNum = iter->second.size();
		if (nPointNum <= 1) continue;
		colorIter = di.lineColorList.find(nAreaIdx);
		lineColor = (colorIter == di.lineColorList.end()) ? defColor : colorIter->second;
		iter2 = iter->second.begin();
		eIter2 = iter->second.end();
		pos1 = (bIsSetCanvasSize == false) ? *iter2 : GetRatioPos(di.canvasSize, *iter2, rtArea.size());
		iter2++;
		while (iter2 != eIter2) {
			pos2 = (bIsSetCanvasSize == false) ? *iter2 : GetRatioPos(di.canvasSize, *iter2, rtArea.size());
			qp.setPen(lineColor);
			qp.drawLine(pos1, pos2);
			pos1 = pos2;
			iter2++;
		}
	}
}

//!	@brief	비율값 계산( A : B = C : ?, ? = B * C / A ), A 가 0 이면 0 반환
int CWndCell::GetRatio(int nA, int nB, int nC) {
	if (nA == 0) return 0;	// X = ( B * C ) / A, A 가 0 이면 예외 발생함
	int nRet = (nB * nC) / (1.0 * nA);
	return nRet;
}

//!	@brief	비율에 맞는 위치 계산
QPoint CWndCell::GetRatioPos(QSize size1, QPoint pos, QSize size2) {
	QPoint retPos;
	retPos.setX(GetRatio(size1.width(), pos.x(), size2.width()));
	retPos.setY(GetRatio(size1.height(), pos.y(), size2.height()));
	return retPos;
}
