
#pragma once

#include "../EventChecker/WndScreen.h"
#include "../TestBase.h"

class T002_MultiScene : public QWidget {
	Q_OBJECT
private:
	const static int TEST_IMG_NUM = 4;
	QImage					*m_pImg[TEST_IMG_NUM];
	QPixmap					*m_pBuf[TEST_IMG_NUM];

	std::thread*			m_pTestThread;
	std::atomic<bool>		m_bIsTesting;

	QGridLayout				m_grid;
	CWndScreen				m_wndScreen;

	
public:
	T002_MultiScene(QWidget* parent = Q_NULLPTR) : QWidget(parent) {
		m_bIsTesting = true;
		const QString imgPath[TEST_IMG_NUM] = {
			"../Res/ch1.bmp", "../Res/ch2.bmp", "../Res/ch3.bmp", "../Res/ch4.bmp",
		};
		bool bRet = true;
		int nIdx = 0;
		for (nIdx = 0; bRet && nIdx < TEST_IMG_NUM; nIdx++) {
			m_pImg[nIdx] = new QImage();	m_pBuf[nIdx] = new QPixmap();
			bRet &= m_pImg[nIdx]->load(imgPath[nIdx]);
		}
		if (bRet == false) { qWarning("Failed to load image."); return; }
		for (nIdx = 0; bRet && nIdx < TEST_IMG_NUM; nIdx++) {
			*m_pBuf[nIdx] = QPixmap::fromImage(*m_pImg[nIdx]);
			bRet &= (m_pBuf[nIdx] && m_pBuf[nIdx]->size().isValid());
		}
		if (bRet == false) { qWarning("Failed to get image data.");	return; }

		m_grid.addWidget(&m_wndScreen, 0, 0);
		setLayout(&m_grid);

		startTimer(1000);

		m_pTestThread = new std::thread(&T002_MultiScene::OnTestThreadProc, this);
	}
	virtual ~T002_MultiScene() {
		m_bIsTesting = false;
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

protected:
	void timerEvent(QTimerEvent *pEvent) override {

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
		m_wndScreen.SetDivision(nDivType);
	}

	void OnTestThreadProc() {

		while (m_bIsTesting) {
			std::this_thread::sleep_for(std::chrono::milliseconds(100));

			int nChIdx = 0, nImgIdx = 0;
			int nMaxDiv = static_cast<int>(ECDivTypeEnum::MAX_DIV);
			QPixmap* pBuf = nullptr;
			for (int nChIdx = 0; m_bIsTesting && nChIdx < nMaxDiv; nChIdx++) {
				nImgIdx = rand() % TEST_IMG_NUM;
				pBuf = m_pBuf[nImgIdx];
				if (m_wndScreen.SetChImage(nChIdx, pBuf) == false) {
					qWarning("Failed to set channel image. ch(%d)", nChIdx);
				}
			}
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

