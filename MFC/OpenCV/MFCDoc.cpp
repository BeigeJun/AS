
// MFCGAJADoc.cpp : CMFCGAJADoc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFCGAJA.h"
#include "SLD.h"
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
		ON_COMMAND(ID_Binary, &CMFCGAJADoc::Binary)
		ON_COMMAND(ID_SLIDER, &CMFCGAJADoc::Slider)
		ON_COMMAND(ID_SOBEL, &CMFCGAJADoc::Sobel)
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

SLD sld;

void CMFCGAJADoc::Slider()
{
	sld.SS =128;
	sld.DoModal();
}
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


void CMFCGAJADoc::DESTROY()
{
	if(!Second_Img.IsNull())
	{
		Second_Img.Destroy();				
	}
//	if(!histo.IsNull())
//	{
//		histo.Destroy();
//	}
}


void CMFCGAJADoc::SetPixel(int x, int y, BYTE color, CImage * image){

	BYTE *p = (BYTE*)image->GetPixelAddress(x, y);					//포인터 사용하여서 주소 바꿔줌 -> 기존 라이브러리함수 setpixel보다 속도가 빠름
	*p++ = color;
	*p++ = color;
	*p = color;
}


void CMFCGAJADoc::GRAY()
{
	COLORREF* color;
	double r,g,b,new_color;

	if(!m_Img.IsNull()){
		DESTROY();

		Second_Img.Create(m_Img.GetWidth(), m_Img.GetHeight(), 24); // 24비트 비트맵 생성
		GRAYIMG = new BYTE*[m_Img.GetHeight()];

		for(int i = 0; i < m_Img.GetWidth(); i++)
		{
			GRAYIMG[i] = new BYTE[m_Img.GetWidth()];
		}
		for(int y = 0; y < m_Img.GetHeight();y++){
			for(int x = 0 ; x < m_Img.GetWidth(); x++){
				color = (COLORREF*)m_Img.GetPixelAddress(x,y);

				r = GetRValue(*color);
				g = GetGValue(*color);
				b = GetBValue(*color);

				new_color = (r+b+g)/3;

				GRAYIMG[y][x] = new_color;
				SetPixel(x,y,GRAYIMG[y][x],&Second_Img);
			}
		}
/*	m_Img.BitBlt(Second_Img.GetDC(), 0, 0, m_Img.GetWidth(), m_Img.GetHeight(), 0, 0, SRCCOPY); // 원래 이미지를 복사함
	Second_Img.ReleaseDC(); // dc 해제



	for(int y = 0; y < Second_Img.GetHeight();y++){
		for(int x = 0 ; x < Second_Img.GetWidth(); x++){
			color = Second_Img.GetPixel(x,y);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			int new_color = (r+g+b)/3;
			Second_Img.SetPixel(x,y,RGB(new_color,new_color,new_color));
		}
	}
*/  }
	UpdateAllViews(NULL);
}

void CMFCGAJADoc::Binary()
{
	COLORREF* color;
	double r,g,b,new_color;

	if(!m_Img.IsNull()){
		DESTROY();
		GRAY();
		BINARYIMG = new BYTE*[m_Img.GetHeight()];

		for(int i = 0; i < m_Img.GetWidth(); i++)
		{
			BINARYIMG[i] = new BYTE[m_Img.GetWidth()];
		}
		for(int y = 0; y < m_Img.GetHeight();y++){
			for(int x = 0 ; x < m_Img.GetWidth(); x++){

				color = (COLORREF*)m_Img.GetPixelAddress(x,y);

				r = GetRValue(*color);
				g = GetGValue(*color);
				b = GetBValue(*color);

				new_color = (r+b+g)/3;

				GRAYIMG[y][x] = new_color;
				if(new_color > sld.SS)
				{
					SetPixel(x,y,255,&Second_Img);
				}
				else
				{
					SetPixel(x,y,0,&Second_Img);
				}
			}
		}


	}

	/*
	m_Img.BitBlt(Second_Img.GetDC(), 0, 0, m_Img.GetWidth(), m_Img.GetHeight(), 0, 0, SRCCOPY); // 원래 이미지를 복사함
	Second_Img.ReleaseDC(); // dc 해제

	for(int y = 0; y < m_Img.GetHeight();y++){
		for(int x = 0 ; x < m_Img.GetWidth(); x++){
			color = m_Img.GetPixel(x,y);

			BYTE b = GetRValue(color);
			BYTE g = GetGValue(color);
			BYTE r = GetBValue(color);

			BYTE new_r = r*0.0722;
			BYTE new_b = b*0.2126;
			BYTE new_g = g*0.7152;

			BYTE new_color = (new_r+new_b+new_g)/3;

			if(RGB(new_r,new_g,new_b) > sld.SS)
			{
				Second_Img.SetPixel(x,y,RGB(255,255,255));
			}
			else
			{
				Second_Img.SetPixel(x,y,RGB(new_color,new_color,new_color));
			}
		}
	}
	*/

	UpdateAllViews(NULL);
}

void CMFCGAJADoc::Sobel()
{
	if(!m_Img.IsNull()){
		DESTROY();
		GRAY();

		int x_filter[3][3]={{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
		int y_filter[3][3]={{1, 2, 1}, {0, 0, 0}, {-1, -2, -1}};

		SOBELIMG = new BYTE*[m_Img.GetHeight()];

		for(int i = 0; i < m_Img.GetWidth(); i++)
		{
			SOBELIMG[i] = new BYTE[m_Img.GetWidth()];
		}


		for(int y = 0; y < m_Img.GetHeight(); y++){
			for(int x = 0 ; x < m_Img.GetWidth(); x++){
				int x_temp = 0, y_temp = 0;
				for(int xx = 0 ; xx < 3 ; xx++){
					for(int yy = 0 ; yy < 3 ; yy++)
					{
						x_temp = GRAYIMG[y+yy][x+xx] * x_filter[xx][yy];
						y_temp = GRAYIMG[y+yy][x+xx] * y_filter[xx][yy];
					}
				}
				if(abs(x_temp + abs(y_temp)) > sld.SS)
				{
					SetPixel(x,y,0,&Second_Img);
				}
				else
				{
					SetPixel(x,y,255,&Second_Img);
				}
			}
		}
	}
}
