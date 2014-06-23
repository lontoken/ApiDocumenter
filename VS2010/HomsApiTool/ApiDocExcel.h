#pragma once

#ifndef _API_DOC_EXCEL_
#define _API_DOC_EXCEL_

#include "ExcelFiler.h"
#include "ApiTypeDefine.h"

class ApiDocExcel
{
public:
    static int SaveDataToExcel(std::vector<FunctionItem*> *funcs, std::string excelName = "api_functin.xls");
private:
    static int WriteFunction(FunctionItem *func, const int row, ExcelFiler& excel);
    static int WriteFiledInput(FiledInput *filed, const int row, ExcelFiler& excel);
    static int WriteFiledOutput(FiledOutput *filed, const int row, ExcelFiler& excel);
private:
    static int ColumnStart;
    static int RowSpace;
    static long BackgoundColorExplain;
    static long FontColorStress;
};


#endif