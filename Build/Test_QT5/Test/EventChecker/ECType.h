
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
using ECPolylineList = std::map<int, ECPointList>;				// [�����ε���(0���ͽ���), ��������]
using ECPolylineIter = std::map<int, ECPointList>::iterator;
using ECAreaColorList = std::map<int, QColor>;					// [�����ε���(0���ͽ���), ��������]
using ECAreaColorIter = std::map<int, QColor>::iterator;

////!	@brief	���� ���� ����
//struct ECDetectAreaInfo {
//	QSize			canvasSize;		//!< �ػ�
//	ECPolylineList	lineList;		//!< ���� ���
//	QColor			lineColor;		//!< �� ����
//};
//
////!	@brief	�̺�Ʈ �߻� ���� ����
//struct ECEventAreaInfo {
//	QSize			canvasSize;		//!< �ػ�
//	QPoint			pos;			//!< ���� �»�� ��ǥ
//	QSize			size;			//!< ���� ũ��
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

	QSize						canvasSize;			//!< �ػ�
	ECPolylineList				lineList;			//!< ���� ���
	ECAreaColorList				lineColorList;		//!< �� ����

	ECDrawInfo() {
		nFrameRectR = nFrameRectG = nFrameRectB = 0; nFrameRectA = 255;
		nTitleTopAlign = nTitleBottomAlign = Qt::AlignmentFlag::AlignLeft;
	}

};

class ECUIEvent {
public:

};

