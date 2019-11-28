
#include "./TestBase.h"

using namespace CUtil;

std::string CUtil::ToBuildDateString(char szDelim) {
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

std::string CUtil::ToBuildTimeString(char szDelim) {
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
