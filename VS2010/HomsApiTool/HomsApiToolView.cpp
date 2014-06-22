
// HomsApiToolView.cpp : CHomsApiToolView 类的实现
//
#include <string>

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "HomsApiTool.h"
#endif

#include "HomsApiToolDoc.h"
#include "HomsApiToolView.h"
#include "ApiDocExcel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHomsApiToolView

IMPLEMENT_DYNCREATE(CHomsApiToolView, CFormView)

BEGIN_MESSAGE_MAP(CHomsApiToolView, CFormView)
    ON_WM_CONTEXTMENU()
    ON_WM_RBUTTONUP()
    ON_BN_CLICKED(IDC_BUTTON_SHIFT, &CHomsApiToolView::OnBnClickedButtonShift)
    ON_BN_CLICKED(IDC_BUTTON_EXIT, &CHomsApiToolView::OnBnClickedButtonExit)
    ON_WM_SIZE()
END_MESSAGE_MAP()

// CHomsApiToolView 构造/析构

CHomsApiToolView::CHomsApiToolView()
    : CFormView(CHomsApiToolView::IDD)
{
    // TODO: 在此处添加构造代码
    SetCurrentDirectory("./");
    apiDoc = ApiDoc::CreateApiDoc();
    apiDoc->Init();
}

CHomsApiToolView::~CHomsApiToolView()
{
    apiDoc->Release();
    apiDoc = NULL;
}

void CHomsApiToolView::DoDataExchange(CDataExchange* pDX)
{
    CFormView::DoDataExchange(pDX);
    DDX_Control( pDX, IDC_MFCEDITBROWSE_INPUT_FILE, editBrowseInputFile);
    DDX_Control( pDX, IDC_MFCEDITBROWSE_OUTPUT_FILE, editBrowseOutputFile);
    DDX_Control(pDX, IDC_RICHEDIT2_INFO, richEditCtrlInfo);
}

BOOL CHomsApiToolView::PreCreateWindow(CREATESTRUCT& cs)
{
    // TODO: 在此处通过修改
    //  CREATESTRUCT cs 来修改窗口类或样式

    return CFormView::PreCreateWindow(cs);
}

void CHomsApiToolView::OnInitialUpdate()
{
    CFormView::OnInitialUpdate();
    GetParentFrame()->RecalcLayout();
    ResizeParentToFit();

    editBrowseInputFile.EnableFileBrowseButton();
    editBrowseInputFile.m_strFileType=_T("Xml Files(*.xml)|*.xml|All Files (*.*)|*.*||");
}

void CHomsApiToolView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
    ClientToScreen(&point);
    OnContextMenu(this, point);
}

void CHomsApiToolView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
    //theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CHomsApiToolView 诊断

#ifdef _DEBUG
void CHomsApiToolView::AssertValid() const
{
    CFormView::AssertValid();
}

void CHomsApiToolView::Dump(CDumpContext& dc) const
{
    CFormView::Dump(dc);
}

CHomsApiToolDoc* CHomsApiToolView::GetDocument() const // 非调试版本是内联的
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHomsApiToolDoc)));
    return (CHomsApiToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CHomsApiToolView 消息处理程序
void CHomsApiToolView::OnBnClickedButtonShift()
{
    // TODO: 在此添加控件通知处理程序代码
    LogerInfo(_T("Shift"));

    CEdit *pEdit = (CEdit*)(&editBrowseInputFile);
    CString strInput;
    pEdit->GetWindowText(strInput);

    pEdit = (CEdit*)(&editBrowseOutputFile);
    CString strOutput;
    pEdit->GetWindowText(strOutput);

    fileNameInputFile = strInput;
    fileNameOutputFile = strOutput;

    LogerDebug(strInput);
    LogerDebug(strOutput);

    std::string strFiledInput(strInput.GetBuffer());
    apiDoc->LoadFuncFromXml(strFiledInput.c_str());

    std::vector<FunctionItem*> *funcs = NULL;
    int iRet = apiDoc->GetFuncList(&funcs);
    if(iRet >= 0 && funcs){
        CString logMessage;
        logMessage.Format(_T("Function Count: %d"), funcs->size());
        LogerDebug(logMessage);

        iRet = ApiDocExcel::SaveDataToExcel(funcs, "api.xlsx");
        if(iRet >= 0){
            LogerDebug("Save Data To Excel Success.");
        }else{
            logMessage.Format(_T("Save Data To Excel Faild.iRet=%d"), iRet);
            LogerDebug(logMessage);
        }
    }
}


void CHomsApiToolView::OnBnClickedButtonExit()
{
    // TODO: 在此添加控件通知处理程序代码
}

int CHomsApiToolView::LogerDebug(CString info)
{
    int line = richEditCtrlInfo.GetLineCount();
    CString logMessage;
    logMessage.Format(_T("%d: %s\r\n"), line, info);

    CHARFORMAT cf;
    richEditCtrlInfo.GetDefaultCharFormat(cf);
    cf.dwMask = CFM_COLOR;
    cf.dwEffects = 0;
    cf.crTextColor = RGB(256, 0, 0);
   
    // Set Focus to auto scroll the Richedit window and update it
    richEditCtrlInfo.SetFocus();
    richEditCtrlInfo.SetSel(0xFFFF, 0xFFFF);
                    
    richEditCtrlInfo.HideSelection(FALSE, TRUE);
                    
    richEditCtrlInfo.SetSelectionCharFormat(cf);
    richEditCtrlInfo.ReplaceSel(logMessage);
    richEditCtrlInfo.HideSelection(TRUE, TRUE);

    return richEditCtrlInfo.GetLineCount();
}

int CHomsApiToolView::LogerError(CString info)
{
    int line = richEditCtrlInfo.GetLineCount();
    CString logMessage;
    logMessage.Format(_T("%d: %s\r\n"), line, info);

    CHARFORMAT cf;
    richEditCtrlInfo.GetDefaultCharFormat(cf);
    cf.dwMask = CFM_COLOR;
    cf.dwEffects = 0;
    cf.crTextColor = RGB(160, 0, 0);
   
    // Set Focus to auto scroll the Richedit window and update it
    richEditCtrlInfo.SetFocus();
    richEditCtrlInfo.SetSel(0xFFFF, 0xFFFF);
                    
    richEditCtrlInfo.HideSelection(FALSE, TRUE);
                    
    richEditCtrlInfo.SetSelectionCharFormat(cf);
    richEditCtrlInfo.ReplaceSel(logMessage);
    richEditCtrlInfo.HideSelection(TRUE, TRUE);

    return richEditCtrlInfo.GetLineCount();
}

int CHomsApiToolView::LogerInfo(CString info)
{
    int line = richEditCtrlInfo.GetLineCount();
    CString logMessage;
    logMessage.Format(_T("%d: %s\r\n"), line, info);

    CHARFORMAT cf;
    richEditCtrlInfo.GetDefaultCharFormat(cf);
    cf.dwMask = CFM_COLOR;
    cf.dwEffects = 0;
    cf.crTextColor = RGB(30, 0, 0);
   
    // Set Focus to auto scroll the Richedit window and update it
    richEditCtrlInfo.SetFocus();
    richEditCtrlInfo.SetSel(0xFFFF, 0xFFFF);
                    
    richEditCtrlInfo.HideSelection(FALSE, TRUE);
                    
    richEditCtrlInfo.SetSelectionCharFormat(cf);
    richEditCtrlInfo.ReplaceSel(logMessage);
    richEditCtrlInfo.HideSelection(TRUE, TRUE);

    return richEditCtrlInfo.GetLineCount();
}


void CHomsApiToolView::OnSize(UINT nType, int cx, int cy)
{
    CFormView::OnSize(nType, cx, cy);

    if (richEditCtrlInfo.GetSafeHwnd()) //判断RichEdit控件是否初始化成功  
    {  
        if (nType==SIZE_RESTORED)  
        {  
            CRect rs;  
            GetClientRect(&rs);  //得到父窗体CFormView的大小和位置  

            CRect rsOld;
            richEditCtrlInfo.GetWindowRect(rsOld);
            ScreenToClient(rsOld);

            richEditCtrlInfo.SetWindowPos(this, 0, rsOld.top, rs.Width(), rs.Height() - rsOld.top, 
                SWP_SHOWWINDOW | SWP_NOZORDER);  
            //按照父窗体的大小和位置，将RichEdit控件移到相应的位置  
        }
    }
}
