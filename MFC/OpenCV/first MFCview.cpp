
// first MFCView.cpp : CfirstMFCView 클래스의 구현
//보여지는 곳

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "first MFC.h"
#endif

#include "first MFCDoc.h"
#include "first MFCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CfirstMFCView

IMPLEMENT_DYNCREATE(CfirstMFCView, CView)

BEGIN_MESSAGE_MAP(CfirstMFCView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CfirstMFCView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CfirstMFCView 생성/소멸

CfirstMFCView::CfirstMFCView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CfirstMFCView::~CfirstMFCView()
{
}

BOOL CfirstMFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CfirstMFCView 그리기

void CfirstMFCView::OnDraw(CDC* pDC)
{
	CfirstMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDC = GetDC(); // dc 가져옴
	pDC -> Rectangle(10, 30, 300, 350);		// 1 원본 사진
	pDC -> Rectangle(310, 30, 600, 350);	// 2 필터 적용 사진
	pDC -> Rectangle(610, 30, 900, 350);	// 3 가로 프로젝션
	pDC -> Rectangle(10, 360, 300, 680);	// 4 히스토그램
	pDC -> Rectangle(310, 360, 600, 680);	// 5 프로젝션
	pDC -> Rectangle(610, 360, 900, 680);	// 6 확대 
	ReleaseDC(pDC);
	
	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CfirstMFCView 인쇄


void CfirstMFCView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CfirstMFCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CfirstMFCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CfirstMFCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CfirstMFCView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CfirstMFCView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CfirstMFCView 진단

#ifdef _DEBUG
void CfirstMFCView::AssertValid() const
{
	CView::AssertValid();
}

void CfirstMFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CfirstMFCDoc* CfirstMFCView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CfirstMFCDoc)));
	return (CfirstMFCDoc*)m_pDocument;
}
#endif //_DEBUG


// CfirstMFCView 메시지 처리기
