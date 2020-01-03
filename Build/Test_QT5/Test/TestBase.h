
#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <ctime>
#include <iomanip>
#include <thread>
#include <chrono>
#include <atomic>
#include <mutex>
#include <vector>
#include <map>

//--------------------------------------------------------------------------
//	메모리 누수 검사 목적
#ifndef __linux__
#	define _CRTDBG_MAP_ALLOC
#	include <stdlib.h>
#	include <crtdbg.h>
#endif
//--------------------------------------------------------------------------

#define cout_post_sz(text, ch, num) { \
	std::string strText(text);	strText += " ";	unsigned int nTextSize = strText.size(); \
	unsigned int nRemainedNum = (num > nTextSize) ? num - (nTextSize) : 0; \
	std::ostringstream oss; oss << strText; \
	if (nRemainedNum > 0) oss << std::string(nRemainedNum, ch); \
	oss << std::endl; \
	std::cout << oss.str(); \
}

namespace CUtil {
	std::string ToBuildDateString(char szDelim = '-');
	std::string ToBuildTimeString(char szDelim = ':');
}

#include "QTDef.h"

struct ITestObject {
public:
	virtual ~ITestObject() {}
	virtual int OnTest(int nArgNum, char** ppArgs) = 0;
};