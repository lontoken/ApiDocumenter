
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "HomsApiTool.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
    ON_WM_CREATE()
    ON_COMMAND(ID_VIEW_CUSTOMIZE, &CMainFrame::OnViewCustomize)
    ON_REGISTERED_MESSAGE(AFX_WM_CREATETOOLBAR, &CMainFrame::OnToolbarCreateNew)
END_MESSAGE_MAP()

static UINT indicators[] =
{
    ID_SEPARATOR,           // 状态行指示器
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
    // TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
        return -1;

    BOOL bNameValid;

    // 设置用于绘制所有用户界面元素的视觉管理器
    CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));

    //if (!m_wndMenuBar.Create(this))
    //{
    //    TRACE0("未能创建菜单栏\n");
    //    return -1;      // 未能创建
    //}

    //m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);

    // 防止菜单栏在激活时获得焦点
    CMFCPopupMenu::SetForceMenuFocus(FALSE);

    //if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
    //    !m_wndToolBar.LoadToolBar(theApp.m_bHiColorIcons ? IDR_MAINFRAME_256 : IDR_MAINFRAME))
    //{
    //    TRACE0("未能创建工具栏\n");
    //    return -1;      // 未能创建
    //}

    CString strToolBarName;
    bNameValid = strToolBarName.LoadString(IDS_TOOLBAR_STANDARD);
    ASSERT(bNameValid);
    //m_wndToolBar.SetWindowText(strToolBarName);

    CString strCustomize;
    bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
    ASSERT(bNameValid);
    //m_wndToolBar.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);

    if (!m_wndStatusBar.Create(this))
    {
        TRACE0("未能创建状态栏\n");
        return -1;      // 未能创建
    }
    m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

    // TODO: 如果您不希望工具栏和菜单栏可停靠，请删除这五行
    //m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
    //m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
    EnableDocking(CBRS_ALIGN_ANY);
    //DockPane(&m_wndMenuBar);
    //DockPane(&m_wndToolBar);


    // 启用 Visual Studio 2005 样式停靠窗口行为
    CDockingManager::SetDockingMode(DT_SMART);
    // 启用 Visual Studio 2005 样式停靠窗口自动隐藏行为
    EnableAutoHidePanes(CBRS_ALIGN_ANY);

    // 启用工具栏和停靠窗口菜单替换
    EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);

    // 启用快速(按住 Alt 拖动)工具栏自定义
    CMFCToolBar::EnableQuickCustomization();

    return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
    //cs.cx = 100;
    //cs.cy=800;
    //cs.style |= FWS_ADDTOTITLE;
    //lstrcpy(cs.lpszName, _T("tet"));

    if( !CFrameWndEx::PreCreateWindow(cs) )
        return FALSE;
    // TODO: 在此处通过修改
    //  CREATESTRUCT cs 来修改窗口类或样式

    return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
    CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
    CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序

void CMainFrame::OnViewCustomize()
{
    CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* 扫描菜单*/);
    pDlgCust->Create();
}