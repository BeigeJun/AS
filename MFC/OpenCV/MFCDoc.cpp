
// MFCGAJADoc.cpp : CMFCGAJADoc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFCGAJA.h"
#endif

#include "MFCGAJADoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCGAJADoc

IMPLEMENT_DYNCREATE(CMFCGAJADoc, CDocument)

BEGIN_MESSAGE_MAP(CMFCGAJADoc, CDocument)
		ON_COMMAND(ID_FILE_OPEN, &CMFCGAJADoc::OnFileOpen)
		ON_COMMAND(ID_GRAY, &CMFCGAJADoc::GRAY)
END_MESSAGE_MAP()


// CMFCGAJADoc 생성/소멸

CMFCGAJADoc::CMFCGAJADoc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CMFCGAJADoc::~CMFCGAJADoc()
{
}

BOOL CMFCGAJADoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CMFCGAJADoc serialization

void CMFCGAJADoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CMFCGAJADoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CMFCGAJADoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMFCGAJADoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMFCGAJADoc 진단

#ifdef _DEBUG
void CMFCGAJADoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCGAJADoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMFCGAJADoc 명령


void CMFCGAJADoc::OnFileOpen()
{
	// 파일 오픈!
	TCHAR strFilter[] = _T("JPEG 이미지|*.jpg|PNG 이미지|*.png|Bitmap 이미지");
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY| OFN_FILEMUSTEXIST|OFN_ALLOWMULTISELECT, strFilter);//TRUE 읽기
	//파일선택 다이로그
	/*
	CFileDialog   ( BOOL bOpenFileDialog,
                    LPCTSTR lpszDefExt = NULL,
                    LPCTSTR lpszFileName = NULL,
                    DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
                    LPCTSTR lpszFilter = NULL,
                    CWnd* pParentWnd = NULL );

	인자값 설명
	bOpenFileDialog    TRUE면 파일열기, false 면 파일 저장
	lpszDefExt		   파일 확장자로 선언이 되면 해당하는 확장자를 가진 파일만 나온다.
	lpszFileName       파일명 에디트 박스에 초기화될 파일명
	dwFlags(*1)        dialog box 기본 FLAG, m_ofn.Flags에 등록된다
	lpszFilter         연속된 문자열으로 파일 확장자를 원하는 타입으로 나오게 할수 있다
	pParentWnd         다이얼로그 소유 윈도우 포인터
*/
	//파일열기 대화상자
	if(IDOK == fileDlg.DoModal())
	{
		CString filePath;
		filePath = fileDlg.GetPathName();
		if (!m_Img.IsNull()) { // 필터링 이미지 있으면
			m_Img.Destroy();
		}


		CFile file;
		switch(fileDlg.m_ofn.nFilterIndex){
		default:
			m_Img.Load(filePath);
		}
	}

	UpdateAllViews(NULL);// 뷰 갱신
}

void CMFCGAJADoc::GRAY()
{

}
