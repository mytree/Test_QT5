
#pragma once

#include "QTDef.h"

struct ITestObject {
public:
	virtual ~ITestObject() {}
	virtual int OnTest(int nArgNum, char** ppArgs) = 0;
};