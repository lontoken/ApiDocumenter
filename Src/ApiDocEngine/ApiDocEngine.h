#pragma once 

#ifndef _API_DOC_ENGINE_
#define _API_DOC_ENGINE_

#include "ApiDocLib.h"
#include "ApiFunctionMgr.h"

class ApiDocEngine : public ApiDoc
{
public:
    ApiDocEngine():apiFuncMgr(NULL),hasInited(false){};
    virtual ~ApiDocEngine(){
        if(apiFuncMgr){
            delete apiFuncMgr;
            apiFuncMgr = NULL;
        }
    };
public:
    virtual int Release();

    virtual int Init();

    virtual int LoadFuncFromXml(const TFileName name);

    virtual int GetFuncList(std::vector<FunctionItem*> **items);
private:
    ApiFunctionMgr* apiFuncMgr;
    bool hasInited;
};

#endif