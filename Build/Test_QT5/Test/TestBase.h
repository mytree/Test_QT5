
#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <ctime>

#define cout_post_sz(text, ch, num) { \
	std::string strText(text);	strText += " ";	unsigned int nTextSize = strText.size(); \
	unsigned int nRemainedNum = (num > nTextSize) ? num - (nTextSize) : 0; \
	std::ostringstream oss; oss << strText; \
	if (nRemainedNum > 0) oss << std::string(nRemainedNum, ch); \
	oss << std::endl; \
	std::cout << oss.str(); \
}

#include "QTDef.h"

struct ITestObject {
public:
	virtual ~ITestObject() {}
	virtual int OnTest(int nArgNum, char** ppArgs) = 0;
};