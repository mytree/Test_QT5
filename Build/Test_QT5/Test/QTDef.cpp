
#include "QTDef.h"

using namespace QUtil;
	
bool QUtil::ConvertBGR24ToQImage(QImage &convImg, unsigned char* pSrcData, int nSrcW, int nSrcH) {
	int nSize = nSrcW * nSrcH * 3;
	if (nSize <= 0) return false;
	convImg = QImage::fromData(pSrcData, nSize, "BMP");
	int nImgByte = convImg.byteCount();
	if (nImgByte < nSize) return false;
	convImg = convImg.rgbSwapped();
	return true;
}

bool QUtil::ConvertARGB32ToQImage(QImage &convImg, unsigned char* pSrcData, int nSrcW, int nSrcH) {
	int nSize = nSrcW * nSrcH * 4;
	if (nSize <= 0) return false;
	convImg = QImage::fromData(pSrcData, nSize, "BMP");
	int nImgByte = convImg.byteCount();
	if (nImgByte < nSize) return false;
	return true;
}


