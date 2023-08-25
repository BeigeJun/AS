
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
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
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
	pDC -> Rectangle(10, 370, 300, 690);	// 4 히스토그램
	pDC -> Rectangle(310, 370, 600, 690);	// 5 세로 프로젝션
	pDC -> Rectangle(610, 370, 900, 690);	// 6 확대 
	pDC -> Rectangle(910, 30, 1200, 260);	// 7 R 
	pDC -> Rectangle(910, 280, 1200, 500);	// 8 G 
	pDC -> Rectangle(910, 520, 1200, 740);	// 9 B 

	pDC->TextOutW(11, 690, _T("0"));
	pDC->TextOutW(274, 690, _T("255"));
	pDC->TextOutW(10, 10, _T("원본"));
	pDC->TextOutW(310, 10, _T("필터적용"));
	pDC->TextOutW(610, 10, _T("가로 프로젝션"));
	pDC->TextOutW(311, 350, _T("세로 프로젝션"));
	pDC->TextOutW(11, 350, _T("히스토그램"));
	pDC->TextOutW(611, 350, _T("확대"));
	pDC->TextOutW(910, 10, _T("R"));
	pDC->TextOutW(910, 260, _T("G"));
	pDC->TextOutW(910, 500, _T("B"));
	pDC->TextOutW(300, 720, _T("백준의 발가락의 때가 될 수 있는 그날 까지"));
	
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
			pDoc->Pro_h.StretchBlt(pDC->m_hDC, 311, 371, 288, 318);
			}
		if (!pDoc->HISTO_Img.IsNull()){
			SetStretchBltMode(pDC->m_hDC, HALFTONE);
			pDoc->HISTO_Img.StretchBlt(pDC->m_hDC, 11, 371, 288, 318);
			}

		if (!pDoc->HISTO_R_Img.IsNull()){
			SetStretchBltMode(pDC->m_hDC, HALFTONE);
			pDoc->HISTO_R_Img.StretchBlt(pDC->m_hDC, 911, 31, 288, 218);
			}
		if (!pDoc->HISTO_G_Img.IsNull()){
			SetStretchBltMode(pDC->m_hDC, HALFTONE);
			pDoc->HISTO_G_Img.StretchBlt(pDC->m_hDC, 911, 281, 288, 218);
			}
		if (!pDoc->HISTO_B_Img.IsNull()){
			SetStretchBltMode(pDC->m_hDC, HALFTONE);
			pDoc->HISTO_B_Img.StretchBlt(pDC->m_hDC, 911, 521, 288, 218);
			}
		}
	if(Button_flag == true)
	{
		pDC -> SelectStockObject(NULL_BRUSH);
		pDC -> Rectangle(Old_x_Pos-5,Old_y_Pos-5,x_Pos+5,y_Pos+5);
	}

	ReleaseDC(pDC);
	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


void CMFCGAJAView::OnMOUSE(CDC* pDC)
{
	CMFCGAJADoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CClientDC dc(this);
	CString strPoint;
	strPoint.Format(_T("마우스 좌표 (%4d, %4d)"), m_Pos.x,m_Pos.y);
	dc.TextOutW(0,0,strPoint);
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


void CMFCGAJAView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if(Button_flag == true)
	{
		m_Pos = point;
		x_Pos = m_Pos.x;
		y_Pos = m_Pos.y;

		Invalidate();
	}
	CView::OnMouseMove(nFlags, point);
}


void CMFCGAJAView::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_Pos = point;
	Button_flag = true;
	Old_x_Pos = m_Pos.x;
	Old_y_Pos = m_Pos.y;
	
	CView::OnLButtonDown(nFlags, point);
}



void CMFCGAJAView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if(Button_flag == true)
	{
		if(!ZOOM_Img.IsNull())
		{
			ZOOM_Img.Destroy();
		}
		CDC* pDC;
		pDC = GetDC();
		CMFCGAJADoc* pDoc = GetDocument();
//		CString strPoint;
//		strPoint.Format(_T("마우스 좌표 (Old :%4d, %4d  New : %4d, %4d)"), Old_x_Pos, Old_y_Pos, x_Pos, y_Pos);
//		MessageBox(strPoint, _T("Warning !"), MB_ICONERROR);
		Button_flag = false;
		/*
		ZOOM_Img.Create(x_Pos - Old_x_Pos, y_Pos - Old_y_Pos , 24);
		double w = pDoc->m_Img.GetWidth() / 250;
		double h = pDoc->m_Img.GetHeight() / 400;
		x_Pos = (double)x_Pos * w;
		y_Pos = (double)y_Pos * h;
		Old_x_Pos = (double)Old_x_Pos * w;
		Old_y_Pos = (double)Old_y_Pos * h;
		pDoc->m_Img.BitBlt(ZOOM_Img.GetDC(),0,0,ZOOM_Img.GetWidth(),ZOOM_Img.GetHeight(),x_Pos+11,y_Pos+31,SRCCOPY);
		ZOOM_Img.ReleaseDC();
		*/
		ZOOM_Img.Create(x_Pos - Old_x_Pos, y_Pos - Old_y_Pos , 24);
		for(int x = Old_x_Pos ; x < x_Pos ; x++)
		{
			for(int y = Old_y_Pos ; y < y_Pos ; y++)
			{
				COLORREF p = pDC->GetPixel(x,y);
				int r = GetRValue(p);
				int g = GetGValue(p);
				int b = GetBValue(p);
				ZOOM_Img.SetPixel(x-Old_x_Pos,y-Old_y_Pos,RGB(r,g,b));
			}
		}
		SetStretchBltMode(pDC->m_hDC, HALFTONE);
		ZOOM_Img.StretchBlt(pDC->m_hDC, 611, 371, 288, 318);
	}
	CView::OnLButtonUp(nFlags, point);
}
