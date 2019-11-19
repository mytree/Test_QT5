
#include "./0501_main_window.h"

C0501_QtEditor::C0501_QtEditor() {
	QMenu *fileMenu;
	QToolBar *toolbar;
	QStatusBar *statusbar;
	QTextEdit *textEdit = new QTextEdit();
	QAction *newAct = new QAction("&New", this);

	newAct->setShortcut(tr("Ctrl+N"));
	newAct->setStatusTip("make new file");
	connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

	fileMenu = menuBar()->addMenu("File");
	fileMenu->addAction(newAct);
		
	toolbar = addToolBar("New");
	toolbar->addAction(newAct);
		
	statusbar = statusBar();
	setCentralWidget(textEdit);
}

int C0501_QtEditor::newFile() {
	return 0;
}
