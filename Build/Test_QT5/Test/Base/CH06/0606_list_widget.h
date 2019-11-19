
#pragma once

class C0606_ListWidget : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char **ppArgs) {
		QApplication app(nArgNum, ppArgs);

		QListWidget *listwidget = new QListWidget(0);
		new QListWidgetItem("Item 1", listwidget);
		new QListWidgetItem("Item 2", listwidget);

		QListWidgetItem *item3 = new QListWidgetItem();
		item3->setText("Item 3");
		listwidget->addItem(item3);
		listwidget->addItem("Item 4");

		listwidget->setFlow(QListView::TopToBottom);
		listwidget->resize(82, 64);
		listwidget->show();

		return app.exec();
	}
};
