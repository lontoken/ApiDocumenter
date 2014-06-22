#pragma once

#include "resource.h"

class CEditBrowseCtrlXml : public CMFCEditBrowseCtrl
{
	//DECLARE_DYNAMIC(CEditBrowseCtrlXml)

public:
	CEditBrowseCtrlXml();
	virtual ~CEditBrowseCtrlXml();

public:
	CString m_strFileType;//自定义开文件类型

private:
	virtual void OnBrowse();//重写CMFCEditBrowseCtrl的打开函数

protected:
	DECLARE_MESSAGE_MAP()
};