
// LightTestView.cpp : CLightTestView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CLightTestView ����/����

CLightTestView::CLightTestView()
{
	// TODO: �ڴ˴���ӹ������

}

CLightTestView::~CLightTestView()
{
}

BOOL CLightTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CLightTestView ����

void CLightTestView::OnDraw(CDC* /*pDC*/)
{
	CLightTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	m_OpenGL.Render();
}


// CLightTestView ��ӡ

BOOL CLightTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CLightTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CLightTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CLightTestView ���

#ifdef _DEBUG
void CLightTestView::AssertValid() const
{
	CView::AssertValid();
}

void CLightTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLightTestDoc* CLightTestView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLightTestDoc)));
	return (CLightTestDoc*)m_pDocument;
}
#endif //_DEBUG


// CLightTestView ��Ϣ�������


int CLightTestView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	m_OpenGL.SetupPixelFormat(::GetDC(GetSafeHwnd()));
	m_OpenGL.Init();

	SetTimer(1, 25, NULL);//����1�Ŷ�ʱ����ÿ��25ms����һ��

	return 0;
}


void CLightTestView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	m_OpenGL.Reshape(cx, cy);
}


void CLightTestView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_OpenGL++;
	m_OpenGL.Render();

	CView::OnTimer(nIDEvent);
}
