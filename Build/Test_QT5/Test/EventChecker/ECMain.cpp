
#include "../TestBase.h"
#include "./ECMain.h"

#include "WndScreen.h"

ECMainWnd::ECMainWnd(ECUIEvent* pEvent) {
	m_pEvent = pEvent;

	std::string strBuildDate = CUtil::ToBuildDateString();
	//std::string strBuildTime = ToBuildTimeString(0);
	std::string strTitle = "EventChecker(" + strBuildDate + ")";	// +"_" + strBuildTime;
	setWindowTitle(strTitle.c_str());
	setFixedSize(960, 600);	//setFixedSize(800, 600);		//setFixedSize(1024, 720); 

	m_pDiv1 = new QPushButton();	m_pDiv1->setText("Div 1");
	m_pDiv4 = new QPushButton();	m_pDiv4->setText("Div 4");
	m_pDiv9 = new QPushButton();	m_pDiv9->setText("Div 9");
	m_pDiv16 = new QPushButton();	m_pDiv16->setText("Div 16");
	m_pDiv24 = new QPushButton();	m_pDiv24->setText("Div 24");

	m_pWndScreen = new CWndScreen(this);
	//m_pWndScreen->move(10, 10);	m_pWndScreen->resize(640, 480);	//m_pWndScreen->update();
	
	m_pHBox = new QHBoxLayout();
	m_pHBox->addWidget(m_pDiv1);
	m_pHBox->addWidget(m_pDiv4);
	m_pHBox->addWidget(m_pDiv9);
	m_pHBox->addWidget(m_pDiv16);
	m_pHBox->addWidget(m_pDiv24);
	
	m_pVBox = new QVBoxLayout();
	m_pVBox->addWidget(m_pWndScreen);
	m_pVBox->addLayout(m_pHBox);
	
	setLayout(m_pVBox);
	startTimer(1000);

	m_nDivType = ECDivTypeEnum::DIV_1;
	m_pWndScreen->SetDivision(m_nDivType, 0);

	connect(m_pDiv1, &QPushButton::clicked, this, &ECMainWnd::onClick_DIV_1);
	connect(m_pDiv4, &QPushButton::clicked, this, &ECMainWnd::onClick_DIV_4);
	connect(m_pDiv9, &QPushButton::clicked, this, &ECMainWnd::onClick_DIV_9);
	connect(m_pDiv16, &QPushButton::clicked, this, &ECMainWnd::onClick_DIV_16);
	connect(m_pDiv24, &QPushButton::clicked, this, &ECMainWnd::onClick_DIV_24);
}

ECMainWnd::~ECMainWnd() {
	if (m_pWndScreen) { delete m_pWndScreen;	m_pWndScreen = nullptr; }
	if (m_pDiv1) { delete m_pDiv1;			m_pDiv1 = nullptr; }
	if (m_pDiv4) { delete m_pDiv4;			m_pDiv4 = nullptr; }
	if (m_pDiv9) { delete m_pDiv9;			m_pDiv9 = nullptr; }
	if (m_pDiv16) { delete m_pDiv16;		m_pDiv16 = nullptr; }
	if (m_pDiv24) { delete m_pDiv24;		m_pDiv24 = nullptr; }
	if (m_pHBox) { delete m_pHBox;			m_pHBox = nullptr; }
	if (m_pVBox) { delete m_pVBox;			m_pVBox = nullptr; }
}

void ECMainWnd::timerEvent(QTimerEvent *pEvent) {

	switch (m_nDivType) {
	case ECDivTypeEnum::DIV_1:	{ m_nDivType = ECDivTypeEnum::DIV_4;	break; }
	case ECDivTypeEnum::DIV_4:	{ m_nDivType = ECDivTypeEnum::DIV_9;	break; }
	case ECDivTypeEnum::DIV_9:	{ m_nDivType = ECDivTypeEnum::DIV_16;	break; }
	case ECDivTypeEnum::DIV_16:	{ m_nDivType = ECDivTypeEnum::DIV_24;	break; }
	case ECDivTypeEnum::DIV_24:	{ m_nDivType = ECDivTypeEnum::DIV_1;	break; }
	default:		
		return;
	}
	m_pWndScreen->SetDivision(m_nDivType, 0);
}

void ECMainWnd::onClick_DIV_1() {
	if (m_pWndScreen) {
		m_pWndScreen->SetDivision(ECDivTypeEnum::DIV_1);
	}
}

void ECMainWnd::onClick_DIV_4() {
	if (m_pWndScreen) {
		m_pWndScreen->SetDivision(ECDivTypeEnum::DIV_4);
	}
}
void ECMainWnd::onClick_DIV_9() {
	if (m_pWndScreen) {
		m_pWndScreen->SetDivision(ECDivTypeEnum::DIV_9);
	}
}
void ECMainWnd::onClick_DIV_16() {
	if (m_pWndScreen) {
		m_pWndScreen->SetDivision(ECDivTypeEnum::DIV_16);
	}
}
void ECMainWnd::onClick_DIV_24() {
	if (m_pWndScreen) {
		m_pWndScreen->SetDivision(ECDivTypeEnum::DIV_24);
	}
}


