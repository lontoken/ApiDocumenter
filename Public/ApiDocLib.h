#pragma once

#ifndef _API_DOC_LIB_
#define _API_DOC_LIB_

#include "ApiTypeDefine.h"
#include <vector>

#ifdef API_DOC_ENGINE_LIB
#define API_DOC_EXPORT __declspec(dllexport)
#else
#define API_DOC_EXPORT __declspec(dllimport)
#endif

class API_DOC_EXPORT ApiDoc
{
public:
    static ApiDoc *CreateApiDoc();

    virtual int Release() = 0;

    virtual int Init() = 0;

    virtual int LoadFuncFromXml(const TFileName name) = 0;

    virtual int GetFuncList(std::vector<FunctionItem*> **items) = 0;
};

#endif