#include "ApiUtil.h"
#include "SimpleLog.h"

int AssigneFiledInput(FiledInput *filed, const tinyxml2::XMLElement *ele)
{
    const tinyxml2::XMLAttribute *attr = ele->FindAttribute("name");
    if(attr){
        strncpy(filed->name, attr->Value(), sizeof(filed->name));
    }

    attr = ele->FindAttribute("type");
    if(attr){
        strncpy(filed->type, attr->Value(), sizeof(filed->type));
    }

    attr = ele->FindAttribute("required");
    if(attr){
        strncpy(filed->required, attr->Value(), sizeof(filed->required));
    }

    attr = ele->FindAttribute("description");
    if(attr){
        strncpy(filed->description, attr->Value(), sizeof(filed->description));
    }

    attr = ele->FindAttribute("default");
    if(attr){
        strncpy(filed->default, attr->Value(), sizeof(filed->default));
    }

    attr = ele->FindAttribute("detail");
    if(attr){
        strncpy(filed->detail, attr->Value(), sizeof(filed->detail));
    }

    return 0;
}

int AssigneFiledOutput(FiledOutput *filed, const tinyxml2::XMLElement *ele)
{
    const tinyxml2::XMLAttribute *attr = ele->FindAttribute("name");
    if(attr){
        strncpy(filed->name, attr->Value(), sizeof(filed->name));
    }

    attr = ele->FindAttribute("type");
    if(attr){
        strncpy(filed->type, attr->Value(), sizeof(filed->type));
    }

    attr = ele->FindAttribute("description");
    if(attr){
        strncpy(filed->description, attr->Value(), sizeof(filed->description));
    }

    attr = ele->FindAttribute("default");
    if(attr){
        strncpy(filed->default, attr->Value(), sizeof(filed->default));
    }

    attr = ele->FindAttribute("detail");
    if(attr){
        strncpy(filed->detail, attr->Value(), sizeof(filed->detail));
    }

    return 0;
}

int AssigneFunctionItem(FunctionItem *funcItem, const tinyxml2::XMLElement *ele)
{
    int iRet = ele->QueryIntAttribute("no", &(funcItem->no));
    if(iRet){
        FILE_LOG_ERROR << "[AssigneFunctionItem]no error.";
    }

    const tinyxml2::XMLAttribute *attr = ele->FindAttribute("name");
    if(attr){
        strncpy(funcItem->name, attr->Value(), sizeof(funcItem->name));
    }

    iRet = ele->QueryIntAttribute("update_date", &(funcItem->updateDate));
    if(iRet){
        FILE_LOG_ERROR << "[AssigneFunctionItem]updateDate error.";
    }

    attr = ele->FindAttribute("version");
    if(attr){
        strncpy(funcItem->version, attr->Value(), sizeof(funcItem->version));
    }

    attr = ele->FindAttribute("status");
    if(attr){
        strncpy(funcItem->status, attr->Value(), sizeof(funcItem->status));
    }

    const tinyxml2::XMLElement* eleChild = ele->FirstChildElement("description");
    if(eleChild){
        strncpy(funcItem->description, eleChild->GetText(), sizeof(funcItem->description));
    }

    eleChild = ele->FirstChildElement("input");
    if(eleChild){
        eleChild = eleChild->FirstChildElement("filed");
        while(eleChild){
            FiledInput *filed = new FiledInput();
            //memset(filed, 0, sizeof(*filed));

            iRet = AssigneFiledInput(filed, eleChild);
            if(iRet >= 0){
                funcItem->filedsInput.push_back(filed);
            }else{
                FILE_LOG_ERROR << "[AssigneFunctionItem]AssigneFiledInput faild.iRet=" << iRet;
                delete funcItem;
            }
        
            eleChild = static_cast<const tinyxml2::XMLElement*>(eleChild->NextSibling());
        }
    }

    eleChild = ele->FirstChildElement("output");
    if(eleChild){
        eleChild = eleChild->FirstChildElement("filed");
        while(eleChild){
            FiledOutput *filed = new FiledOutput();
            //memset(filed, 0, sizeof(*filed));

            iRet = AssigneFiledOutput(filed, eleChild);
            if(iRet >= 0){
                funcItem->filedsOutput.push_back(filed);
            }else{
                FILE_LOG_ERROR << "[AssigneFunctionItem]AssigneFiledOutput faild.iRet=" << iRet;
                delete funcItem;
            }
        
            eleChild = static_cast<const tinyxml2::XMLElement*>(eleChild->NextSibling());
        }
    }

    return 0;
}