
#pragma once

class Ex02_0207_Review : public QWidget {
public:
	Ex02_0207_Review(QWidget *parent = 0) : QWidget(parent) {
		QGridLayout *grid = new QGridLayout(this);
		grid->setVerticalSpacing(15);
		grid->setHorizontalSpacing(10);

		QLabel *title = new QLabel("Title:", this);
		grid->addWidget(title, 0, 0, 1, 1);
		title->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

		QLineEdit *pEdit1 = new QLineEdit(this);
		grid->addWidget(pEdit1, 0, 1, 1, 1);

		QLabel *author = new QLabel("Author:", this);
		grid->addWidget(author, 1, 0, 1, 1);
		author->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

		QLineEdit *pEdit2 = new QLineEdit(this);
		grid->addWidget(pEdit2, 1, 1, 1, 1);

		QLabel *review = new QLabel("Review:", this);
		grid->addWidget(review, 2, 0, 1, 1);
		review->setAlignment(Qt::AlignRight | Qt::AlignTop);

		QTextEdit *te = new QTextEdit(this);
		grid->addWidget(te, 2, 1, 3, 1);

		setLayout(grid);

	}
};


class Ex02_0207_Test_Review : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char **ppArgs) {

		QApplication app(nArgNum, ppArgs);

		Ex02_0207_Review window;

		window.setWindowTitle("Review");
		window.show();

		int nRet = app.exec();

		return nRet;
	}
};
