#pragma once

#ifndef _API_FUNCTION_MGR_
#define _API_FUNCTION_MGR_

#include <vector>
#include <string>
#include "ApiTypeDefine.h"
#include "SimpleLog.h"

class ApiFunctionMgr
{
public:
    ApiFunctionMgr(){};
    virtual ~ApiFunctionMgr(){
        ReleaseFunctions();
    };
public:
    int LoadFundionFromXml(std::string filePath);
    std::vector<FunctionItem*>* GetFunctions();
private:
    int ReleaseFunctions();
private:
    std::vector<FunctionItem*> functions;
};

#endif