#pragma once

#ifndef _API_DOC_EXCEL_
#define _API_DOC_EXCEL_

#include "ExcelFiler.h"
#include "ApiTypeDefine.h"

class ApiDocExcel
{
public:
    static int SaveDataToExcel(std::vector<FunctionItem*> *funcs, std::string excelName = "api_functin.xls");
};


#endif