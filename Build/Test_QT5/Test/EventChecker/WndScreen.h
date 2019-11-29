
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
	QString					m_strTitleTop;

public:
	CWndCell(QWidget *parent = nullptr);
	void SetFrameRectColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);
	void SetTitleText(QString strText);

protected:
	inline void setText(const QString &atext) = delete;

private:
	virtual void paintEvent(QPaintEvent *event) override;

	void paintTitle(QPainter &qp, QRect rtArea);
};

class CWndScreen : public QWidget {
	Q_OBJECT
public:
	using ChList = std::vector<CWndCell*>;
	using ChIter = std::vector<CWndCell*>::iterator;
	using ImgList = std::map<int, QPixmap*>;				// [ä���ε���(0���ͽ���), QPixmap]
	using ImgIter = std::map<int, QPixmap*>::iterator;
	using RecvList = std::map<int, bool>;					// [ä���ε���(0���ͽ���), �̹������ſ���]
	using RecvIter = std::map<int, bool>::iterator;

private:
	std::mutex					m_chListMutex;
	ChList						m_chList;			//!< Grid �� Cell ���
	ImgList						m_imgList;			//!< Cell �� ���� �̹��� ���
	RecvList					m_recvList;			//!< �̹��� ���� ���� ���

	QGridLayout					m_grid;				//!< Grid ������ Layout ���� ���
	ECDivTypeEnum				m_nDivType;			//!< ���� ���� ����
	int							m_nBeginChIdx;		//!< ���� ���� ä�� �ε���(0 ~ MAX_DIV)
	bool						m_bIsFirstCallDiv;	//!< ���� ��û�� �� �Ǿ����� ����(true: ���� ȣ�� �� ��)

	bool						m_bIsFullScreen;
	QPoint						m_parentPos;

public:
	CWndScreen(QWidget *pParent = nullptr);
	virtual ~CWndScreen();

	ECDivTypeEnum GetDivType();

	void SetDivision(ECDivTypeEnum nDivType, int nBeginChIdx = -1);
	bool SetChImage(int nChIdx, QPixmap* pBuf);

private:
	virtual void resizeEvent(QResizeEvent *pEvent) override;
	virtual void timerEvent(QTimerEvent *pEvent) override;
	
};