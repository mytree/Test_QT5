
#pragma once

#include "ECUIEvent.h"

class CWndScreen : public QWidget {
private:
	QGridLayout						*m_pGrid;
	std::vector<QPushButton*>		m_chList;

public:
	CWndScreen(QWidget *pParent = nullptr);

	void SetDivision(ECDivTypeEnum nDivType);
};