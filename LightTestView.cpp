
// LightTestView.cpp : CLightTestView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "LightTest.h"
#endif

#include "LightTestDoc.h"
#include "LightTestView.h"
#include "MyOpenGL.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLightTestView

IMPLEMENT_DYNCREATE(CLightTestView, CView)

BEGIN_MESSAGE_MAP(CLightTestView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CLightTestView 构造/析构

CLightTestView::CLightTestView()
{
	// TODO: 在此处添加构造代码

}

CLightTestView::~CLightTestView()
{
}

BOOL CLightTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CLightTestView 绘制

void CLightTestView::OnDraw(CDC* /*pDC*/)
{
	CLightTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	m_OpenGL.Render();
}


// CLightTestView 打印

BOOL CLightTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CLightTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CLightTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CLightTestView 诊断

#ifdef _DEBUG
void CLightTestView::AssertValid() const
{
	CView::AssertValid();
}

void CLightTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLightTestDoc* CLightTestView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLightTestDoc)));
	return (CLightTestDoc*)m_pDocument;
}
#endif //_DEBUG


// CLightTestView 消息处理程序


int CLightTestView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	m_OpenGL.SetupPixelFormat(::GetDC(GetSafeHwnd()));
	m_OpenGL.Init();

	SetTimer(1, 25, NULL);//设置1号定时器，每隔25ms启动一次

	return 0;
}


void CLightTestView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	m_OpenGL.Reshape(cx, cy);
}


void CLightTestView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_OpenGL++;
	m_OpenGL.Render();

	CView::OnTimer(nIDEvent);
}
