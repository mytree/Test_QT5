
#pragma once

class Ex02_0509_file_path_test : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char **ppArgs) {

		QTextStream out(stdout);

		if (nArgNum != 2) {

			out << "Usage: file_times file" << endl;
			return 1;
		}

		QString filename = ppArgs[1];

		QFileInfo fileinfo(filename);

		QString absPath = fileinfo.absoluteFilePath();
		QString baseName = fileinfo.baseName();
		QString compBaseName = fileinfo.completeBaseName();
		QString fileName = fileinfo.fileName();
		QString suffix = fileinfo.suffix();
		QString compSuffix = fileinfo.completeSuffix();

		out << "Absolute file path: " << absPath << endl;
		out << "Base name: " << baseName << endl;
		out << "Complete base name: " << compBaseName << endl;
		out << "File name: " << fileName << endl;
		out << "Suffix: " << suffix << endl;
		out << "Whole suffix: " << compSuffix << endl;

		return 0;
	}
};
