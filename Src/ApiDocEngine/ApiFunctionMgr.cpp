#include "ApiFunctionMgr.h"
#include "tinyxml2.h"
#include "ApiUtil.h"

int ApiFunctionMgr::LoadFundionFromXml(std::string filePath)
{
    FILE_LOG_INFO << "[ApiFunctionMgr::LoadFundionFromXml]start.filePath=" << filePath;
    tinyxml2::XMLDocument doc;
    int iRet = 0;
    try{
        iRet = doc.LoadFile(filePath.c_str());
    }catch(...){
        FILE_LOG_ERROR << "[ApiFunctionMgr::LoadFundionFromXml]LoadFile error.";
        return -1;
    }

    if(iRet){
        FILE_LOG_ERROR << "[ApiFunctionMgr::LoadFundionFromXml]LoadFile faild.filePath=" << filePath
            << ", errorinfo=" << doc.GetErrorStr1() << " " << doc.GetErrorStr2();
        return -2;
    }

    ReleaseFunctions();

    tinyxml2::XMLElement* ele = doc.FirstChildElement();
    while(ele){
        FunctionItem *funcItem = new FunctionItem();
        //memset(funcItem, 0, sizeof(*funcItem));

        iRet = AssigneFunctionItem(funcItem, ele);
        if(iRet >= 0){
            functions.push_back(funcItem);
        }else{
            FILE_LOG_ERROR << "[ApiFunctionMgr::LoadFundionFromXml]AssigneFunctionItem faild.iRet=" << iRet;
            delete funcItem;
        }
        
        ele = static_cast<tinyxml2::XMLElement*>(ele->NextSibling());
    }

    return functions.size();
}

std::vector<FunctionItem*>* ApiFunctionMgr::GetFunctions()
{
    return &functions;
}

int ApiFunctionMgr::ReleaseFunctions()
{
    for(std::vector<FunctionItem*>::iterator it = functions.begin(); it != functions.end(); ++it){
        FunctionItem* func = *it;
        delete func;
    }

    functions.clear();
    return 0;
}