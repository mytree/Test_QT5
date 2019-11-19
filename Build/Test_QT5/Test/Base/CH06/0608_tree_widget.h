
#pragma once

class C0608_TreeWidget : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char **ppArgs) {
		QApplication app(nArgNum, ppArgs);

		QTreeWidget *treeWidget = new QTreeWidget(0);
		treeWidget->setColumnCount(2);

		QTreeWidgetItem *headerItem = new QTreeWidgetItem();
		headerItem->setText(0, "1");
		headerItem->setText(1, "2");
		headerItem->setText(2, "3");
		headerItem->setText(3, "4");
		treeWidget->setHeaderItem(headerItem);

		QTreeWidgetItem *item1 = new QTreeWidgetItem(treeWidget);
		item1->setText(0, "Item 1");
		item1->setText(1, "Item 2");
		item1->setText(2, "Item 3");
		item1->setText(3, "Item 4");

		QTreeWidgetItem *item2 = new QTreeWidgetItem(treeWidget);
		item2->setText(0, "Item 5");
		item2->setText(1, "Item 6");
		item2->setText(2, "Item 7");
		item2->setText(3, "Item 8");
		treeWidget->addTopLevelItem(item2);

		QTreeWidgetItem *item3 = new QTreeWidgetItem(treeWidget);
		item3->setText(0, "Item 9");
		item3->setText(1, "Item 10");
		item3->setText(2, "Item 11");
		item3->setText(3, "Item 12");

		QTreeWidgetItem *subItem1 = new QTreeWidgetItem(treeWidget);
		subItem1->setText(0, "subItem 1");
		subItem1->setText(1, "subItem 2");
		subItem1->setText(2, "subItem 3");
		subItem1->setText(3, "subItem 4");
		item2->addChild(subItem1);

		QTreeWidgetItem *subItem2 = new QTreeWidgetItem(treeWidget);
		subItem2->setText(0, "subItem 1");
		subItem2->setText(1, "subItem 2");
		subItem2->setText(2, "subItem 3");
		subItem2->setText(3, "subItem 4");
		item2->addChild(subItem2);

		treeWidget->resize(420, 120);
		treeWidget->setSortingEnabled(true);
		treeWidget->show();

		return app.exec();
	}
};
