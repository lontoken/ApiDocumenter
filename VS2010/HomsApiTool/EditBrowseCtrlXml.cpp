#include "stdafx.h"
#include "EditBrowseCtrlXml.h"


// CMyEditBrowseCtrl

//IMPLEMENT_DYNAMIC(CMyEditBrowseCtrl, CMFCEditBrowseCtrl)

CEditBrowseCtrlXml::CEditBrowseCtrlXml()
{
	m_strFileType = _T("All Files (*.*)|*.*||");
}

CEditBrowseCtrlXml::~CEditBrowseCtrlXml()
{
}


BEGIN_MESSAGE_MAP(CEditBrowseCtrlXml, CMFCEditBrowseCtrl)
END_MESSAGE_MAP()



// CMyEditBrowseCtrl 消息处理程序


void CEditBrowseCtrlXml::OnBrowse()
{
	CString TempPathName;

    TCHAR Buffer[256];
    GetCurrentDirectory(256, Buffer);

	CFileDialog dlg(TRUE, NULL, NULL, NULL, m_strFileType, NULL, 0, TRUE);
    dlg.m_ofn.lpstrInitialDir = Buffer;

	//(dlg.m_ofn).lpstrTitle=_T("打开文件");

	if(dlg.DoModal()==IDOK)
	{
		TempPathName=dlg.GetPathName();
		SetWindowText(TempPathName);
	}
	else
		return;
}