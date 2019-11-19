
#include "./0702_dir.h"

C0702_Dir::C0702_Dir() {
	int cnt;
	QVBoxLayout *mainLayout = new QVBoxLayout(this);
	dirlist = new QListWidget(this);
	mainLayout->addWidget(dirlist);
	fileName = new QLineEdit();
	mainLayout->addWidget(fileName);
	
	QPushButton *makeDir = new QPushButton();
	makeDir->setText("Make Directory");
	mainLayout->addWidget(makeDir);

	QPushButton *removeDir = new QPushButton();
	removeDir->setText("Remove Directory");
	mainLayout->addWidget(removeDir);

	QPushButton *renameDir = new QPushButton();
	renameDir->setText("Rename Directory");
	mainLayout->addWidget(renameDir);

	directory = new QDir(".");

	for (cnt = 0; cnt < directory->entryList().count(); cnt++) {
		dirlist->addItem(directory->entryList().at(cnt));
	}
	connect(dirlist, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(changeDir()));
	connect(dirlist, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(itemSelected()));
	connect(makeDir, SIGNAL(clicked()), this, SLOT(makeDir()));
	connect(renameDir, SIGNAL(clicked()), this, SLOT(renameDir()));
	connect(removeDir, SIGNAL(clicked()), this, SLOT(removeDir()));

	setLayout(mainLayout);
}

int C0702_Dir::itemSelected() {
	fileName->setText(dirlist->currentItem()->text());
	return 0;
}

int C0702_Dir::changeDir() {
	int cnt;
	QFileInfo checkDir(dirlist->currentItem()->text());
	if (checkDir.isDir()) {
		directory->cd(dirlist->currentItem()->text());
		dirlist->clear();

		for (cnt = 0; cnt < directory->entryList().count(); cnt++) {
			dirlist->addItem(directory->entryList().at(cnt));
		}
	}
	return 0;
}

int C0702_Dir::makeDir() {
	int cnt;
	if (!fileName->text().length()) {
		directory->mkdir(fileName->text());
	}
	dirlist->clear();
	directory->refresh();
	for (cnt = 0; cnt < directory->entryList().count(); cnt++) {
		dirlist->addItem(directory->entryList().at(cnt));
	}
	return 0;
}

int C0702_Dir::removeDir() {
	int cnt;
	if (!fileName->text().length()) {
		directory->rmdir(fileName->text());
	}
	dirlist->clear();
	directory->refresh();
	for (cnt = 0; cnt < directory->entryList().count(); cnt++) {
		dirlist->addItem(directory->entryList().at(cnt));
	}
	return 0;
}

int C0702_Dir::renameDir() {
	int cnt;
	if (!fileName->text().length()) {
		directory->rename(dirlist->currentItem()->text(), fileName->text());
	}
	dirlist->clear();
	directory->refresh();
	for (cnt = 0; cnt < directory->entryList().count(); cnt++) {
		dirlist->addItem(directory->entryList().at(cnt));
	}
	return 0;
}



