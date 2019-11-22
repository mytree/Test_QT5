
#pragma once

class Ex02_0506_last_read_test : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char **ppArgs) {
		QTextStream out(stdout);
		if (nArgNum != 2) {
			qWarning("Usage: file_times file");
			return 1;
		}
		QString filename = ppArgs[1];
		QFileInfo fileinfo(filename);

		QDateTime last_rea = fileinfo.lastRead();
		QDateTime last_mod = fileinfo.lastModified();

		out << "Last read: " << last_rea.toString() << endl;
		out << "Last modified: " << last_mod.toString() << endl;
		return 0;
	}
};
