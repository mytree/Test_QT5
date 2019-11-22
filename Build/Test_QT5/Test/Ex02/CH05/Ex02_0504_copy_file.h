
#pragma once

class Ex02_0504_copy_file_test : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char **ppArgs) {
		QTextStream out(stdout);
		if (nArgNum != 3) {
			qWarning("Usage: copyfile source destination");
			return 1;
		}
		QString source = ppArgs[1];
		if (!QFile(source).exists()) {
			qWarning("The source file does not exist");
			return 1;
		}
		QString destin(ppArgs[2]);
		QFile::copy(source, destin);
		return 0;
	}
};