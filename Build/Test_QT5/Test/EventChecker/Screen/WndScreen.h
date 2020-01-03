
#pragma once

#include "../../TestBase.h"
#include "../ECType.h"

class CWndCell;
class CWndScreenInner;
class CWndScreen : public QWidget {
	Q_OBJECT
public:
	enum {
		DetectAreaNum		= 2,							// ���� ���� ����
	};

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
	bool						m_bIsResized;		//!< ȭ�� ũ�Ⱑ ���� �Ǿ����� ����(true: ȭ�� ũ�� �����)

	CWndScreenInner*			m_pWndInner;

public:
	CWndScreen(QWidget *pParent = nullptr);
	virtual ~CWndScreen();

	ECDivTypeEnum GetDivType();

	//!	@brief	ȭ�� ����
	//!	@param	nDivType		[in] ���� ȭ�� ����
	//!	@oaran	nBeginChIdx		[in] ���� ȭ�� �ε���(0���� ����)
	void SetDivision(ECDivTypeEnum nDivType, int nBeginChIdx = -1);

	//!	@brief	ȭ�� �̹��� ����
	//!	@param	nChIdx			[in] ��� ȭ�� �ε���(0���� ����)
	//!	@param	pBuf			[in] �̹��� ����
	//!	@return	true �� ���� ����
	bool SetChImage(int nChIdx, QPixmap* pBuf);

	//!	@brief	ȭ�� �׸� ���� ����
	//!	@param	nChIdx			[in] ��� ȭ�� �ε���(0���� ����)
	//!	@param	di				[in] �׸� ����
	//!	@return ���� ����
	bool SetDrawInfo(int nChIdx, ECDrawInfo &di);

	//!	@brief	���� �ε��� �� ���� ����
	//!	@param	nAreaIdx		[in] ���� �ε���(0���� ����)
	//!	@param	areaColor		[in] ���� ����
	void SetAreaColor(int nAreaIdx, QColor &areaColor);

private:
	virtual void resizeEvent(QResizeEvent *pEvent) override;
	virtual void timerEvent(QTimerEvent *pEvent) override;
	virtual void mouseDoubleClickEvent(QMouseEvent *event) override;
	
};