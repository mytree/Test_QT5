
#include "./0601_validator.h"

C0601_Validator::C0601_Validator(QWidget *parent) {
	QGridLayout *grid = new QGridLayout();
	label_double = new QLabel(this);		label_double->setText("Double");
	label_int = new QLabel(this);			label_int->setText("Int");
	label_regexp = new QLabel(this);		label_regexp->setText("Regular Expression");

	lineedit_double = new QLineEdit(this);
	lineedit_int = new QLineEdit(this);
	lineedit_regexp = new QLineEdit(this);

	doubleValidator = new QDoubleValidator(this);
	doubleValidator->setTop(10.0);
	doubleValidator->setBottom(-10.0);
	doubleValidator->setDecimals(3);
	lineedit_double->setValidator(doubleValidator);

	intValidator = new QIntValidator(this);
	intValidator->setTop(10);
	intValidator->setBottom(-10);
	lineedit_int->setValidator(intValidator);

	regexpValidator = new QRegExpValidator(this);
	regexpValidator->setRegExp(QRegExp("^\\d{1,3}.\\d{1,3}.\\d{1,3}.\\d{1,3}"));
	lineedit_regexp->setValidator(regexpValidator);

	grid->addWidget(label_double, 0, 0);
	grid->addWidget(label_int, 1, 0);
	grid->addWidget(label_regexp, 2, 0);
	grid->addWidget(lineedit_double, 0, 1);
	grid->addWidget(lineedit_int, 1, 1);
	grid->addWidget(lineedit_regexp, 2, 1);

	setLayout(grid);
	setWindowTitle("Validator");
}


