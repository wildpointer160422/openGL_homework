
// LightTestView.h : CLightTestView 类的接口
//

#pragma once

#include "MyOpenGL.h"

class CLightTestView : public CView
{
private:
	MyOpenGL m_OpenGL;

protected: // 仅从序列化创建
	CLightTestView();
	DECLARE_DYNCREATE(CLightTestView)

// 特性
public:
	CLightTestDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
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
// 生成的消息映射函数
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

#ifndef _DEBUG  // LightTestView.cpp 中的调试版本
inline CLightTestDoc* CLightTestView::GetDocument() const
   { return reinterpret_cast<CLightTestDoc*>(m_pDocument); }
#endif

