
#include "./WndScreenInner.h"
#include "./WndCell.h"
#include "../ECUIEvent.h"

#include <QtGui/QGuiApplication>		// qApp
#include <QtGui/QScreen>				// QScreen

CWndScreenInner::CWndScreenInner(QWidget *pParent) : QWidget(pParent, Qt::Popup | Qt::Dialog) {
//CWndScreenInner::CWndScreenInner(QWidget *pParent) : QWidget(pParent, Qt::Popup) {
	setWindowTitle(" ");

	m_nChIdx = -1;
	m_pCell = new CWndCell(this);
}

CWndScreenInner::~CWndScreenInner() {
	if (m_pCell) {
		delete m_pCell;	m_pCell = nullptr;
	}
}

bool CWndScreenInner::SetChImage(int nChIdx, QPixmap *pBuf) {
	if (nChIdx < 0 || nChIdx >= static_cast<int>(ECDivTypeEnum::MAX_DIV)) return false;
	if (m_pCell == nullptr || pBuf == nullptr) return false;
	m_nChIdx = nChIdx;
	m_pCell->setPixmap(*pBuf);
	return true;
}

int CWndScreenInner::GetChIdx() {
	return m_nChIdx;
}

bool CWndScreenInner::SetDrawInfo(CWndCell& wndCell) {
	if (m_pCell == nullptr) return false;
	CWndCell::DrawInfo di = wndCell.GetDrawInfo();
	return m_pCell->SetDrawInfo(di);
}

void CWndScreenInner::resizeEvent(QResizeEvent *pEvent) {
	QSize wndSize = pEvent->size();
	m_pCell->resize(wndSize);
	m_pCell->update();
}