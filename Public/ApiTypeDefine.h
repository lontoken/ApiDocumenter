#pragma once

#ifndef _API_TYPE_DEFINE_
#define _API_TYPE_DEFINE_

#include <vector>

typedef char TFileName[256];

typedef int TFunctionNo;
typedef char TFunctionName[64];
typedef int TFunctionUpdateDate;
typedef char TFunctionVersion[32];
typedef char TFunctionStatus[32];
typedef char TFunctionDescription[1024];

typedef char TFiledName[64];
typedef char TFiledType[64];
typedef char TFiledRequired[2];
typedef char TResultSetReturn[2];
typedef char TFiledDescription[512];
typedef char TFiledDefault[128];
typedef char TFiledDetail[512];

const char filedRequiredYes = 'Y';
const char filedRequiredNo = 'N';

struct FiledInput
{
    TFiledName name;
    TFiledType type;
    TFiledRequired required;
    TFiledDescription description;
    TFiledDefault default;
    TFiledDetail detail;

public:
    FiledInput(){
        memset(name, 0, sizeof(name));
        memset(type, 0, sizeof(type));
        memset(required, 0, sizeof(required));
        memset(description, 0, sizeof(description));
        memset(default, 0, sizeof(default));
        memset(detail, 0, sizeof(detail));
    };
};

struct FiledOutput
{
    TFiledName name;
    TFiledType type;
    TFiledDescription description;
    TFiledDefault default;
    TFiledDetail detail;
public:
    FiledOutput(){
        memset(name, 0, sizeof(name));
        memset(type, 0, sizeof(type));
        memset(description, 0, sizeof(description));
        memset(default, 0, sizeof(default));
        memset(detail, 0, sizeof(detail));
    };
};

struct FunctionItem
{
    TFunctionNo no;
    TFunctionName name;
    TFunctionName funcName;
    TFunctionUpdateDate updateDate;
    TFunctionVersion version;
    TFunctionStatus status;
    TFunctionDescription description;
    TResultSetReturn resultSetReturn;

    std::vector<FiledInput*> filedsInput;
    std::vector<FiledOutput*> filedsOutput;
public:
    FunctionItem(){
        no = 0;
        memset(name, 0, sizeof(name));
        memset(funcName, 0, sizeof(funcName));
        updateDate = 0;
        memset(version, 0, sizeof(version));
        memset(status, 0, sizeof(status));
        memset(description, 0, sizeof(description));
        memset(resultSetReturn, 0, sizeof(resultSetReturn));
    };
    virtual ~FunctionItem(){
        for(std::vector<FiledInput*>::iterator it = filedsInput.begin(); it != filedsInput.end(); ++it){
            FiledInput* func = *it;
            delete func;
        }

        for(std::vector<FiledOutput*>::iterator it = filedsOutput.begin(); it != filedsOutput.end(); ++it){
            FiledOutput* func = *it;
            delete func;
        }
    };
};

struct FunctionList
{
    int count;
    FunctionItem item[1];
};

#endif