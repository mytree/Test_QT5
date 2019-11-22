
#pragma once

class Ex02_0507_dir_test : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char **ppArgs) {
		QTextStream out(stdout);
		QDir dir;

		if (dir.mkdir("mydir")) {
			out << "mydir successfully created" << endl;
		}

		dir.mkdir("mydir2");

		if (dir.exists("mydir2")) {
			dir.rename("mydir2", "newdir");
		}

		dir.mkpath("temp/newdir");
		return 0;
	}
};
