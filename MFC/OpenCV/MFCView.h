
// MFCGAJAView.h : CMFCGAJAView 클래스의 인터페이스
//

#pragma once


class CMFCGAJAView : public CView
{
protected: // serialization에서만 만들어집니다.
	CMFCGAJAView();
	DECLARE_DYNCREATE(CMFCGAJAView)

// 특성입니다.
public:
	CMFCGAJADoc* GetDocument() const;

	CPoint m_Pos;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual void OnMOUSE(CDC* pDC);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CMFCGAJAView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	int what_filter;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBinary();
	afx_msg void OnGray();
	afx_msg void OnSobel();
};

#ifndef _DEBUG  // MFCGAJAView.cpp의 디버그 버전
inline CMFCGAJADoc* CMFCGAJAView::GetDocument() const
   { return reinterpret_cast<CMFCGAJADoc*>(m_pDocument); }
#endif

