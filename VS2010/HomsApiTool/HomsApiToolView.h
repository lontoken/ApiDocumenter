
// HomsApiToolView.h : CHomsApiToolView 类的接口
//

#pragma once

#include "resource.h"
#include "ApiTypeDefine.h"
#include "ApiDocLib.h"
#include "EditBrowseCtrlXml.h"

class CHomsApiToolView : public CFormView
{
protected: // 仅从序列化创建
    CHomsApiToolView();
    DECLARE_DYNCREATE(CHomsApiToolView)

public:
    enum{ IDD = IDD_HOMSAPITOOL_FORM };

// 特性
public:
    CHomsApiToolDoc* GetDocument() const;

// 操作
public:

// 重写
public:
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
    virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
    virtual ~CHomsApiToolView();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
    afx_msg void OnFilePrintPreview();
    afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedButtonShift();
    afx_msg void OnBnClickedButtonExit();

public:
    CEditBrowseCtrlXml editBrowseInputFile;
    CEditBrowseCtrlXml editBrowseOutputFile;
private:
    CString fileNameInputFile;
    CString fileNameOutputFile;
    CRect rectForm;
    ApiDoc *apiDoc;
private:
    int LogerError(CString info);
    int LogerInfo(CString info);
    int LogerDebug(CString info);
public:
    CRichEditCtrl richEditCtrlInfo;
    afx_msg void OnSize(UINT nType, int cx, int cy);
};

#ifndef _DEBUG  // HomsApiToolView.cpp 中的调试版本
inline CHomsApiToolDoc* CHomsApiToolView::GetDocument() const
   { return reinterpret_cast<CHomsApiToolDoc*>(m_pDocument); }
#endif

