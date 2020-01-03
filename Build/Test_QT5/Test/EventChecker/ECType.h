
#pragma once

enum class ECDivTypeEnum {
	DIV_1 = 1, 
	DIV_4 = 4, 
	DIV_9 = 9, 
	DIV_16 = 16, 
	DIV_24 = 24,

	MAX_DIV = DIV_24,
};

using ECPointList = std::vector<QPoint>;
using ECPointIter = std::vector<QPoint>::iterator;
using ECPolylineList = std::map<int, ECPointList>;				// [영역인덱스(0부터시작), 영역정보]
using ECPolylineIter = std::map<int, ECPointList>::iterator;
using ECAreaColorList = std::map<int, QColor>;					// [영역인덱스(0부터시작), 색상정보]
using ECAreaColorIter = std::map<int, QColor>::iterator;

////!	@brief	검지 영역 정보
//struct ECDetectAreaInfo {
//	QSize			canvasSize;		//!< 해상도
//	ECPolylineList	lineList;		//!< 영역 목록
//	QColor			lineColor;		//!< 선 색상
//};
//
////!	@brief	이벤트 발생 영역 정보
//struct ECEventAreaInfo {
//	QSize			canvasSize;		//!< 해상도
//	QPoint			pos;			//!< 영역 좌상단 좌표
//	QSize			size;			//!< 영역 크기
//};

struct ECDrawInfo {
	unsigned char				nFrameRectR;
	unsigned char				nFrameRectG;
	unsigned char				nFrameRectB;
	unsigned char				nFrameRectA;
	QString						strTitleTop;
	Qt::AlignmentFlag			nTitleTopAlign;
	QString						strTitleBottom;
	Qt::AlignmentFlag			nTitleBottomAlign;

	QSize						canvasSize;			//!< 해상도
	ECPolylineList				lineList;			//!< 영역 목록
	ECAreaColorList				lineColorList;		//!< 선 색상

	ECDrawInfo() {
		nFrameRectR = nFrameRectG = nFrameRectB = 0; nFrameRectA = 255;
		nTitleTopAlign = nTitleBottomAlign = Qt::AlignmentFlag::AlignLeft;
	}

};

class ECUIEvent {
public:

};

