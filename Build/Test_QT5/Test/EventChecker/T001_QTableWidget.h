
#pragma once

//#include <QtWidgets/QMainWindow>
//#include <QtWidgets/QApplication>
//#include <QtWidgets/QDesktopWidget>
//#include <QtWidgets/QHeaderView>
//#include <QtWidgets/QMessageBox>
//#include <QtWidgets/QTableWidget>

#include "../TestBase.h"

class T001_QTableWidget : public QMainWindow {
	Q_OBJECT
private:
	QTableWidget*			m_pTableWidget;
	QStringList				m_TableHeader;

public:
	T001_QTableWidget(QWidget* parent = nullptr) : QMainWindow(parent), m_pTableWidget(nullptr) {
		m_pTableWidget = new QTableWidget(this);
		m_pTableWidget->setRowCount(10);
		m_pTableWidget->setColumnCount(3);
		//m_TableHeader << "#" << "Name" << "Text";
		//m_pTableWidget->setHorizontalHeaderLabels(m_TableHeader);
		//m_pTableWidget->horizontalHeader()->setVisible(false);
		m_pTableWidget->verticalHeader()->setVisible(false);
		m_pTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
		m_pTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
		m_pTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
		m_pTableWidget->setShowGrid(false);
		m_pTableWidget->setStyleSheet("QTableView {selection-background-color: red;}");
		//m_pTableWidget->setStyleSheet("QTableView {background-color: blue;}");
		m_pTableWidget->setGeometry(QApplication::desktop()->screenGeometry());

		//insert data
		m_pTableWidget->setItem(0, 1, new QTableWidgetItem("Hello"));

		connect(m_pTableWidget, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(cellSelected(int, int)));
	}

	~T001_QTableWidget() {
	}

private slots:
	void cellSelected(int nRow, int nCol) {
		QMessageBox::information(this, "",
			"Cell at row " + QString::number(nRow) +
			" column " + QString::number(nCol) +
			" was double clicked.");
	}

};

class T001_QTableWidgetTest : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char **ppArgs) {
		QApplication app(nArgNum, ppArgs);
		T001_QTableWidget wnd;
		wnd.show();
		return app.exec();
	}
};