
#include "./WndScreenInner.h"
#include "./WndCell.h"
#include "../ECType.h"
#include "./WndScreen.h"

#include <QtGui/QGuiApplication>		// qApp
#include <QtGui/QScreen>				// QScreen

//--------------------------------------------------------------------------
//
//	CWndScreenInner::CCellEventHandler
//

class CWndScreenInner::CCellEventHandler : public CWndCellEvent {
private:
	CWndScreenInner*		m_pParent;

public:
	CCellEventHandler(CWndScreenInner* pParent) : m_pParent(pParent) {
	}

	virtual void OnWndCellPaint(QPainter &qp) {
		if (m_pParent) m_pParent->OnPaint(qp);
	}
	virtual void OnWndCellMouseMove(QPoint &mousePos, Qt::MouseButton &nMouseType) {
		if (m_pParent) m_pParent->OnMouseMove(mousePos, nMouseType);
	}
	//virtual void OnWndCellMouseDown(QPoint &mousePos, Qt::MouseButton &nMouseType) {
	//	switch (nMouseType) {
	//	case Qt::RightButton:	default:	return;
	//	case Qt::LeftButton:			
	//		if (m_pParent) m_pParent->OnLButtonDown(mousePos);
	//		break;
	//	}
	//}
	//virtual void OnWndCellMouseUp(QPoint &mousePos, Qt::MouseButton &nMouseType) {
	//	switch (nMouseType) {
	//	case Qt::RightButton:	default:	return;
	//	case Qt::LeftButton:
	//		if (m_pParent) m_pParent->OnLButtonUp(mousePos);
	//		break;
	//	}
	//}
	//virtual void OnWndCellDoubleClick(QPoint &mousePos, Qt::MouseButton &nMouseType) {
	//	switch (nMouseType) {
	//	case Qt::RightButton:	default:	return;
	//	case Qt::LeftButton:
	//		if (m_pParent) m_pParent->OnLButtonDoubleClick(mousePos);
	//		break;
	//	}
	//}
};

//--------------------------------------------------------------------------

CWndScreenInner::CWndScreenInner(QWidget *pParent, int nAreaNum) : QWidget(pParent, Qt::Popup | Qt::Dialog) {
//CWndScreenInner::CWndScreenInner(QWidget *pParent) : QWidget(pParent, Qt::Popup) {
	setWindowTitle(" ");

	m_nChIdx = -1;
	m_pEventHandler = new CWndScreenInner::CCellEventHandler(this);
	m_pCell = new CWndCell(this, m_pEventHandler);
	m_pCell->setContextMenuPolicy(Qt::CustomContextMenu);			// ���ؽ�Ʈ �޴� ���
	m_pCell->setMouseTracking(true);								// ���콺 Ŭ������ �ʾƵ� ���콺 �̵� �̺�Ʈ ���� ����
	connect(m_pCell, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(customMenuRequested(QPoint)));

	m_nDetectAreaNum = (nAreaNum < 1) ? 1 : ((nAreaNum > 10) ? 10 : nAreaNum);
	m_nCurAreaIdx = -1;
	for (int nAreaIdx = 0; nAreaIdx < 10; nAreaIdx++) {
		m_pAct_Area[nAreaIdx] = nullptr;
	}
	m_prevPos = m_curPos = QPoint(-1, -1);

	std::ostringstream ossText;
	for (int nAreaIdx = 0; nAreaIdx < m_nDetectAreaNum; nAreaIdx++) {
		ossText.clear();	ossText.str("");
		ossText << "AREA " << nAreaIdx + 1;
		m_pAct_Area[nAreaIdx] = m_menu.addAction(ossText.str().c_str());
		m_pAct_Area[nAreaIdx]->setCheckable(true);
	}
	m_menu.addAction("Clear");
	m_menu.addAction("Apply");

}

CWndScreenInner::~CWndScreenInner() {
	if (m_pCell) {
		delete m_pCell;	m_pCell = nullptr;
	}
	if (m_pEventHandler) {
		delete m_pEventHandler;	m_pEventHandler = nullptr;
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
	ECDrawInfo di = wndCell.GetDrawInfo();
	return m_pCell->SetDrawInfo(di);
}

void CWndScreenInner::resizeEvent(QResizeEvent *pEvent) {
	QSize wndSize = pEvent->size();
	m_pCell->resize(wndSize);
	m_pCell->update();
}

void CWndScreenInner::mousePressEvent(QMouseEvent *pEvent) {
	QPoint mousePos = pEvent->pos();
	Qt::MouseButton nMouseType = pEvent->button();
	switch (nMouseType) {
	case Qt::RightButton:	default:	return;
	case Qt::LeftButton:
		OnLButtonDown(mousePos);
		break;
	}
}

void CWndScreenInner::mouseReleaseEvent(QMouseEvent *pEvent) {
	QPoint mousePos = pEvent->pos();
	Qt::MouseButton nMouseType = pEvent->button();
	switch (nMouseType) {
	case Qt::RightButton:	default:	return;
	case Qt::LeftButton:
		OnLButtonUp(mousePos);
		break;
	}
}

void CWndScreenInner::mouseDoubleClickEvent(QMouseEvent *pEvent) {
	QPoint mousePos = pEvent->pos();
	Qt::MouseButton nMouseType = pEvent->button();
	switch (nMouseType) {
	case Qt::RightButton:	default:	return;
	case Qt::LeftButton:
		OnLButtonDoubleClick(mousePos);
		break;
	}
}



//
//void CWndScreenInner::customMenuRequested(QPoint pos) {
//	qDebug("customMenuRequested...POS(%d, %d)", pos.x(), pos.y());
//	QPoint globalPos = m_pCell->mapToGlobal(pos);
//
//	QAction* selectedItem = m_menu.exec(globalPos);
//	if (selectedItem) {
//		QString strText = selectedItem->text();
//		//qDebug("[ITEM_SELECTED] " + strText.toLocal8Bit());
//		if (strText.compare("End DetectArea") == 0) {
//			qDebug("[ITEM_SELECTED] " + strText.toLocal8Bit());
//			SetUI_DetectArea(true);
//		}
//		else if (strText.compare("Clear DetectArea") == 0) {
//			qDebug("[ITEM_SELECTED] " + strText.toLocal8Bit());
//		}
//		else if (strText.compare("AREA 1") == 0) {
//			qDebug("[ITEM_SELECTED] " + strText.toLocal8Bit());
//			SetUI_DetectArea(false);
//		}
//		else if (strText.compare("AREA 2") == 0) {
//			qDebug("[ITEM_SELECTED] " + strText.toLocal8Bit());
//			SetUI_DetectArea(false);
//		}
//	}
//	else {		// ���� �׸��� ���� ���
//
//	}
//
//}

void CWndScreenInner::customMenuRequested(QPoint pos) {
	//qDebug("customMenuRequested...POS(%d, %d)", pos.x(), pos.y());
	QPoint globalPos = m_pCell->mapToGlobal(pos);

	QAction* selectedItem = m_menu.exec(globalPos);
	if (selectedItem == nullptr) return;

	QString strText = selectedItem->text();
	QStringList strTokenList = strText.split(" ");
	if (strTokenList[0].compare("Clear") == 0) {
		m_pCell->ClearAllArea();
		m_pCell->update();
	}
	if (strTokenList[0].compare("Apply") == 0) {
		CWndScreen* pScreen = static_cast<CWndScreen*>(parent());
		if (pScreen) {
			ECDrawInfo di = m_pCell->GetDrawInfo();
			di.canvasSize = m_pCell->size();
			pScreen->SetDrawInfo(m_nChIdx, di);
		}
	}
	else if (strTokenList[0].compare("AREA") == 0) {					// "AREA 1", "AREA 2", ...
		int nAreaIdx = strTokenList[1].toInt() - 1;						// (AREA, 0), (AREA, 1), ... , (AREA, {m_nDetectAreaNum-1})
		if (nAreaIdx < 0 || nAreaIdx >= m_nDetectAreaNum) return;
		for (int nIdx = 0; nIdx < m_nDetectAreaNum; nIdx++) {
			if (nAreaIdx != nIdx) 
				m_pAct_Area[nIdx]->setChecked(false);
			else {
				m_pAct_Area[nIdx]->setChecked(true);
				m_nCurAreaIdx = nIdx;
			}
		}
	}
}

void CWndScreenInner::OnLButtonDown(QPoint mousePos) {

	bool bIsValidAreaIdx = (m_nCurAreaIdx >= 0) && (m_nCurAreaIdx < m_nDetectAreaNum);	// ���� �ε��� ���Ἲ ����
	if (bIsValidAreaIdx == false) return;												// ���� �ε����� ���� �� �Ǿ����� skip
	QPoint prevPos = m_prevPos;												// ���� ���� ��ġ ������
	m_prevPos = mousePos;													// ���� ���� ��ġ ����

	if (prevPos == QPoint(-1, -1)) {										// ���� ���� ��ġ�� �����Ǿ� ���� �ʾҴٸ�
		m_pCell->ClearArea(m_nCurAreaIdx);									// ���� ���� �����ϴ� ������ ����, ���� ���� ����
	}

	m_pCell->AddAreaPoint(m_nCurAreaIdx, mousePos);							// ���� ��ġ �߰�
	//	m_pCell->update();

	repaint();
	//qDebug("[LBTN_DOWN] Pos(%d, %d) ", mousePos.x(), mousePos.y());
}

void CWndScreenInner::OnLButtonUp(QPoint mousePos) {
	//qDebug("[LBTN_UP] Pos(%d, %d) ", mousePos.x(), mousePos.y());
}

void CWndScreenInner::OnLButtonDoubleClick(QPoint mousePos) {
	bool bIsValidAreaIdx = (m_nCurAreaIdx >= 0) && (m_nCurAreaIdx < m_nDetectAreaNum);	// ���� �ε��� ���Ἲ ����
	if (bIsValidAreaIdx == false) return;												// ���� �ε����� ���� �� �Ǿ����� skip

	//qDebug("[DOUBLE_CLICK] Pos(%d, %d) ", mousePos.x(), mousePos.y());
	QPoint undefinedPos = QPoint(-1, -1);
	if (m_prevPos != undefinedPos) {
		m_pCell->AddAreaPoint(m_nCurAreaIdx, mousePos, true);
		m_prevPos = m_curPos = QPoint(-1, -1);
	}

	repaint();
}
void CWndScreenInner::OnMouseMove(QPoint mousePos, Qt::MouseButton nMouseType) {
	if (m_nCurAreaIdx < 0) return;				// ���� �ε����� ���� �� �Ǿ����� skip
	if (m_prevPos == QPoint(-1, -1)) return;	// ���� ��ġ�� ���� ���� �ʾ����� skip
	
	//qDebug("[MOUSE_MOVE] Pos(%d, %d) ", mousePos.x(), mousePos.y());
	repaint();
	m_curPos = mousePos;
}

void CWndScreenInner::OnPaint(QPainter& qp) {

	QPoint undefinedPos = QPoint(-1, -1);
	if (m_prevPos != undefinedPos && m_curPos != undefinedPos) {			// �ӽ� ���� ���� ���� �׸���
		qp.setPen(QColor(255, 255, 255));
		qp.drawLine(m_prevPos, m_curPos);
		//qDebug("[PAINT] Line(%d, %d - %d, %d)", m_prevPos.x(), m_prevPos.y(), m_curPos.x(), m_curPos.y());
	}
	
}

void CWndScreenInner::SetUI_DetectArea(bool bIsBegin) {
	//if (bIsBegin) {
	//	m_submenu_detect_area.setEnabled(true);
	//	m_pAct_EndDetectArea->setEnabled(false);
	//	
	//}
	//else {
	//	m_submenu_detect_area.setEnabled(false);
	//	m_pAct_EndDetectArea->setEnabled(true);

	//	m_pAct_EndDetectArea->setCheckable(true);
	//	m_pAct_EndDetectArea->setChecked(true);
	//}
}