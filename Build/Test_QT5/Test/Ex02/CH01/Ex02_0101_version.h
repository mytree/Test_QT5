
#pragma once

class Ex02_0101_version : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char **ppArgs) {
		std::cout << "Qt version: " << qVersion() << std::endl;

		QApplication app(nArgNum, ppArgs);
		QWidget window;

		window.resize(300, 200);
		window.setWindowTitle("Simple example");
		window.show();

		return app.exec();
	}
};