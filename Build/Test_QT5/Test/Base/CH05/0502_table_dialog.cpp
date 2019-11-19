
#include "./0502_table_dialog.h"

QtTabDialog::QtTabDialog(QWidget *parent) : QDialog(parent) {
	resize(320, 240);

	tabwidget = new QTabWidget(this);
	tabwidget->setGeometry(QRect(0, 0, 320, 240));

	tab_1 = new QWidget();
	tabwidget->addTab(tab_1, "Tab 1");
	tab_2 = new QWidget();
	tabwidget->addTab(tab_2, "Tab 2");
	tab_3 = new QWidget();
	tabwidget->addTab(tab_3, "Tab 3");

	setWindowTitle("Tab Dialog");
}