
#include "WndScreen.h"
#include "./WndCell.h"
#include "./WndScreenInner.h"

#include <QtGui/QGuiApplication>


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
			//pCell->SetTitleTopText(strText, Qt::AlignmentFlag::AlignRight);
			pCell->SetTitleTopText(strText);
			pCell->SetTitleBottomText(strText, Qt::AlignmentFlag::AlignRight);
			pCell->hide();
			m_chList.push_back(pCell);
		}
	}
	m_bIsFirstCallDiv = true;
	m_bIsResized = true;
	m_nDivType = ECDivTypeEnum::DIV_1;
	m_nBeginChIdx = 0;

	// ��ũ�� ���� ����
	//QRect rtScreen;
	//QList<QScreen*> scrList = qApp->screens();
	//for (int nIdx = 0; nIdx < scrList.size(); nIdx++) {
	//	rtScreen = scrList[nIdx]->geometry();
	//}

	m_pWndInner = new CWndScreenInner(this);

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

	if (m_pWndInner) {
		delete m_pWndInner;	m_pWndInner = nullptr;
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

	// ���� ���� ��İ� ������ ���� ��û�̸� skip (��, ó�� ȣ���̸� �׳� ����)
	if (m_bIsFirstCallDiv == false && m_bIsResized == false && m_nDivType == nDivType && nBeginChIdx == m_nBeginChIdx) return;
	if (m_bIsFirstCallDiv) m_bIsFirstCallDiv = false;
	if (m_bIsResized) m_bIsResized = false;

	int nGridIdx = 0, nCIdx = 0, nRIdx = 0;
	CWndCell* pCell = nullptr;

	// ��� Cell ȭ�鿡�� ����
	ChIter chIter = m_chList.begin();
	ChIter chEIter = m_chList.end();
	for (; chIter != chEIter; chIter++) {
		pCell = static_cast<CWndCell*>(*chIter);	pCell->hide();
	}

	// Table Layout ���� ����
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
		pCell->update();
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

	// �̹��� �߰�
	ImgIter imgFIter = m_imgList.find(nChIdx);
	if (imgFIter != m_imgList.end()) {
		QPixmap* pPrevSrc = imgFIter->second;	delete pPrevSrc;	m_imgList.erase(imgFIter);
	}
	QPixmap* pNewBuf = new QPixmap(*pSrcBuf);
	m_imgList.insert(std::make_pair(nChIdx, pNewBuf));

	// �̹��� ���ſ��� ����
	m_recvList[nChIdx] = true;

	return true;
}

void CWndScreen::resizeEvent(QResizeEvent *event) {
	m_bIsResized = true;
	SetDivision(m_nDivType);
}

void CWndScreen::timerEvent(QTimerEvent *pEvent) {

	{
		std::lock_guard<std::mutex> lock(m_chListMutex);

		QPixmap* pBuf = nullptr;
		int nInnerIdx = m_pWndInner->GetChIdx();
		int nChIdx = 0, nMaxDiv = static_cast<int>(ECDivTypeEnum::MAX_DIV);
		for (nChIdx = 0; nChIdx < nMaxDiv; nChIdx++) {
			if (m_recvList[nChIdx] == false) continue;		// ���ŵ� �̹��� ������ skip
			m_recvList[nChIdx] = false;
			pBuf = m_imgList[nChIdx];
			m_chList[nChIdx]->setPixmap(*pBuf);

			if (m_pWndInner->isVisible() == false) continue;
			if (nChIdx != nInnerIdx) continue;
			m_pWndInner->SetChImage(nChIdx, pBuf);			// �̹��� ����
		}
	}
}

void CWndScreen::mouseDoubleClickEvent(QMouseEvent *pEvent) {
	
	int nFindChIdx = -1;
	bool bIsChExist = false;
	QPoint mousePos = pEvent->pos();
	QRect rtCh;
	CWndCell* pCell = nullptr;

	{	// ���콺 ��ġ�� ���� ä�� �ε��� ���
		std::lock_guard<std::mutex> lock(m_chListMutex);
		int nChIdx = -1;
		int nDivNum = static_cast<int>(m_nDivType);					// ���� ���� ��
		int nMaxDiv = static_cast<int>(ECDivTypeEnum::MAX_DIV);		// �ִ� ���� ��
		for (int nDivIdx = 0; nDivIdx < nDivNum; nDivIdx++) {		// ���� ���� �� ��ŭ �ݺ�
			nChIdx = (m_nBeginChIdx + nDivIdx) % nMaxDiv;			// ���� ä�� �ε���
			pCell = m_chList[nChIdx];								// ä�� �ε����� �´� ���� ä�� ȭ��
			rtCh = pCell->geometry();								// ä�� ȭ�� ����
			if (rtCh.contains(mousePos) == false) continue;			// ä�� ȭ�� ������ ���콺 ��ġ�� �����ϴ��� Ȯ��
			bIsChExist = true;
			nFindChIdx = nChIdx;
			break;
		}
	}
	if (bIsChExist == false) return;						// ������ ȭ�鿡 ä���� �������� ������ skip

	//if (bIsChExist == false) qDebug("X(%d) Y(%d)", mousePos.x(), mousePos.y());
	//else qDebug("X(%d) Y(%d) CH(%d)", mousePos.x(), mousePos.y(), nFindChIdx + 1);

	if (m_pWndInner) {
		std::ostringstream oss;	oss << "ä�� " << nFindChIdx + 1;
		m_pWndInner->setWindowTitle(QString::fromLocal8Bit(oss.str().c_str()));
		
		{
			std::lock_guard<std::mutex> lock(m_chListMutex);
			QPixmap* pBuf = m_imgList[nFindChIdx];
			if (pBuf) {
				m_pWndInner->SetChImage(nFindChIdx, pBuf);
			}
			if (pCell) {
				m_pWndInner->SetDrawInfo(*pCell);				// �ش� Cell �� ������ �׸� ���� ����
			}
		}
		m_pWndInner->resize(640, 480);
		m_pWndInner->show();
		m_pWndInner->setFocus();
	}

	//if (m_pWndInner) {
	//	//m_pWndInner->resize(640, 480);

	//	QRect rtScreen;
	//	QList<QScreen*> scrList = qApp->screens();				// ��ũ�� ���� ����
	//	if (scrList.size() > 0) { rtScreen = scrList[0]->geometry(); }
	//	
	//	QWidget* pParent = static_cast<QWidget*>(parent());
	//	QRect rtAreaInParent = pParent->geometry();		// check pParent ...

	//	if (rtScreen.isEmpty() == false &&
	//		pParent && rtAreaInParent.isEmpty() == false) {

	//		m_pWndInner->move(rtScreen.x(), rtScreen.y());
	//		m_pWndInner->resize(rtScreen.size());
	//		
	//		//setParent(m_pWndInner);
	//		
	//		m_pWndInner->show();
	//	}
	//	
	//}
}
