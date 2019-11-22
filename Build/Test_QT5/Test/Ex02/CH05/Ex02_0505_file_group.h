
#pragma once

// 파일에 소속된 그룹과 소유자 반환. 윈도우 환경에서는 출력정보 없음

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