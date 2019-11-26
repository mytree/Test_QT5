
#include "../TestBase.h"
#include "WndScreen.h"


CWndCell::CWndCell(QWidget *parent) : QLabel(parent) {

}

//--------------------------------------------------------------------------

//CWndScreen::CWndScreen(QWidget* pParent) : QTableWidget(pParent) {
CWndScreen::CWndScreen(QWidget* pParent) : QWidget(pParent) {
	QSize parentSize = pParent->size();
	for (int nChIdx = 0; nChIdx < ECDivTypeEnum::MAX_DIV; nChIdx++) {
		//std::ostringstream oss; oss << "CH " << nChIdx + 1;
		//CWndCell* pCell = new CWndCell(this);	pCell->setText(oss.str().c_str());
		QString strText = "CH " + QString::number(nChIdx + 1);
		CWndCell* pCell = new CWndCell(this); pCell->setText(strText);
		m_chList.push_back(pCell);
	}

	//m_pGrid = new QGridLayout();		
	//SetDivision(DIV_1);
	

//	setLayout(m_pGrid);
}

CWndScreen::~CWndScreen() {
	//std::vector<CWndCell*>::iterator iter;
	//for (iter = m_chList.begin(); iter != m_chList.end(); iter++) {
	//	QWidget* pWidget = static_cast<QWidget*>(*iter);
	//	m_pGrid->removeWidget(pWidget);
	//	this->removeCell
	//	if (pWidget) {
	//		delete pWidget;	pWidget = nullptr;
	//	}
	//}

	std::vector<CWndCell*>::iterator iter;
	for (iter = m_chList.begin(); iter != m_chList.end(); iter++) {
		CWndCell* pCell = static_cast<CWndCell*>(*iter);
		if (pCell) {
			delete pCell; pCell = nullptr;
		}
	}
	//this->columnCount();
	//this->rowCount();
	//this->removeCellWidget(0, 0);
}

void CWndScreen::SetDivision(ECDivTypeEnum nDivType) {

	int nGridIdx = 0, nCIdx = 0, nRIdx = 0;

	// Table 에 등록된 Item 해제(제거 안 함)
	//int nPrevRowNum = rowCount();
	//int nPrevColNum = columnCount();
	//for (nRIdx = 0; nRIdx < nPrevRowNum; nRIdx++)
	//	for (nCIdx = 0; nCIdx < nPrevColNum; nCIdx++) takeItem(nRIdx, nCIdx);

	// Table Layout 새로 구성
	int nRowNum = 0, nColNum = 0;
	switch (nDivType) {
	case DIV_1:		{ nColNum = nRowNum = 1; break; }
	case DIV_4:		{ nColNum = nRowNum = 2; break; }
	case DIV_9:		{ nColNum = nRowNum = 3; break; }
	case DIV_16:	{ nColNum = nRowNum = 4; break; }
	case DIV_24:	{ nColNum = 6; nRowNum = 4; break; }
	default:	return;
	}
	int nCellW = width() / nColNum;
	int nCellH = height() / nRowNum;
	int nGridNum = nColNum * nRowNum;
	int nBeginPos = 0, nEndPos = (nBeginPos + (int)nDivType) % MAX_DIV, nPos = 0;
	CWndCell* pCell = nullptr;
	for (nGridIdx = 0; nGridIdx < (int)nDivType; nGridIdx++) {
		nCIdx = nGridIdx % nColNum;
		nRIdx = nGridIdx / nColNum;
		nPos = (nBeginPos + nGridIdx) % (int)nDivType;
		pCell = m_chList[nPos];
		pCell->setFixedSize(nCellW, nCellH);
		pCell->setAlignment(Qt::AlignCenter);
		//setCellWidget(nRIdx, nCIdx, pCell);
		//setItem(nRIdx, nCIdx, pCell);
	}
}
