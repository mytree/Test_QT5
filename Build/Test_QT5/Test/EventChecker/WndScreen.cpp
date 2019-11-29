
#include "../TestBase.h"
#include "WndScreen.h"

#include <QtGui/QGuiApplication>

CWndCell::CWndCell(QWidget *parent) : QLabel(parent) {
	m_nFrameRectR = m_nFrameRectG = m_nFrameRectB = 0; m_nFrameRectA = 255;
}

void CWndCell::SetFrameRectColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
	m_nFrameRectR = r;	m_nFrameRectG = g;	m_nFrameRectB = b;	m_nFrameRectA = a;
	//repaint();
}
void CWndCell::SetTitleText(QString strText) {
	m_strTitleTop = strText;
}

void CWndCell::paintEvent(QPaintEvent *pEvent) {
	Q_UNUSED(pEvent);

	// 영역 계산, 가장자리 남김
	const int BORDER_SIZE = 1;
	QRect rtDraw; rtDraw.setRect(BORDER_SIZE, BORDER_SIZE, width() - (BORDER_SIZE * 2), height() - (BORDER_SIZE * 2));
	if (rtDraw.width() <= 0 || rtDraw.height() <= 0) return;			// 가로/세로 길이 잘 못 되었으면 skip

	QPainter qp(this);
	
	// 배경 이미지 그리기
	QPixmap* pPixmap = const_cast<QPixmap*>(pixmap());
	if (pPixmap) { 
		QPainter qp2(pPixmap);
		//paintTitle(qp2, rtDraw);
		qp.drawPixmap(rtDraw, *pPixmap);
		
	}

	// 영역 테두리 그리기
	QColor frameRectColor(m_nFrameRectR, m_nFrameRectG, m_nFrameRectB, m_nFrameRectA);		// 영역 테두리 색상
	qp.setPen(Qt::SolidLine);		//qp.setBrush(frameRectColor);
	qp.drawRect(rtDraw);	

	paintTitle(qp, rtDraw);
	
}

void CWndCell::paintTitle(QPainter &qp, QRect rtArea) {
	QString strTitle = m_strTitleTop;	// text();
	if (strTitle.size() <= 0) return;

	// 타이틀 글자 그리기
	QFont fontTitle = qp.font();
	fontTitle.setPointSize(20);
	fontTitle.setBold(true);
	qp.setFont(fontTitle);
	qp.setPen(QColor(0, 0, 0));
	
	//QTextOption textOpt;	textOpt.setAlignment(Qt::AlignRight);
	QTextOption textOpt;	textOpt.setAlignment(Qt::AlignLeft);
	QRect rtTitleTop(rtArea);
	int nTitleH = rtTitleTop.height() / 4;	if (nTitleH < 20) nTitleH = 20;
	
	rtTitleTop.setHeight(nTitleH);		qp.drawText(rtTitleTop, strTitle, textOpt);
	rtTitleTop.moveTo(2, 2);			qp.drawText(rtTitleTop, strTitle, textOpt);
	rtTitleTop.moveTo(-1, -1);	qp.setPen(QColor(250, 250, 250));	qp.drawText(rtTitleTop, strTitle, textOpt);

}

//--------------------------------------------------------------------------

//CWndScreen::CWndScreen(QWidget* pParent) : QTableWidget(pParent) {
CWndScreen::CWndScreen(QWidget* pParent) : QWidget(pParent) {
	{
		std::lock_guard<std::mutex> lock(m_chListMutex);
		//QSize parentSize = pParent->size();
		for (int nChIdx = 0; nChIdx < static_cast<int>(ECDivTypeEnum::MAX_DIV); nChIdx++) {
			//std::ostringstream oss; oss << "CH " << nChIdx + 1;
			//CWndCell* pCell = new CWndCell(this);	pCell->setText(oss.str().c_str());
			QString strText = "CH " + QString::number(nChIdx + 1);
			CWndCell* pCell = new CWndCell(this);
			pCell->SetTitleText(strText);
			pCell->hide();
			m_chList.push_back(pCell);
		}
	}
	m_bIsFirstCallDiv = true;
	m_nDivType = ECDivTypeEnum::DIV_1;
	m_nBeginChIdx = 0;

	m_bIsFullScreen = false;

	QRect rtScreen;
	QList<QScreen*> scrList = qApp->screens();
	for (int nIdx = 0; nIdx < scrList.size(); nIdx++) {
		rtScreen = scrList[nIdx]->geometry();
	}

	startTimer(30);
}

CWndScreen::~CWndScreen() {
	
	{
		std::lock_guard<std::mutex> lock(m_chListMutex);
		for (ChIter iter = m_chList.begin(); iter != m_chList.end(); iter++) {
			CWndCell* pCell = static_cast<CWndCell*>(*iter);
			if (pCell) { delete pCell; pCell = nullptr; }
		}
		m_chList.clear();
		for (ImgIter iter = m_imgList.begin(); iter != m_imgList.end(); iter++) {
			delete iter->second;
		}
		m_imgList.clear();
		m_recvList.clear();
	}
}

ECDivTypeEnum CWndScreen::GetDivType() {
	return m_nDivType;
}

void CWndScreen::SetDivision(ECDivTypeEnum nDivType, int nBeginChIdx) {

	std::lock_guard<std::mutex> lock(m_chListMutex);

	int nMaxDiv = static_cast<int>(ECDivTypeEnum::MAX_DIV);
	if (nBeginChIdx < 0 || nBeginChIdx >= nMaxDiv) {
		nBeginChIdx = m_nBeginChIdx;
	}

	// 이전 분할 방식과 동일한 분할 요청이면 skip (단, 처음 호출이면 그냥 진행)
	if (m_bIsFirstCallDiv == false && m_nDivType == nDivType) return;	
	if (m_bIsFirstCallDiv) m_bIsFirstCallDiv = false;

	int nGridIdx = 0, nCIdx = 0, nRIdx = 0;
	CWndCell* pCell = nullptr;

	// 모든 Cell 화면에서 숨김
	ChIter chIter = m_chList.begin();
	ChIter chEIter = m_chList.end();
	for (; chIter != chEIter; chIter++) {
		pCell = static_cast<CWndCell*>(*chIter);	pCell->hide();
	}

	// Table Layout 새로 구성
	int nRowNum = 0, nColNum = 0;
	switch (nDivType) {
	case ECDivTypeEnum::DIV_1:	{ nColNum = nRowNum = 1; break; }
	case ECDivTypeEnum::DIV_4:	{ nColNum = nRowNum = 2; break; }
	case ECDivTypeEnum::DIV_9:	{ nColNum = nRowNum = 3; break; }
	case ECDivTypeEnum::DIV_16:	{ nColNum = nRowNum = 4; break; }
	case ECDivTypeEnum::DIV_24:	{ nColNum = 6; nRowNum = 4; break; }
	default:	return;
	}
	int nCellW = width() / nColNum;
	int nCellH = height() / nRowNum;
	int nGridNum = nColNum * nRowNum;
	int nBeginPos = nBeginChIdx, nEndPos = (nBeginPos + (int)nDivType) % nMaxDiv, nPos = 0;
	for (nGridIdx = 0; nGridIdx < (int)nDivType; nGridIdx++) {
		nCIdx = nGridIdx % nColNum;
		nRIdx = nGridIdx / nColNum;
		nPos = (nBeginPos + nGridIdx) % (int)nMaxDiv;
		pCell = m_chList[nPos];
		pCell->move(nCellW * nCIdx, nCellH * nRIdx);
		pCell->setFixedSize(nCellW, nCellH);
		pCell->setAlignment(Qt::AlignCenter);
		pCell->show();
		//setCellWidget(nRIdx, nCIdx, pCell);
	}

	m_nDivType = nDivType;
	m_nBeginChIdx = nBeginChIdx;
}

bool CWndScreen::SetChImage(int nChIdx, QPixmap* pSrcBuf) {
	// std::lock_guard<std::mutex> lock(m_chListMutex);
	// if (nChIdx < 0 || nChIdx >= static_cast<int>(ECDivTypeEnum::MAX_DIV) || pBuf == nullptr) return false;
	// m_chList[nChIdx]->setPixmap(*pBuf);
	// return true;

	std::lock_guard<std::mutex> lock(m_chListMutex);
	if (nChIdx < 0 || nChIdx >= static_cast<int>(ECDivTypeEnum::MAX_DIV) || pSrcBuf == nullptr) return false;

	// 이미지 추가
	ImgIter imgFIter = m_imgList.find(nChIdx);
	if (imgFIter != m_imgList.end()) {
		QPixmap* pPrevSrc = imgFIter->second;	delete pPrevSrc;	m_imgList.erase(imgFIter);
	}
	QPixmap* pNewBuf = new QPixmap(*pSrcBuf);
	m_imgList.insert(std::make_pair(nChIdx, pNewBuf));

	// 이미지 수신여부 설정
	m_recvList[nChIdx] = true;

	return true;
}

void CWndScreen::resizeEvent(QResizeEvent *event) {
	SetDivision(m_nDivType);
}

void CWndScreen::timerEvent(QTimerEvent *pEvent) {

	{
		std::lock_guard<std::mutex> lock(m_chListMutex);

		QPixmap* pBuf = nullptr;
		int nChIdx = 0, nMaxDiv = static_cast<int>(ECDivTypeEnum::MAX_DIV);
		for (nChIdx = 0; nChIdx < nMaxDiv; nChIdx++) {
			if (m_recvList[nChIdx] == false) continue;		// 수신된 이미지 없으면 skip
			m_recvList[nChIdx] = false;
			pBuf = m_imgList[nChIdx];
			m_chList[nChIdx]->setPixmap(*pBuf);
		}
	}
}

	
