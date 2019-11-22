
#pragma once

class Ex02_0501_file_size_test : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char **ppArgs) {
		QTextStream out(stdout);

		if (nArgNum != 2) {

			qWarning("Usage: file_size file");
			return 1;
		}

		QString filename = ppArgs[1];

		if (!QFile(filename).exists()) {

			qWarning("The file does not exist");
			return 1;
		}

		QFileInfo fileinfo(filename);

		qint64 size = fileinfo.size();

		QString str = "The size is: %1 bytes";

		out << str.arg(size) << endl;

		return 0;
	}

};