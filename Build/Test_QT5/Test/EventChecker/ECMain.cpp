
#include "../TestBase.h"
#include "./ECMain.h"

#include "WndScreen.h"

std::string ToBuildDateString(char szDelim = '-') {
	const std::string strMonthList[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun",
		"Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
	std::string strMonth;
	unsigned short nDay = 0, nMonth = 0, nYear = 0;
	std::istringstream iss(__DATE__);	iss >> strMonth >> nDay >> nYear;
	for (int nIdx = 0; nIdx < 12; nIdx++) {
		if (strMonth.compare(strMonthList[nIdx]) == 0) {
			nMonth = nIdx + 1;	break;
		}
	}
	std::ostringstream oss;	
	oss << std::setw(4) << std::setfill('0') << std::right << nYear;
	if (szDelim != 0) oss << szDelim;
	oss << std::setw(2) << std::setfill('0') << std::right << nMonth;
	if (szDelim != 0) oss << szDelim;
	oss << std::setw(2) << std::setfill('0') << std::right << nDay;
	return oss.str();
}

std::string ToBuildTimeString(char szDelim = ':') {
	char szTemp = 0;
	unsigned short nHour = 0, nMinute = 0, nSecond = 0;
	std::istringstream iss(__TIME__);	iss >> nHour >> szTemp >> nMinute >> szTemp >> nSecond;
	std::ostringstream oss;
	oss << std::setw(2) << std::setfill('0') << std::right << nHour;
	if (szDelim != 0) oss << szDelim;
	oss << std::setw(2) << std::setfill('0') << std::right << nMinute;
	if (szDelim != 0) oss << szDelim;
	oss << std::setw(2) << std::setfill('0') << std::right << nSecond;
	return oss.str();
}

ECMainWnd::ECMainWnd(ECUIEvent* pEvent) {
	m_pEvent = pEvent;

	std::string strBuildDate = ToBuildDateString();
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
	m_pWndScreen->move(10, 10);	m_pWndScreen->resize(640, 480);
	m_nDivType = DIV_1;	
	m_pWndScreen->SetDivision(m_nDivType);

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
	//startTimer(1000);

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
	case DIV_1:		{ m_nDivType = DIV_4;	break; }
	case DIV_4:		{ m_nDivType = DIV_9;	break; }
	case DIV_9:		{ m_nDivType = DIV_16;	break; }
	case DIV_16:	{ m_nDivType = DIV_24;	break; }
	case DIV_24:	{ m_nDivType = DIV_1;	break; }
	default:		
		return;
	}
	m_pWndScreen->SetDivision(m_nDivType);
}

void ECMainWnd::onClick_DIV_1() {

}

void ECMainWnd::onClick_DIV_4() {
}
void ECMainWnd::onClick_DIV_9() {
}
void ECMainWnd::onClick_DIV_16() {
}
void ECMainWnd::onClick_DIV_24() {
}


