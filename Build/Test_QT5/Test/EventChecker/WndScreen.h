
#pragma once

#include "ECUIEvent.h"
#include "../TestBase.h"

class CWndCell : public QLabel {
	Q_OBJECT
private:
	unsigned char			m_nFrameRectR;
	unsigned char			m_nFrameRectG;
	unsigned char			m_nFrameRectB;
	unsigned char			m_nFrameRectA;

public:
	CWndCell(QWidget *parent = nullptr);
	void SetFrameRectColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);

private:
	virtual void paintEvent(QPaintEvent *event) override;
};

class CWndScreen : public QWidget {
	Q_OBJECT
public:
	using ChList = std::vector<CWndCell*>;
	using ChIter = std::vector<CWndCell*>::iterator;
	using ImgList = std::map<int, QPixmap*>;				// [채널인덱스(0부터시작), QPixmap]
	using ImgIter = std::map<int, QPixmap*>::iterator;
	using RecvList = std::map<int, bool>;					// [채널인덱스(0부터시작), 이미지수신여부]
	using RecvIter = std::map<int, bool>::iterator;

private:
	std::mutex					m_chListMutex;
	ChList						m_chList;			//!< Grid 내 Cell 목록
	ImgList						m_imgList;			//!< Cell 에 들어가는 이미지 목록
	RecvList					m_recvList;			//!< 이미지 수신 유무 목록

	QGridLayout					m_grid;				//!< Grid 형식의 Layout 구성 담당
	ECDivTypeEnum				m_nDivType;			//!< 현재 분할 종류

public:
	CWndScreen(QWidget *pParent = nullptr);
	virtual ~CWndScreen();

	ECDivTypeEnum GetDivType();

	void SetDivision(ECDivTypeEnum nDivType);
	bool SetChImage(int nChIdx, QPixmap* pBuf);

private:
	virtual void resizeEvent(QResizeEvent *pEvent) override;
	virtual void timerEvent(QTimerEvent *pEvent) override;

};