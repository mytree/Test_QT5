
#pragma once

class C0605_Model : public QWidget {
private:
	QStandardItemModel	*model;
	QTableView			*tableView;
public:
	C0605_Model(QWidget *parent = 0, Qt::WindowFlags flags = 0) {
		model = new QStandardItemModel(this);
		model->insertColumns(0, 2);
		model->setHeaderData(0, Qt::Horizontal, tr("Number"));
		model->setHeaderData(1, Qt::Horizontal, tr("Name"));

		model->insertRow(2);
		QStandardItem *item0 = new QStandardItem("No 1");				model->setItem(0, 0, item0);
		QStandardItem *item1 = new QStandardItem("YoungJin Suh");		model->setItem(0, 1, item1);
		QStandardItem *item2 = new QStandardItem("No 2");				model->setItem(1, 0, item2);
		QStandardItem *item3 = new QStandardItem("youngHwa Ryu");		model->setItem(1, 1, item3);

		tableView = new QTableView(this);
		tableView->setModel(model);
	}
};

class C0605_TestModel : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char **ppArgs) {
		QApplication app(nArgNum, ppArgs);

		C0605_Model w;
		w.show();
		app.connect(&app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()));
		
		return app.exec();
	}
};
