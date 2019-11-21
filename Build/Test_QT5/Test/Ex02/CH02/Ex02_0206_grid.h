
#pragma once

class Ex02_0206_Grid : public QWidget {
public:
	Ex02_0206_Grid(QWidget *parent = 0) : QWidget(parent) {
		QGridLayout *grid = new QGridLayout(this);
		grid->setSpacing(2);

		QList<QString> values({ "7", "8", "9", "/",
			"4", "5", "6", "*",
			"1", "2", "3", "-",
			"0", ".", "=", "+"
		});

		int pos = 0;

		for (int i = 0; i<4; i++) {
			for (int j = 0; j<4; j++) {

				QPushButton *btn = new QPushButton(values[pos], this);
				btn->setFixedSize(40, 40);
				grid->addWidget(btn, i, j);
				pos++;
			}
		}

		setLayout(grid);

	}
};


class Ex02_0206_Test_Grid : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char **ppArgs) {

		QApplication app(nArgNum, ppArgs);

		Ex02_0206_Grid window;

		window.setWindowTitle("Grid Layout");
		window.show();

		int nRet = app.exec();

		return nRet;
	}
};
