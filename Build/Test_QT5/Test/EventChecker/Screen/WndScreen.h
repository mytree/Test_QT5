
#pragma once

#include "../../TestBase.h"
#include "../ECType.h"

class CWndCell;
class CWndScreenInner;
class CWndScreen : public QWidget {
	Q_OBJECT
public:
	enum {
		DetectAreaNum		= 2,							// 검지 영역 개수
	};

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
	int							m_nBeginChIdx;		//!< 현재 시작 채널 인덱스(0 ~ MAX_DIV)
	bool						m_bIsFirstCallDiv;	//!< 분할 요청이 안 되었는지 유무(true: 아직 호출 안 됨)
	bool						m_bIsResized;		//!< 화면 크기가 변경 되었는지 여부(true: 화면 크기 변경됨)

	CWndScreenInner*			m_pWndInner;

public:
	CWndScreen(QWidget *pParent = nullptr);
	virtual ~CWndScreen();

	ECDivTypeEnum GetDivType();

	//!	@brief	화면 분할
	//!	@param	nDivType		[in] 분할 화면 종류
	//!	@oaran	nBeginChIdx		[in] 시작 화면 인덱스(0부터 시작)
	void SetDivision(ECDivTypeEnum nDivType, int nBeginChIdx = -1);

	//!	@brief	화면 이미지 설정
	//!	@param	nChIdx			[in] 출력 화면 인덱스(0부터 시작)
	//!	@param	pBuf			[in] 이미지 정보
	//!	@return	true 는 설정 성공
	bool SetChImage(int nChIdx, QPixmap* pBuf);

	//!	@brief	화면 그림 정보 설정
	//!	@param	nChIdx			[in] 출력 화면 인덱스(0부터 시작)
	//!	@param	di				[in] 그림 정보
	//!	@return 성공 여부
	bool SetDrawInfo(int nChIdx, ECDrawInfo &di);

	//!	@brief	영역 인덱스 별 색상 정의
	//!	@param	nAreaIdx		[in] 영역 인덱스(0부터 시작)
	//!	@param	areaColor		[in] 영역 색상
	void SetAreaColor(int nAreaIdx, QColor &areaColor);

private:
	virtual void resizeEvent(QResizeEvent *pEvent) override;
	virtual void timerEvent(QTimerEvent *pEvent) override;
	virtual void mouseDoubleClickEvent(QMouseEvent *event) override;
	
};