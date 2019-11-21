
#pragma once

class Ex02_0302_keypress : public QWidget {
public:
	Ex02_0302_keypress(QWidget* parent = 0) : QWidget(parent) {
	}
protected:
	void keyPressEvent(QKeyEvent * e) {
		if (e->key() == Qt::Key_Escape) {
			qApp->quit();
		}
	}
};

class Ex02_0302_keypress_test : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char **ppArgs) {
		QApplication app(nArgNum, ppArgs);

		Ex02_0302_keypress window;

		window.resize(250, 150);
		window.setWindowTitle("Key press");
		window.show();

		return app.exec();

	}
};
