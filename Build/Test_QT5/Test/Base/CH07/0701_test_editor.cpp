
#include "../../TestBase.h"
#include "./0701_test_editor.h"

C0701_Editor::C0701_Editor() {
	workspace = new QMdiArea();

	QMenu *fileMenu;
	QToolBar *toolbar;
	QStatusBar *statusbar;
	QTextEdit *textEdit = new QTextEdit();
	
	// New
	QAction *newAct = new QAction("&New", this);
	newAct->setShortcut(tr("Ctrl+N"));
	newAct->setStatusTip("make new file");
	connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));
	fileMenu = menuBar()->addMenu("File");		fileMenu->addAction(newAct);
	toolbar = addToolBar("New");				toolbar->addAction(newAct);
	statusbar = statusBar();
	
	//	Open
	QAction *openAct = new QAction("&Open", this);
	openAct->setShortcut(tr("Ctrl+O"));
	openAct->setStatusTip(tr("Open existing file"));
	connect(openAct, SIGNAL(triggered()), this, SLOT(openFile()));
	fileMenu->addAction(openAct);
	toolbar->addAction(openAct);

	//	Save
	QAction *saveAct = new QAction("&Save", this);
	saveAct->setShortcut(tr("Ctrl+S"));
	saveAct->setStatusTip(tr("Save current file"));
	connect(saveAct, SIGNAL(triggered()), this, SLOT(saveFile()));
	fileMenu->addAction(saveAct);
	toolbar->addAction(saveAct);

	//	File Info
	QAction *infoAct = new QAction("File &info", this);
	infoAct->setShortcut(tr("Ctrl+I"));
	infoAct->setStatusTip(tr("Get file Information"));
	connect(infoAct, SIGNAL(triggered()), this, SLOT(showFileInfo()));
	fileMenu->addAction(infoAct);
	toolbar->addAction(infoAct);

	setCentralWidget(workspace);
	workspace->addSubWindow(textEdit);
	workspace->show();
}

int C0701_Editor::newFile() {
	return 0;
}

int C0701_Editor::openFile() {
	QByteArray msg;
	QFileDialog *fileDlg = new QFileDialog(this);
	QString fileName = fileDlg->getOpenFileName(this, "Choose a file", "/home", \
		"Plain Text(*.text *.txt *.html)");
	QFile *file = new QFile();
	file->setFileName(fileName);
	file->open(QIODevice::ReadOnly);
	msg = file->read(file->size());
	file->close();

	QTextEdit *textedit = new QTextEdit();
	textedit->setWindowTitle(fileName);
	textedit->setPlainText(msg);
	workspace->addSubWindow(textedit);
	textedit->show();

	return 0;
}

int C0701_Editor::saveFile() {
	QByteArray msg;
	QFile *file = new QFile();
	bool bIsExistActiveWindow = workspace->isActiveWindow();
	QTextEdit *textEdit = (QTextEdit*)workspace->activeSubWindow();
	bool bIsWidget = textEdit->isWidgetType();
	bool bIsWindow = textEdit->isWindow();
	if (bIsWidget == false || bIsWindow == false) return -1;		// 정상 동작 안 함.
	QString strPlainText = textEdit->toPlainText();
	msg.append(strPlainText);

	QString fileName = textEdit->windowTitle();
	if (!fileName.length()) {
		fileName = QFileDialog::getSaveFileName(this, "Choose a file", \
			"/home", "Plain Text(*.text *.txt *.html)");
	}
	file->setFileName(fileName);
	file->open(QIODevice::WriteOnly);
	file->write(msg);
	file->close();
	
	return 0;
}

int C0701_Editor::showFileInfo() {
	QString fileName = workspace->activeSubWindow()->windowTitle();
	QFileInfo *fileInfo = new QFileInfo(fileName);
	QTextEdit *fileInfoDisplay = new QTextEdit();
	QString text;
	text = QString("File Path : %1 \n size: %2").arg(fileInfo->filePath()).arg(fileInfo->size());

	fileInfoDisplay->setReadOnly(true);
	fileInfoDisplay->setPlainText(text);

	workspace->addSubWindow(fileInfoDisplay);
	fileInfoDisplay->show();

	return 0;
}