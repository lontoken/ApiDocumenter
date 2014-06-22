#include "StdAfx.h"
#include "ApiDocExcel.h"

int ApiDocExcel::SaveDataToExcel(std::vector<FunctionItem*> *funcs, std::string excelName)
{
    ExcelFiler::InitExcel();
    ExcelFiler excel;

    TCHAR Buffer[256];
    GetCurrentDirectory(256, Buffer);
    std::string fullNameTmp;
    fullNameTmp.append(Buffer).append("\\temp.xlsx");

    excel.OpenExcelFile(fullNameTmp.c_str());
    excel.LoadSheet(1, true);

    excel.SetCellString(2, 1, "2a");
    excel.SetCellString(2, 2, "2b");

    std::string fullNameNew;
    fullNameNew.append(Buffer).append("\\").append(excelName);
    excel.SaveasXSLFile(fullNameNew.c_str());

    excel.CloseExcelFile(false);

    //remove(fullNameTmp.c_str());

    ExcelFiler::ReleaseExcel();
    return 0;
}