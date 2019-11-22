
#pragma once

// ���Ͽ� �Ҽӵ� �׷�� ������ ��ȯ. ������ ȯ�濡���� ������� ����

class Ex02_0505_file_group_test : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char **ppArgs) {
		QTextStream out(stdout);
		if (nArgNum != 2) {
			qWarning("Usage: owner file");
			return 1;
		}
		QString filename = ppArgs[1];
		QFileInfo fileinfo(filename);
		QString group = fileinfo.group();
		QString owner = fileinfo.owner();
		out << "Group: " << group << endl;
		out << "Owner: " << owner << endl;
		return 0;
	}
};