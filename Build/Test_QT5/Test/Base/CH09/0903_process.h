
#pragma once

#include <QtCore/QProcess>

class C0903_TestProcess : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char **ppArgs) {
		QApplication app(nArgNum, ppArgs);

		QProcess cmd_ls;
#ifdef linux
		cmd_ls.start("ls", QStringList() << "-l");
#else
		cmd_ls.start("dir", QStringList());
#endif
		if (!cmd_ls.waitForStarted()) return false;

		if (!cmd_ls.waitForFinished()) return false;

		QByteArray result = cmd_ls.readAllStandardOutput();
		// cmd_ls.readAll();

		QTextEdit *edit = new QTextEdit();
		edit->setReadOnly(true);
		edit->append(result);
		edit->show();

		return app.exec();
	}
};