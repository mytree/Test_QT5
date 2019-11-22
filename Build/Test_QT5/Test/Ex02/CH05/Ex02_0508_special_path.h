
#pragma once

class Ex02_0508_special_path_test : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char **ppArgs) {

		QTextStream out(stdout);

		out << "Current path:" << QDir::currentPath() << endl;
		out << "Home path:" << QDir::homePath() << endl;
		out << "Temporary path:" << QDir::tempPath() << endl;
		out << "Rooth path:" << QDir::rootPath() << endl;

		return 0;
	}
};
