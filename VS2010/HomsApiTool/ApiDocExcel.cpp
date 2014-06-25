#include "StdAfx.h"
#include "ApiDocExcel.h"

int ApiDocExcel::ColumnStart = 2;
int ApiDocExcel::RowSpace = 2;
long ApiDocExcel::BackgoundColorExplain = RGB(255, 255, 153);
long ApiDocExcel::BackgoundColorNormal = RGB(255, 255, 255);
long ApiDocExcel::FontColorStress = RGB(255, 0, 0);

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

    excel.SetAllCellBackgroundColor(RGB(204, 255, 255));

    int row = 2;
    int rowFunc = 0;
    for(std::vector<FunctionItem*>::iterator it = funcs->begin(); it != funcs->end(); ++it){
        FunctionItem* item = *it;
        rowFunc = WriteFunction(item, row, excel);
        row += rowFunc;

        for(int i = 1; i <= RowSpace; ++i){
            //excel.SetCellString(row, ColumnStart, "", -1, BackgoundColorExplain);
            row++;
        }
    }

    std::string fullNameNew;
    fullNameNew.append(Buffer).append("\\").append(excelName);
    excel.SaveasXSLFile(fullNameNew.c_str());

    excel.CloseExcelFile(false);
    ExcelFiler::ReleaseExcel();
    return 0;
}

int ApiDocExcel::WriteFunction(FunctionItem *func, const int row, ExcelFiler& excel)
{
    int rowCur = row;

    int rowAll = 6 + func->filedsInput.size() + 2 + func->filedsOutput.size() + 6;
    excel.SetAreaBackgroundColor(rowCur, ColumnStart, rowCur + rowAll - 1, ColumnStart + 5, RGB(255, 255, 255));

    excel.SetColumnWidth(1, 2);
    excel.SetColumnWidth(ColumnStart, 12);
    excel.SetColumnWidth(ColumnStart + 1, 25);
    excel.SetColumnWidth(ColumnStart + 2, 12);
    excel.SetColumnWidth(ColumnStart + 3, 30);
    excel.SetColumnWidth(ColumnStart + 4, 15);
    excel.SetColumnWidth(ColumnStart + 5, 30);

    excel.SetCellString(rowCur, ColumnStart, "功能号", -1, BackgoundColorExplain, 3);
    excel.SetCellInt(rowCur, ColumnStart + 1, func->no);
    excel.SetCellString(rowCur, ColumnStart + 2, "老功能号", -1, BackgoundColorExplain, 3);
    excel.SetCellString(rowCur, ColumnStart + 4, "更新日期", -1, BackgoundColorExplain, 3);
    excel.SetCellInt(rowCur, ColumnStart + 5, func->updateDate);
    rowCur++;

    excel.SetCellString(rowCur, ColumnStart, "功能名称", -1, BackgoundColorExplain, 3);
    excel.SetCellString(rowCur, ColumnStart + 1, func->name);
    excel.SetCellString(rowCur, ColumnStart + 2, "版本号", -1, BackgoundColorExplain, 3);
    excel.SetCellString(rowCur, ColumnStart + 3, func->version);
    excel.SetCellString(rowCur, ColumnStart + 4, "结果集返回", -1, BackgoundColorExplain, 3);
    excel.SetCellString(rowCur, ColumnStart + 5, func->resultSetReturn);
    rowCur++;

    excel.SetCellString(rowCur, ColumnStart, "英文名", -1, BackgoundColorExplain, 3);
    excel.SetCellString(rowCur, ColumnStart + 1, func->funcName);
    excel.MergeCell(rowCur, ColumnStart + 1, rowCur, ColumnStart + 3);
    excel.SetCellString(rowCur, ColumnStart + 4, "请求类型", -1, BackgoundColorExplain, 3);
    excel.SetCellString(rowCur, ColumnStart + 5, "请求");
    rowCur++;

    excel.SetCellString(rowCur, ColumnStart, "业务范围", -1, BackgoundColorExplain, 3);
    excel.SetCellString(rowCur, ColumnStart + 1, "HomsApi");
    excel.MergeCell(rowCur, ColumnStart + 1, rowCur, ColumnStart + 3);
    excel.SetCellString(rowCur, ColumnStart + 4, "功能状态", -1, BackgoundColorExplain, 3);
    excel.SetCellString(rowCur, ColumnStart + 5, func->status);
    rowCur++;

    excel.SetCellString(rowCur, ColumnStart, "功能描述", -1, BackgoundColorExplain, 3);
    excel.SetCellString(rowCur, ColumnStart + 1, func->description);
    excel.MergeCell(rowCur, ColumnStart + 1, rowCur, ColumnStart + 5);
    rowCur++;

    excel.SetCellString(rowCur, ColumnStart, "输入参数", -1, BackgoundColorExplain, 3);
    excel.SetCellString(rowCur, ColumnStart + 1, "参数名", -1, BackgoundColorExplain, 3);
    excel.SetCellString(rowCur, ColumnStart + 2, "类型", -1, BackgoundColorExplain, 3);
    excel.SetCellString(rowCur, ColumnStart + 3, "说明", -1, BackgoundColorExplain, 3);
    excel.SetCellString(rowCur, ColumnStart + 4, "必须", -1, BackgoundColorExplain, 3);
    excel.SetCellString(rowCur, ColumnStart + 5, "备注", -1, BackgoundColorExplain, 3);
    rowCur++;

    for(std::vector<FiledInput*>::iterator it = func->filedsInput.begin(); it != func->filedsInput.end(); ++it){
        FiledInput* filed = *it;
        int iRet = WriteFiledInput(filed, rowCur, excel);
        if(iRet < 0){
            
        }
        rowCur++;
    }

    excel.SetCellString(rowCur, ColumnStart, "输出参数", -1, BackgoundColorExplain, 3);
    excel.SetCellString(rowCur, ColumnStart + 1, "参数名", -1, BackgoundColorExplain, 3);
    excel.SetCellString(rowCur, ColumnStart + 2, "类型", -1, BackgoundColorExplain, 3);
    excel.SetCellString(rowCur, ColumnStart + 3, "说明", -1, BackgoundColorExplain, 3);
    excel.SetCellString(rowCur, ColumnStart + 4, "", -1, BackgoundColorExplain, 3);
    excel.SetCellString(rowCur, ColumnStart + 5, "备注", -1, BackgoundColorExplain, 3);
    rowCur++;

    for(std::vector<FiledOutput*>::iterator it = func->filedsOutput.begin(); it != func->filedsOutput.end(); ++it){
        FiledOutput* filed = *it;
        int iRet = WriteFiledOutput(filed, rowCur, excel);
        if(iRet < 0){
            
        }
        rowCur++;
    }

    excel.SetCellString(rowCur, ColumnStart, "", -1, BackgoundColorExplain);
    rowCur++;

    excel.SetCellString(rowCur, ColumnStart, "业务说明", -1, BackgoundColorExplain, 3);
    excel.MergeCell(rowCur, ColumnStart + 1, rowCur, ColumnStart + 5);
    rowCur++;

    excel.SetCellString(rowCur, ColumnStart, "", -1, BackgoundColorExplain);
    excel.MergeCell(rowCur, ColumnStart + 1, rowCur, ColumnStart + 5);
    rowCur++;

    excel.SetCellString(rowCur, ColumnStart, "出错说明", -1, BackgoundColorExplain, 3);
    excel.SetCellString(rowCur, ColumnStart + 1, "错误号", -1, BackgoundColorExplain, 3);
    excel.SetCellString(rowCur, ColumnStart + 2, "错误信息", -1, BackgoundColorExplain, 3);
    excel.SetCellString(rowCur, ColumnStart + 3, "错误说明", -1, BackgoundColorExplain, 3);
    excel.SetCellString(rowCur, ColumnStart + 4, "错误级别", -1, BackgoundColorExplain, 3);
    rowCur++;

    excel.SetCellString(rowCur, ColumnStart, "", -1, BackgoundColorExplain);
    rowCur++;

    excel.SetCellString(rowCur, ColumnStart, "修改记录", -1, BackgoundColorExplain, 3);
    excel.MergeCell(rowCur, ColumnStart + 1, rowCur, ColumnStart + 5);
    excel.SetCellBackgroundColor(rowCur, ColumnStart + 1, RGB(200, 200, 200));
    rowCur++;

    return rowCur - row;
}


int ApiDocExcel::WriteFiledInput(FiledInput *filed, const int row, ExcelFiler& excel)
{
    excel.SetCellString(row, ColumnStart, "", -1, BackgoundColorExplain);
    excel.SetCellString(row, ColumnStart + 1, filed->name);
    excel.SetCellString(row, ColumnStart + 2, filed->type);
    excel.SetCellString(row, ColumnStart + 3, filed->description);
    excel.SetCellString(row, ColumnStart + 4, filed->required);
    excel.SetCellString(row, ColumnStart + 4, filed->detail);
    return 0;
}


int ApiDocExcel::WriteFiledOutput(FiledOutput *filed, const int row, ExcelFiler& excel)
{
    excel.SetCellString(row, ColumnStart, "", -1, BackgoundColorExplain);
    excel.SetCellString(row, ColumnStart + 1, filed->name);
    excel.SetCellString(row, ColumnStart + 2, filed->type);
    excel.SetCellString(row, ColumnStart + 3, filed->description);
    excel.SetCellString(row, ColumnStart + 4, filed->default);
    excel.SetCellString(row, ColumnStart + 4, filed->detail);
    return 0;
}