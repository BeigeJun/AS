
// MFCGAJAView.cpp : CMFCGAJAView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFCGAJA.h"
#endif

#include "MFCGAJADoc.h"
#include "MFCGAJAView.h"
#include <atlimage.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCGAJAView

IMPLEMENT_DYNCREATE(CMFCGAJAView, CView)

BEGIN_MESSAGE_MAP(CMFCGAJAView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCGAJAView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMFCGAJAView 생성/소멸

CMFCGAJAView::CMFCGAJAView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMFCGAJAView::~CMFCGAJAView()
{
}

BOOL CMFCGAJAView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMFCGAJAView 그리기

void CMFCGAJAView::OnDraw(CDC* pDC)
{
	CMFCGAJADoc* pDoc = GetDocument();
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

	pDC->TextOutW(11, 680, _T("0"));
	pDC->TextOutW(274, 680, _T("255"));
	
	if (!pDoc->m_Img.IsNull()){ // 원본 이미지 출력
		SetStretchBltMode(pDC->m_hDC, HALFTONE); // m_hDC 소유 창의 디바이스 컨텍스트에 대한 핸들입니다.
		//이미지 확대 축소를 통해 생기는 손실을 보정해주는 함수
		// BLACKONWHITE 제거되거나 존재하는 픽셀의 색상 값을 사용하여 AND연사자를 수행 흑백 비트맵인경우 흰 픽셀을 훼손시키고 검정 픽셀을 보존
		// COLORONCOLOR 픽셀을 삭제합니다. 모두 제거된 픽셀 줄의 정보를 보존하지 않고 삭제합니다.
		// HALFTONE 원본 사각형에서 대상 사각형 안의 픽셀 영역으로 픽셀을 보여줍니다. *대상 픽셀의 평균 색상을 원본 픽셀 색상으로 근사치로 계산합니다.
		// WHITEONBLACK 제거되거나 존재하는 픽셀의 색상 값을 사용하여 OR 연산자를 수행합니다.흑백 비트맵의 경우 검은 픽셀을 훼손시키고 흰 픽셀을 보존합니다.
		pDoc->m_Img.StretchBlt(pDC->m_hDC, 11, 31, 288, 318);
		if (!pDoc->Second_Img.IsNull()){
			SetStretchBltMode(pDC->m_hDC, HALFTONE);
			pDoc->Second_Img.StretchBlt(pDC->m_hDC, 311, 31, 288, 318);
			}
		if (!pDoc->Pro_w.IsNull()){
			SetStretchBltMode(pDC->m_hDC, HALFTONE);
			pDoc->Pro_w.StretchBlt(pDC->m_hDC, 611, 31, 288, 318);
			}
		if (!pDoc->Pro_h.IsNull()){
			SetStretchBltMode(pDC->m_hDC, HALFTONE);
			pDoc->Pro_h.StretchBlt(pDC->m_hDC, 311, 361, 288, 318);
			}
		if (!pDoc->HISTO_Img.IsNull()){
			SetStretchBltMode(pDC->m_hDC, HALFTONE);
			pDoc->HISTO_Img.StretchBlt(pDC->m_hDC, 11, 361, 288, 318);
			}
		}


	ReleaseDC(pDC);
	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CMFCGAJAView 인쇄


void CMFCGAJAView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCGAJAView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMFCGAJAView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMFCGAJAView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CMFCGAJAView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCGAJAView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCGAJAView 진단

#ifdef _DEBUG
void CMFCGAJAView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCGAJAView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCGAJADoc* CMFCGAJAView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCGAJADoc)));
	return (CMFCGAJADoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCGAJAView 메시지 처리기
