
#pragma once

#include "../EventChecker/Screen/WndScreen.h"
#include "../TestBase.h"

class T002_MultiScene : public QWidget {
	Q_OBJECT
private:
	const static int TEST_IMG_NUM = 24;	// 4;
	QImage					*m_pImg[TEST_IMG_NUM];
	QPixmap					*m_pBuf[TEST_IMG_NUM];

	std::thread*			m_pTestThread;
	std::atomic<bool>		m_bIsTesting;
	std::atomic<bool>		m_bTestThreadAlive;

	QVBoxLayout				m_layout;
	QHBoxLayout				m_layout_btn;
	CWndScreen				m_wndScreen;
	QPushButton				m_btn_DIV1;
	QPushButton				m_btn_DIV4;
	QPushButton				m_btn_DIV9;
	QPushButton				m_btn_DIV16;
	QPushButton				m_btn_DIV24;
	QPushButton				m_btn_FullScreen;
	QPushButton				m_btn_test1;

	bool					m_bIsFullScreen;

public:
	T002_MultiScene(QWidget* parent = Q_NULLPTR) : QWidget(parent) {
		std::srand(time(nullptr));
		m_bIsFullScreen = false;
		m_bTestThreadAlive = true;	m_bIsTesting = false;
		//const QString imgPath[TEST_IMG_NUM] = {
		//	"../Res/ch1.bmp", "../Res/ch2.bmp", "../Res/ch3.bmp", "../Res/ch4.bmp",
		//};
		const QString imgPath[TEST_IMG_NUM] = {
			"../Res/image1.png", "../Res/image2.png", "../Res/image3.png", "../Res/image4.png", "../Res/image5.png",
			"../Res/image6.png", "../Res/image7.png", "../Res/image8.png", "../Res/image9.png", "../Res/image10.png",
			"../Res/image11.png", "../Res/image12.png", "../Res/image13.png", "../Res/image14.png", "../Res/image15.png",
			"../Res/image16.png", "../Res/image17.png", "../Res/image18.png", "../Res/image19.png", "../Res/image20.png",
			"../Res/image21.png", "../Res/image22.png", "../Res/image23.png", "../Res/image24.png"
		};
		bool bRet = true;
		int nIdx = 0;
		for (nIdx = 0; bRet && nIdx < TEST_IMG_NUM; nIdx++) {
			m_pImg[nIdx] = new QImage();	m_pBuf[nIdx] = new QPixmap();
			bRet &= m_pImg[nIdx]->load(imgPath[nIdx]);
			if (bRet == false) break;
		}
		if (bRet == false) { qWarning("Failed to load image."); return; }
		for (nIdx = 0; bRet && nIdx < TEST_IMG_NUM; nIdx++) {
			*m_pBuf[nIdx] = QPixmap::fromImage(*m_pImg[nIdx]);
			bRet &= (m_pBuf[nIdx] && m_pBuf[nIdx]->size().isValid());
		}
		if (bRet == false) { qWarning("Failed to get image data.");	return; }

		m_btn_DIV1.setText(QString::fromLocal8Bit(" 1 채널"));	
		m_btn_DIV4.setText(QString::fromLocal8Bit(" 4 채널"));		
		m_btn_DIV9.setText(QString::fromLocal8Bit(" 9 채널"));		
		m_btn_DIV16.setText(QString::fromLocal8Bit("16 채널"));		
		m_btn_DIV24.setText(QString::fromLocal8Bit("24 채널"));		
		m_btn_FullScreen.setText(QString::fromLocal8Bit("전체화면"));
		m_btn_test1.setText(QString::fromLocal8Bit("채널전환 테스트 시작"));

		connect(&m_btn_DIV1, &QPushButton::clicked, this, &T002_MultiScene::OnClick_DIV1);
		connect(&m_btn_DIV4, &QPushButton::clicked, this, &T002_MultiScene::OnClick_DIV4);
		connect(&m_btn_DIV9, &QPushButton::clicked, this, &T002_MultiScene::OnClick_DIV9);
		connect(&m_btn_DIV16, &QPushButton::clicked, this, &T002_MultiScene::OnClick_DIV16);
		connect(&m_btn_DIV24, &QPushButton::clicked, this, &T002_MultiScene::OnClick_DIV24);
		connect(&m_btn_FullScreen, &QPushButton::clicked, this, &T002_MultiScene::OnClick_FullScreen);
		connect(&m_btn_test1, &QPushButton::clicked, this, &T002_MultiScene::OnClick_test1);
		
		m_layout_btn.addWidget(&m_btn_DIV1);
		m_layout_btn.addWidget(&m_btn_DIV4);
		m_layout_btn.addWidget(&m_btn_DIV9);
		m_layout_btn.addWidget(&m_btn_DIV16);
		m_layout_btn.addWidget(&m_btn_DIV24);
		m_layout_btn.addWidget(&m_btn_FullScreen);
		m_layout_btn.addWidget(&m_btn_test1);

		m_layout.addWidget(&m_wndScreen);	//m_grid.addWidget(&m_wndScreen, 0, 0);
		m_layout.addLayout(&m_layout_btn);	// m_grid.addWidget(&m_testBtn, 1, 0);
		setLayout(&m_layout);				//setLayout(&m_grid);

		int nBeginIdx = rand() % (int)ECDivTypeEnum::MAX_DIV;
		m_wndScreen.SetDivision(ECDivTypeEnum::DIV_24, nBeginIdx);

		startTimer(1000);		// 일정 주기로 화면분할 요청 진행

		m_pTestThread = new std::thread(&T002_MultiScene::OnTestThreadProc, this);	// 이미지 추가 스레드 동작
	}
	virtual ~T002_MultiScene() {
		m_bTestThreadAlive = false;
		if (m_pTestThread) {
			m_pTestThread->join();
			delete m_pTestThread;	m_pTestThread = nullptr;
		}

		for (int nIdx = 0; nIdx < TEST_IMG_NUM; nIdx++) {
			if (m_pBuf[nIdx]) { delete[] m_pBuf[nIdx]; m_pBuf[nIdx] = nullptr; }
			if (m_pImg[nIdx]) { delete[] m_pImg[nIdx]; m_pImg[nIdx] = nullptr; }
		}
	}
	bool SetUIEvent(ECUIEvent* pEvent) {
		return false;
	}
	bool SetChImage(int nChIdx, QPixmap* pBuf) {
		return m_wndScreen.SetChImage(nChIdx, pBuf);
	}

	void ToggleFullScreen() {
		if (m_bIsFullScreen == false) {
			m_btn_DIV1.hide();	m_btn_DIV4.hide();	m_btn_DIV9.hide();	m_btn_DIV16.hide();	m_btn_DIV24.hide(); 
			m_btn_FullScreen.hide();	m_btn_test1.hide();
			showFullScreen();
		}
		else {
			m_btn_DIV1.show();	m_btn_DIV4.show();	m_btn_DIV9.show();	m_btn_DIV16.show();	m_btn_DIV24.show();
			m_btn_FullScreen.show();	m_btn_test1.show();
			showNormal();
		}
		m_bIsFullScreen = !m_bIsFullScreen;
	}

protected:
	void timerEvent(QTimerEvent *pEvent) override {

		if (m_bIsTesting == false) return;

		int nMaxDiv = static_cast<int>(ECDivTypeEnum::MAX_DIV);
		//int nBeginChIdx = 0;
		int nBeginChIdx = rand() % nMaxDiv;
		
		ECDivTypeEnum nDivType = m_wndScreen.GetDivType();

		switch (nDivType) {
		case ECDivTypeEnum::DIV_1:	{ nDivType = ECDivTypeEnum::DIV_4;	break; }
		case ECDivTypeEnum::DIV_4:	{ nDivType = ECDivTypeEnum::DIV_9;	break; }
		case ECDivTypeEnum::DIV_9:	{ nDivType = ECDivTypeEnum::DIV_16;	break; }
		case ECDivTypeEnum::DIV_16:	{ nDivType = ECDivTypeEnum::DIV_24;	break; }
		case ECDivTypeEnum::DIV_24:	{ nDivType = ECDivTypeEnum::DIV_1;	break; }
		default:
			return;
		}

		std::ostringstream ossLog;
		int nDivNum = static_cast<int>(nDivType);
		int nDivMax = static_cast<int>(ECDivTypeEnum::MAX_DIV);
		int nChIdx = nBeginChIdx;
		ossLog << "[SetDivision] DIV(" << nDivNum << ") BEGIN(" << (nChIdx + 1) << ") ";
		for (int nDivIdx = 0; nDivIdx < nDivNum; nDivIdx++) {
			ossLog << (nChIdx + 1) << " ";
			nChIdx = (nChIdx + 1) % nDivMax;
		}
		//qDebug(ossLog.str().c_str());
		m_wndScreen.SetDivision(nDivType, nBeginChIdx);
	}

	//	주기적으로 임의의 채널 이미지 추가
	void OnTestThreadProc() {
		bool bIsFirstCall = true;
		while (m_bTestThreadAlive) {
			std::this_thread::sleep_for(std::chrono::milliseconds(2000));

			if (m_bIsTesting || bIsFirstCall) {
				int nChIdx = 0, nImgIdx = 0;
				int nMaxDiv = static_cast<int>(ECDivTypeEnum::MAX_DIV);
				QPixmap* pBuf = nullptr;
				for (int nChIdx = 0; (m_bIsTesting || bIsFirstCall) && nChIdx < nMaxDiv; nChIdx++) {
					nImgIdx = rand() % TEST_IMG_NUM;
					pBuf = m_pBuf[nImgIdx];
					if (m_wndScreen.SetChImage(nChIdx, pBuf) == false) {
						qWarning("Failed to set channel image. ch(%d)", nChIdx);
					}
				}
				bIsFirstCall = false;
			}
		}
	}

	//	채널 이미지 추가(1회)
	//void OnTestThreadProc() {
	//	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	//	int nChIdx = 0, nImgIdx = 0;
	//	int nMaxDiv = static_cast<int>(ECDivTypeEnum::MAX_DIV);
	//	QPixmap* pBuf = nullptr;
	//	for (int nChIdx = 0; m_bIsTesting && nChIdx < nMaxDiv; nChIdx++) {
	//		nImgIdx = rand() % TEST_IMG_NUM;
	//		pBuf = m_pBuf[nImgIdx];
	//		if (m_wndScreen.SetChImage(nChIdx, pBuf) == false) {
	//			qWarning("Failed to set channel image. ch(%d)", nChIdx);
	//		}
	//	}
	//}

	virtual void keyReleaseEvent(QKeyEvent *pEvent) {
		int nKey = pEvent->key();
		switch (nKey) {
		default:	return;
		case Qt::Key_Escape:
			if (m_bIsFullScreen) ToggleFullScreen();
			break;
		}
	}

	void OnClick_DIV1() {
		int nMaxDiv = static_cast<int>(ECDivTypeEnum::MAX_DIV);
		int nBeginChIdx = rand() % nMaxDiv;
		m_wndScreen.SetDivision(ECDivTypeEnum::DIV_1, nBeginChIdx);
	}
	void OnClick_DIV4() {
		int nMaxDiv = static_cast<int>(ECDivTypeEnum::MAX_DIV);
		int nBeginChIdx = rand() % nMaxDiv;
		m_wndScreen.SetDivision(ECDivTypeEnum::DIV_4, nBeginChIdx);
	}
	void OnClick_DIV9() {
		int nMaxDiv = static_cast<int>(ECDivTypeEnum::MAX_DIV);
		int nBeginChIdx = rand() % nMaxDiv;
		m_wndScreen.SetDivision(ECDivTypeEnum::DIV_9, nBeginChIdx);
	}
	void OnClick_DIV16() {
		int nMaxDiv = static_cast<int>(ECDivTypeEnum::MAX_DIV);
		int nBeginChIdx = rand() % nMaxDiv;
		m_wndScreen.SetDivision(ECDivTypeEnum::DIV_16, nBeginChIdx);
	}
	void OnClick_DIV24() {
		int nMaxDiv = static_cast<int>(ECDivTypeEnum::MAX_DIV);
		int nBeginChIdx = rand() % nMaxDiv;
		m_wndScreen.SetDivision(ECDivTypeEnum::DIV_24, nBeginChIdx);
	}
	void OnClick_FullScreen() {
		ToggleFullScreen();
	}
	void OnClick_test1() {
		if (m_bIsTesting == false) {
			m_bIsTesting = true;
			m_btn_test1.setText(QString::fromLocal8Bit("화면전환 테스트 중지"));
		}
		else {
			m_bIsTesting = false;
			m_btn_test1.setText(QString::fromLocal8Bit("화면전환 테스트 시작"));
		}
	}
};

class T002_MultiSceneTest : public ITestObject {
private:
	
	class ECUIHandler : public ECUIEvent {
	} m_eventHandler;
	T002_MultiScene		*m_pMainWnd;

public:
	T002_MultiSceneTest() {
		m_pMainWnd = nullptr;
	}
	virtual int OnTest(int nArgNum, char **ppArgs) {
		int nRet = 0;
		QApplication app(nArgNum, ppArgs);
		if (OnInit() == false) {
			qWarning("Failed to initialize app. \n");
		}
		else {
			m_pMainWnd = new T002_MultiScene();
			m_pMainWnd->resize(1280, 720);
			m_pMainWnd->show();
			nRet = app.exec();
		}
		OnDestroy();
		return nRet;
	}
protected:
	bool OnInit() {
		
		return true;
	}
	void OnDestroy() {
		if (m_pMainWnd) { delete m_pMainWnd;	m_pMainWnd = nullptr; }
		
	}
};

