
#include "../TestBase.h"
#include "WndScreen.h"

CWndScreen::CWndScreen(QWidget* pParent) : QWidget(pParent) {

	for (int nChIdx = 0; nChIdx < ECDivTypeEnum::MAX_DIV; nChIdx++) {
		std::ostringstream oss; oss << "CH " << nChIdx + 1;
		QPushButton* pBtn = new QPushButton();	pBtn->setText(oss.str().c_str());
		m_chList.push_back(pBtn);
	}

	m_pGrid = new QGridLayout();		SetDivision(DIV_1);

}

void CWndScreen::SetDivision(ECDivTypeEnum nDivType) {
	std::vector<QPushButton*>::iterator iter;
	for (iter = m_chList.begin(); iter != m_chList.end(); iter++) {
		QWidget* pWidget = static_cast<QWidget*>(*iter);
		m_pGrid->removeWidget(pWidget);
	}
	iter = m_chList.begin();	std::advance(iter, 0);
	for (; iter != m_chList.end(); iter++) {
		QWidget* pWidget = static_cast<QWidget*>(*iter);
		m_pGrid->addWidget(pWidget);
	}
}
