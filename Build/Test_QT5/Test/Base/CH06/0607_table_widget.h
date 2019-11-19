
#pragma once

class C0607_TableWidget : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char **ppArgs) {
		QApplication app(nArgNum, ppArgs);

		QTableWidget *tableWidget = new QTableWidget(3, 4, 0);
		QTableWidgetItem *item1 = new QTableWidgetItem("Item 1");
		QTableWidgetItem *item2 = new QTableWidgetItem("Item 2");
		QTableWidgetItem *item3 = new QTableWidgetItem("Item 3");
		QTableWidgetItem *item4 = new QTableWidgetItem("Item 4");
		tableWidget->setItem(0, 0, item1);
		tableWidget->setItem(0, 1, item2);
		tableWidget->setItem(2, 1, item3);
		tableWidget->setItem(2, 3, item4);
		tableWidget->resize(420, 120);
		tableWidget->show();
		
		return app.exec();
	}
};
