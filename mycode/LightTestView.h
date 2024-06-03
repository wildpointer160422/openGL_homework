
// LightTestView.h : CLightTestView ��Ľӿ�
//

#pragma once

#include "MyOpenGL.h"

class CLightTestView : public CView
{
private:
	MyOpenGL m_OpenGL;

protected: // �������л�����
	CLightTestView();
	DECLARE_DYNCREATE(CLightTestView)

// ����
public:
	CLightTestDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CLightTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
private:
	BOOL m_bLeftButtonDown;
	CPoint m_lastMousePos;
	float m_rotationAngleX;
	float m_rotationAngleY;
};

#ifndef _DEBUG  // LightTestView.cpp �еĵ��԰汾
inline CLightTestDoc* CLightTestView::GetDocument() const
   { return reinterpret_cast<CLightTestDoc*>(m_pDocument); }
#endif

