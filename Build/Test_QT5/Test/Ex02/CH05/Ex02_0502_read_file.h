
#pragma once

//	���� �����ؼ� �� ���� �а� �ܼ� ����ϴ� ���α׷�
class Ex02_0502_read_file_test : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char **ppArgs) {
		QTextStream out(stdout);
		QFile file("colours");
		if (!file.open(QIODevice::ReadOnly)) {
			qWarning("Cannot open file for reading");
			return 1;
		}

		QTextStream in(&file);
		while (!in.atEnd()) {
			QString line = in.readLine();
			out << line << endl;
		}
		file.close();
		return 0;
	}

};