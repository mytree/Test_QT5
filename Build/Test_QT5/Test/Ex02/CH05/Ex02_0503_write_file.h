
#pragma once

class Ex02_0503_write_file_test : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char **ppArgs) {
		QTextStream out(stdout);
		QString filename = "distros";
		QFile file(filename);
		if (file.open(QIODevice::WriteOnly)) {
			QTextStream out(&file);
			out << "Xubuntu" << endl;
			out << "Arch" << endl;
			out << "Debian" << endl;
			out << "Redhat" << endl;
			out << "Slackware" << endl;
		}
		else {
			qWarning("Could not open file");
		}
		file.close();
		return 0;
	}

};