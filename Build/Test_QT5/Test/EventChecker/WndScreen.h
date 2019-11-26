
#pragma once

#include "ECUIEvent.h"
#include <QtWidgets/QWidget>
#include <QtWidgets/QLayout>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QLabel>

class CWndCell : public QLabel {
	Q_OBJECT
public:
	CWndCell(QWidget *parent = nullptr);
};

//class CWndScreen : public QTableWidget {
class CWndScreen : public QWidget {
	Q_OBJECT
private:
	std::vector<CWndCell*>		m_chList;
	QGridLayout					m_grid;

public:
	CWndScreen(QWidget *pParent = nullptr);
	virtual ~CWndScreen();

	void SetDivision(ECDivTypeEnum nDivType);
};