
#pragma once

class Ex02_0510_permission_test : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char **ppArgs) {

		QTextStream out(stdout);
		if (nArgNum != 2) {
			out << "Usage: permissions file" << endl;
			return 1;
		}
		QString filename = ppArgs[1];
		QFile::Permissions ps = QFile::permissions(filename);
		QString fper;

		if (ps & QFile::ReadOwner) fper.append('r');
		else fper.append('-');
		if (ps & QFile::WriteOwner) fper.append('w');
		else fper.append('-');
		if (ps & QFile::ExeOwner) fper.append('x');
		else fper.append('-');
		if (ps & QFile::ReadGroup) fper.append('r');
		else fper.append('-');
		if (ps & QFile::WriteGroup) fper.append('w');
		else fper.append('-');
		if (ps & QFile::ExeGroup) fper.append('x');
		else fper.append('-');
		if (ps & QFile::ReadOther) fper.append('r');
		else fper.append('-');
		if (ps & QFile::WriteOther) fper.append('w');
		else fper.append('-');
		if (ps & QFile::ExeOther) fper.append('x');
		else fper.append('-');
		
		out << fper << endl;
		return 0;
	}
};
