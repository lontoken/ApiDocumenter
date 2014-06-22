#include "ApiDocEngine.h"
#include "SimpleLog.h"

ApiDoc *ApiDoc::CreateApiDoc()
{
    ApiDocEngine *apiDoc = new ApiDocEngine();
    INIT_FILE_LOG("DEBUG1");
    FILE_LOG_INFO << "[ApiDoc::CreateApiDoc]start.";
    return apiDoc;
}

int ApiDocEngine::Release()
{
    delete this;
    return 0;
}

int ApiDocEngine::Init()
{
    if(!apiFuncMgr){
        apiFuncMgr = new ApiFunctionMgr();
    }

    hasInited = true;
    return 0;
}

int ApiDocEngine::LoadFuncFromXml(const TFileName name)
{
    FILE_LOG_INFO << "[ApiDocEngine::LoadFuncFromXml]start.";

    if(!name){
        FILE_LOG_ERROR << "[ApiDocEngine::LoadFuncFromXml]param error.";
        return -1;
    }

    if(!hasInited){
        FILE_LOG_ERROR << "[ApiDocEngine::LoadFuncFromXml]has not init.";
        return -2;
    }

    FILE_LOG_INFO << "[ApiDocEngine::LoadFuncFromXml]LoadFundionFromXml start.name=" << name;
    int iRet = apiFuncMgr->LoadFundionFromXml(name);

    FILE_LOG_INFO << "[ApiDocEngine::LoadFuncFromXml]end.iRet=" << iRet;
    return iRet;
}

int ApiDocEngine::GetFuncList(std::vector<FunctionItem*> **items)
{
    FILE_LOG_INFO << "[ApiDocEngine::GetFuncList]start.";

    if(!items){
        FILE_LOG_ERROR << "[ApiDocEngine::GetFuncList]param error.";
        return -1;
    }

    if(!hasInited){
        FILE_LOG_ERROR << "[ApiDocEngine::GetFuncList]has not init.";
        return -2;
    }

    std::vector<FunctionItem*>* funcs = apiFuncMgr->GetFunctions();
    *items = funcs;
    return funcs->size();
}