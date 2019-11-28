
#include "../TestBase.h"
#include "WndScreen.h"


CWndCell::CWndCell(QWidget *parent) : QLabel(parent) {
	m_nFrameRectR = m_nFrameRectG = m_nFrameRectB = 0; m_nFrameRectA = 255;
}

void CWndCell::SetFrameRectColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
	m_nFrameRectR = r;	m_nFrameRectG = g;	m_nFrameRectB = b;	m_nFrameRectA = a;
	//repaint();
}

void CWndCell::paintEvent(QPaintEvent *pEvent) {
	Q_UNUSED(pEvent);

	int nX = 1, nY = 1, nW = width() - (nX * 2), nH = height() - (nY * 2);	// 영역 계산, 가장자리 1 pixel 남김
	if (nW <= 0 || nH <= 0) return;											// 가로/세로 길이 잘 못 되었으면 skip

	int nCellW = width(), nCellH = height();
	const QPixmap* pPixmap = pixmap();
	if (pPixmap) {
		pPixmap->scaled(nCellW, nCellH, Qt::KeepAspectRatio);
	}
	QLabel::paintEvent(pEvent);
	QColor frameRectColor(m_nFrameRectR, m_nFrameRectG, m_nFrameRectB, m_nFrameRectA);		// 영역 테두리 색상

	QPainter qp(this);
	qp.setPen(Qt::SolidLine);		//qp.setBrush(frameRectColor);
	qp.drawRect(nX, nY, nW, nH);															// 영역 테두리 그림
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
			pCell->setText(strText);
			pCell->setScaledContents(true);
			pCell->hide();
			m_chList.push_back(pCell);
		}
	}
	m_nDivType = ECDivTypeEnum::DIV_1;

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

void CWndScreen::SetDivision(ECDivTypeEnum nDivType) {

	std::lock_guard<std::mutex> lock(m_chListMutex);

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
	int nMaxDiv = static_cast<int>(ECDivTypeEnum::MAX_DIV);
	int nBeginPos = 0, nEndPos = (nBeginPos + (int)nDivType) % nMaxDiv, nPos = 0;
	for (nGridIdx = 0; nGridIdx < (int)nDivType; nGridIdx++) {
		nCIdx = nGridIdx % nColNum;
		nRIdx = nGridIdx / nColNum;
		nPos = (nBeginPos + nGridIdx) % (int)nDivType;
		pCell = m_chList[nPos];
		pCell->move(nCellW * nCIdx, nCellH * nRIdx);
		pCell->setFixedSize(nCellW, nCellH);
		pCell->setAlignment(Qt::AlignCenter);
		pCell->show();
		//setCellWidget(nRIdx, nCIdx, pCell);
	}

	m_nDivType = nDivType;
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