
// MFCGAJADoc.cpp : CMFCGAJADoc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFCGAJA.h"
#include "SLD.h"
#include "SLD2.h"
#endif

#include "MFCGAJADoc.h"

#include <propkey.h>
#include <algorithm>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCGAJADoc

IMPLEMENT_DYNCREATE(CMFCGAJADoc, CDocument)

BEGIN_MESSAGE_MAP(CMFCGAJADoc, CDocument)
		ON_COMMAND(ID_FILE_OPEN, &CMFCGAJADoc::OnFileOpen)
		ON_COMMAND(ID_FILE_SAVE, &CMFCGAJADoc::OnFileSave)
		ON_COMMAND(ID_GRAY, &CMFCGAJADoc::GRAY)
		ON_COMMAND(ID_Binary, &CMFCGAJADoc::Binary)
		ON_COMMAND(ID_SLIDER, &CMFCGAJADoc::Slider)
		ON_COMMAND(ID_SOBEL, &CMFCGAJADoc::Sobel)
		ON_COMMAND(ID_RGB, &CMFCGAJADoc::HISTO_RGB)
		ON_COMMAND(ID_STRECHING, &CMFCGAJADoc::HISTO_streching)
		ON_COMMAND(ID_EQUALIZATION, &CMFCGAJADoc::HISTO_equalization)
		ON_COMMAND(ID_FIND, &CMFCGAJADoc::FIND)
		ON_COMMAND(ID_BRIGHT, &CMFCGAJADoc::Bright)
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
	money_flag = false;
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
SLD2 sld1;

void CMFCGAJADoc::Slider()
{
	sld.SS =128;
	sld.DoModal();
}

void CMFCGAJADoc::Bright()
{
	sld1.SS1 =128;
	sld1.DoModal();
	int bright = sld1.SS1;

		for(int i = 0; i < m_Img.GetWidth(); i++){
			int sum=0;
			for(int j = 0; j < m_Img.GetHeight(); j++){
				int rgb[3];
				COLORREF pix_data;
				memcpy(&pix_data, m_Img.GetPixelAddress(i, j), 3);
				rgb[0] = GetRValue(pix_data);
				rgb[1] = GetGValue(pix_data);
				rgb[2] = GetBValue(pix_data);
				for(int k = 0; k < 3 ; k++){
					rgb[k] += bright;
					if(rgb[k] > 255) rgb[k] = 255;
					else if (rgb[k] < 0) rgb[k] = 0;
				}
				pix_data = RGB(rgb[0], rgb[1], rgb[2]);
				memcpy(m_Img.GetPixelAddress(i, j), &pix_data, 3);
			}
		}
	/*for(int a = 0 ; m_Img.GetHeight()-1 > a ; a++)
	{
		for(int b = 0 ; m_Img.GetWidth()-1 > b; b++)
		{
			int red, green, blue;
			COLORREF* color;
			color = (COLORREF*)m_Img.GetPixelAddress(a,b);

			red = GetRValue(*color);
			green = GetGValue(*color);
			blue = GetBValue(*color);

			red += sld1.SS1;
			green += sld1.SS1;
			blue += sld1.SS1;
			if(red > 255)
			{red=255;}
			if(green > 255)
			{green=255;}
			if(blue > 255)
			{blue=255;}
			if(red<0)
			{red=0;}
			if(blue<0)
			{blue=0;}
			if(green<0)
			{green=0;}
			m_Img.SetPixel(a,b,RGB(red,green,blue));
		}
	}
	*/
	UpdateAllViews(NULL);
}

void CMFCGAJADoc::OnFileOpen()
{
	TCHAR strFilter[] = _T("JPEG 이미지|*.jpg|PNG 이미지|*.png|Bitmap 이미지|*.bmp|Raw 이미지|*.raw|Raw3 이미지|*.raw3|");
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY| OFN_FILEMUSTEXIST|OFN_ALLOWMULTISELECT, strFilter);//TRUE 읽기

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
		case 4:
			{
				int w, h, i, j;
				BYTE value=0;
				COLORREF pix_data;
				file.Open(filePath, CFile::modeRead, NULL);
				file.Read(&w, 4);
				file.Read(&h, 4);
				m_Img.Create(w, h, 24);

				for(i = 0; i < h; i++){
					for(j = 0; j < w; j++){
						file.Read(&value, 1);
						pix_data = RGB(value, value, value);
						memcpy(m_Img.GetPixelAddress(j, i), &pix_data, 3);
					}
				}
				break;
				file.Close();
			}
		case 5: // raw 컬러 이미지
			{
				int w, h, i, j;
				//BYTE r, g, b;
				COLORREF pix_data=0;
				file.Open(filePath, CFile::modeRead, NULL);
				file.Read(&w, 4);
				file.Read(&h, 4);
				m_Img.Create(w, h, 24);

				for(i = 0; i < h; i++){
					for(j = 0; j < w; j++){
						file.Read(&pix_data, 3);
						memcpy(m_Img.GetPixelAddress(j, i), &pix_data, 3);
					}
				}
				break;
			}
			file.Close();
		default:
			m_Img.Load(filePath);
		}
	}
	UpdateAllViews(NULL);// 뷰 갱신
}

void CMFCGAJADoc::OnFileSave(){
	if (!m_Img.IsNull()){
		TCHAR strFilter[] = _T("JPEG 이미지|*.jpg|PNG 이미지|*.png|Bitmap 이미지|*.bmp|Raw 이미지|*.raw|Raw3 이미지|*.raw3|");
		CFileDialog fileDlg(FALSE, NULL, NULL, OFN_HIDEREADONLY, strFilter);
		CString filePath;

		if(fileDlg.DoModal() == IDOK)
		{	
			filePath = fileDlg.GetPathName();
			switch(fileDlg.m_ofn.nFilterIndex)
			{
			case 1:
				filePath += _T(".jpg");
				m_Img.Save(filePath, Gdiplus::ImageFormatJPEG);
				break;
			case 2:
				filePath += _T(".png");
				m_Img.Save(fileDlg.GetPathName(), Gdiplus::ImageFormatPNG);
				break;
			case 3:
				filePath += _T(".bmp");
				m_Img.Save(fileDlg.GetPathName(), Gdiplus::ImageFormatBMP);
				break;
			case 4: // raw파일 저장할거야
				{
					filePath += _T(".raw");
					CFile file;
					int w = m_Img.GetWidth();
					int h = m_Img.GetHeight();
					MAKE_GRAY();
					file.Open(filePath,CFile::modeCreate | CFile::modeWrite, NULL);
					file.Write(&w, 4);
					file.Write(&h, 4);
					for(int i = 0; i < h; i++){
						for(int j = 0; j < w ; j++){
							BYTE pix_temp = GRAYIMG[i][j];
							file.Write(&pix_temp, 1);
						}
					}
					file.Close();
					break;
				}
			case 5:
				{
					filePath += _T(".raw3");
					CFile file;
					int w = m_Img.GetWidth();
					int h = m_Img.GetHeight();

					file.Open(filePath,CFile::modeCreate | CFile::modeWrite, NULL);
					file.Write(&w, 4);
					file.Write(&h, 4);
					for(int i = 0; i < h; i++){
						for(int j = 0; j < w; j++){
							COLORREF pix_data;
							memcpy(&pix_data, m_Img.GetPixelAddress(j, i), 3);
							file.Write(&pix_data, 3);
						}
					}
					file.Close();
					break;
				}
			}
		}	
	}
}

void CMFCGAJADoc::SetPixel(int x, int y, BYTE color, CImage * image){

	BYTE *p = (BYTE*)image->GetPixelAddress(x, y);					//포인터 사용하여서 주소 바꿔줌 -> 기존 라이브러리함수 setpixel보다 속도가 빠름
	*p++ = color;
	*p++ = color;
	*p = color;
}

void CMFCGAJADoc::GRAY()
{
	MAKE_GRAY();

	if(!m_Img.IsNull()){
		for(int y = 0; y < m_Img.GetHeight()-1;y++){
			for(int x = 0 ; x < m_Img.GetWidth()-1; x++){
				SetPixel(x,y,GRAYIMG[y][x],&Second_Img);
			}
		}
		mode = 0;
		HISTO();
//		HISTO_RGB();
		PROJECTION(0);
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

void CMFCGAJADoc::MAKE_GRAY()
{
	COLORREF* color;
	int r,g,b,new_color;
	average = 0;

	for( int i = 0 ; i <=255 ; i++)
	{
		HISTO_arr[i] = 0;
		HISTO_R[i] = 0;
		HISTO_G[i] = 0;
		HISTO_B[i] = 0;
	}

	if(!m_Img.IsNull()){
		if(!Second_Img.IsNull())
		{
			Second_Img.Destroy();
		}
		if(!Pro_w.IsNull())
		{
			Pro_w.Destroy();
		}
		if(!Pro_h.IsNull())
		{
			Pro_h.Destroy();
		}
		if(!HISTO_Img.IsNull())
		{
			HISTO_Img.Destroy();
		}
		if(!HISTO_R_Img.IsNull())
		{
			HISTO_R_Img.Destroy();
		}
		if(!HISTO_G_Img.IsNull())
		{
			HISTO_G_Img.Destroy();
		}
		if(!HISTO_B_Img.IsNull())
		{
			HISTO_B_Img.Destroy();
		}
		if(!MONEY.IsNull())
		{
			MONEY.Destroy();
		}
		if(!MONEY_Price.IsNull())
		{
			MONEY_Price.Destroy();
		}
		if(!MONEY_Price_P.IsNull())
		{
			MONEY_Price_P.Destroy();
		}
		if(!MONEY_BINARY.IsNull())
		{
			MONEY_BINARY.Destroy();
		}
		Second_Img.Create(m_Img.GetWidth(), m_Img.GetHeight(), 24); // 24비트 비트맵 생성

		GRAYIMG = new int*[m_Img.GetHeight()];

		for(int i = 0; i < m_Img.GetHeight(); i++)
		{
			GRAYIMG[i] = new int[m_Img.GetWidth()];
		}

		for(int y = 0; y < m_Img.GetHeight()-1;y++){
			for(int x = 0 ; x < m_Img.GetWidth()-1; x++){
				color = (COLORREF*)m_Img.GetPixelAddress(x,y);

				r = GetRValue(*color);
				g = GetGValue(*color);
				b = GetBValue(*color);

				new_color = (r+b+g)/3;

//				HISTO_arr[(int)new_color] += 1;
				HISTO_R[(int)r] += 1;
				HISTO_G[(int)g] += 1;
				HISTO_B[(int)b] += 1;

				average += new_color;

				GRAYIMG[y][x] = new_color;
			}
		}
		average /= m_Img.GetHeight() * m_Img.GetWidth();

    }
	UpdateAllViews(NULL);
}

void CMFCGAJADoc::Binary()
{
	if(!m_Img.IsNull()){
		MAKE_GRAY();		
		BINARYIMG = new int*[m_Img.GetHeight()];

		for(int i = 0; i < m_Img.GetHeight(); i++)
		{
			BINARYIMG[i] = new int[m_Img.GetWidth()];
		}
		
		for(int y = 0; y < m_Img.GetHeight()-1;y++){
			for(int x = 0 ; x < m_Img.GetWidth()-1; x++)
			{
				if(GRAYIMG[y][x] > sld.SS)
				{
					SetPixel(x,y,255,&Second_Img);
					BINARYIMG[y][x] = 255;
				}
				else
				{
					SetPixel(x,y,0,&Second_Img);
					BINARYIMG[y][x] = 0;
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
	mode = 1;
	HISTO();
	PROJECTION(1);
	UpdateAllViews(NULL);
}

void CMFCGAJADoc::Sobel()
{
	if(!m_Img.IsNull()){

		MAKE_GRAY();

		int x_filter[3][3]={{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
		int y_filter[3][3]={{1, 2, 1}, {0, 0, 0}, {-1, -2, -1}};

		SOBELIMG = new int*[m_Img.GetHeight()];

		for(int i = 0; i <  m_Img.GetHeight(); i++)
		{
			SOBELIMG[i] = new int[m_Img.GetWidth()];
		}
		

		for(int w = 1 ; w < m_Img.GetWidth() - 1 ; w++){
			for(int h = 1; h < m_Img.GetHeight() -1 ; h++){
				int x_temp = 0, y_temp = 0;
				for(int a = 0 ; a < 3 ; a++){
					for(int b = 0 ; b < 3 ; b++)
					{
						x_temp += GRAYIMG[h-1+a][w-1+b] * x_filter[a][b];
						y_temp += GRAYIMG[h-1+a][w-1+b] * y_filter[a][b];
					}
				}
				if((abs(x_temp) + abs(y_temp)) > sld.SS)
				{
					SetPixel(w,h,255,&Second_Img);
					SOBELIMG[h][w] = 255; 
				}
				else
				{
					SetPixel(w,h,0,&Second_Img);
					SOBELIMG[h][w] = 0;
				}
			}
		}
	}
	mode = 2;
	HISTO();
	PROJECTION(2);
	UpdateAllViews(NULL);
}

void CMFCGAJADoc::PROJECTION(int select)
{
	Pro_w.Create(Second_Img.GetWidth()+1, Second_Img.GetHeight()+1, 24);
	Pro_h.Create(Second_Img.GetWidth()+1, Second_Img.GetHeight()+1, 24);
	int x_p_sum = 0;
	int y_p_sum = 0;
	start_x = 0, start_y = 0 , end_x = 0,end_y = 0 ;
	int str_x = 0, str_y = 0 , ed_x = 0,ed_y = 0 ;
	switch(select)
	{
	case 0:
		for(int y = Second_Img.GetHeight()-1 ; y > 0 ; y--)
		{
			for(int x = Second_Img.GetWidth()-1 ; x > 0 ; x--)
			{
				if(average  < GRAYIMG[y][x])
				{
					y_p_sum++;
				}
			}
			for(int xx = 0 ; xx <= Second_Img.GetWidth()-1 - y_p_sum ; xx++)
			{
				SetPixel(xx,y,0,&Pro_w);
			}
			for(int xx = Second_Img.GetWidth()-1 -(y_p_sum + 1) ; xx < Second_Img.GetWidth()-1 ; xx++)
			{
				SetPixel(xx,y,255,&Pro_w);
			}
			y_p_sum = 0;
		}

		for(int x = Second_Img.GetWidth()-1 ; x > 0 ; x--)
		{
			for(int y = Second_Img.GetHeight()-1 ; y > 0 ; y--)
			{
				if(average  < GRAYIMG[y][x])
				{
					x_p_sum++;
				}
			}
			for(int yy = 0 ; yy <= Second_Img.GetHeight()-1 -x_p_sum ; yy++)
			{
				SetPixel(x,yy,0,&Pro_h);
			}
			for(int yy = Second_Img.GetHeight()-1 -(x_p_sum + 1) ; yy < Second_Img.GetHeight()-1 ; yy++)
			{
				SetPixel(x,yy,255,&Pro_h);
			}
			x_p_sum = 0;
		}
		UpdateAllViews(NULL);
		break;
	case 1:
		for(int y = 0 ; y < m_Img.GetHeight() ; y++)
		{
			for(int x = 0 ; x < m_Img.GetWidth() ; x++)
			{
				if(sld.SS  < BINARYIMG[y][x])
				{
					y_p_sum++;
				}
			}
			for(int xx = 0 ; xx <= y_p_sum ; xx++)
			{
				SetPixel(xx,y,0,&Pro_w);
			}
			for(int xx = y_p_sum + 1 ; xx < m_Img.GetWidth()-1 ; xx++)
			{
				SetPixel(xx,y,255,&Pro_w);
			}
			y_p_sum = 0;
		}

		for(int x = 0 ; x < Second_Img.GetWidth() ; x++)
		{
			for(int y = 0 ; y < Second_Img.GetHeight(); y++)
			{
				if(sld.SS  < BINARYIMG[y][x])
				{
					x_p_sum++;
				}
			}
			for(int yy = 0 ; yy <= x_p_sum ; yy++)
			{
				SetPixel(x,yy,0,&Pro_h);
			}
			for(int yy = x_p_sum + 1 ; yy < Second_Img.GetHeight()-1 ; yy++)
			{
				SetPixel(x,yy,255,&Pro_h);
			}
			x_p_sum = 0;
		}
		break;
		case 2:

		HIGH_p = new int[m_Img.GetHeight()];
		WIDTH_p = new int[m_Img.GetWidth()];

		for(int y = 0 ; y < m_Img.GetHeight() ; y++)
		{
			int x;
			for(x = 0 ; x < m_Img.GetWidth() ; x++)
			{
				if(sld.SS  < SOBELIMG[y][x])
				{
					x_p_sum++;
				}
			}
			HIGH_p[y] = x_p_sum;
			for(int xx = 0 ; xx <= x_p_sum ; xx++)
			{
				SetPixel(xx,y,0,&Pro_w);
			}
			for(int xx = x_p_sum + 1 ; xx < m_Img.GetWidth()-1 ; xx++)
			{
				SetPixel(xx,y,255,&Pro_w);
			}
			x_p_sum = 0;
		}

		for(int x = 0 ; x < Second_Img.GetWidth() ; x++)
		{
			int y;
			for(y = 0 ; y < Second_Img.GetHeight(); y++)
			{
				if(sld.SS  < SOBELIMG[y][x])
				{
					y_p_sum++;
				}
			}
			WIDTH_p[x] = y_p_sum;
			for(int yy = 0 ; yy <= y_p_sum ; yy++)
			{
				SetPixel(x,yy,0,&Pro_h);
			}
			for(int yy = y_p_sum + 1 ; yy < Second_Img.GetHeight()-1 ; yy++)
			{
				SetPixel(x,yy,255,&Pro_h);
			}
			y_p_sum = 0;
		}
		str_y = HIGH_p[0];
		for(int y = 1 ; y < Second_Img.GetHeight()-2 ; y++)
		{
			if(str_y < HIGH_p[y])
			{
				start_y = y;
				str_y = HIGH_p[y];
			}
		}
		str_y = HIGH_p[0];
		for(int y = 1 ; y < Second_Img.GetHeight()-2 ; y++)
		{
			if(str_y < HIGH_p[y])
			{//!((y < start_y+50) && (y > start_y-50))
				if(!((y < start_y+50) && (y > start_y-50)))
				{
					end_y = y;
					str_y = HIGH_p[y];
				}
			}
		}
		str_x = WIDTH_p[0];
		for(int x = 1 ; x < Second_Img.GetWidth()-2 ; x++)
		{
			if(str_x < WIDTH_p[x])
			{
				start_x = x;
				str_x = WIDTH_p[x];
			}
		}
		str_x = WIDTH_p[0];
		for(int x = 1 ; x < Second_Img.GetWidth()-2 ; x++)
		{
			if(str_x < WIDTH_p[x])
			{//!((y < start_y+50) && (y > start_y-50))
				if(!((x < start_x+50) && (x > start_x-50)))
				{
					end_x = x;
					str_x = WIDTH_p[x];
				}
			}
		}
		UpdateAllViews(NULL);
		break;
	}
}

void CMFCGAJADoc::HISTO()
{
	int MAX = 0;
	switch(mode)
	{
		case 0:
		{
			for(int y = 0; y < m_Img.GetHeight()-1;y++){
				for(int x = 0 ; x < m_Img.GetWidth()-1; x++){
					int num = GRAYIMG[y][x];
					HISTO_arr[num]++;
				}
			}
			for(int i = 0 ; i <= 255 ; i++)
			{
				if(HISTO_arr[i] > MAX)
				{
					MAX = HISTO_arr[i];
				}
			}

			if(HISTO_Img.Create(255, MAX, 24) != 0)
			{
				for(int x = 0 ; x < 255 ; x++)
				{
					for(int y = 0 ; y < MAX ; y++)
					{
						if(y < HISTO_arr[x])
						{
							SetPixel(x,MAX-y-1,0,&HISTO_Img);
						}
						else
						{
							SetPixel(x,MAX-y-1,255,&HISTO_Img);
						}
					}
				}	
			}
			break;
		}

		case 1:
		{
		for(int y = 0; y < m_Img.GetHeight()-1;y++){
			for(int x = 0 ; x < m_Img.GetWidth()-1; x++){
				int num = BINARYIMG[y][x];
				HISTO_arr[num]++;
			}
		}
		for(int i = 0 ; i <= 255 ; i++)
			{
				if(HISTO_arr[i] > MAX)
				{
					MAX = HISTO_arr[i];
				}
			}

		if(HISTO_Img.Create(255, MAX, 24) != 0)
		{
			for(int x = 0 ; x <= 5 ; x++)
			{
				for(int y = 0 ; y < MAX ; y++)
				{
					if(y < HISTO_arr[0])
					{
						SetPixel(x+1,MAX-y-1,255,&HISTO_Img);
					}
					else
					{
						SetPixel(x+1,MAX-y-1,0,&HISTO_Img);
					}
				}
			}
			for(int x = 250 ; x <= 255 ; x++)
			{
				for(int y = 0 ; y < MAX ; y++)
				{
					if(y < HISTO_arr[255])
					{
						SetPixel(x-2,MAX-y-1,255,&HISTO_Img);
					}
					else
					{
						SetPixel(x-2,MAX-y-1,0,&HISTO_Img);
					}
				}
			}
		}
		break;
		}
		case 2:
			{
			for(int y = 1; y < m_Img.GetHeight()-1;y++){
				for(int x = 1 ; x < m_Img.GetWidth()-1; x++){
					int num = SOBELIMG[y][x];
					HISTO_arr[num]++;
				}
			}
			for(int i = 0 ; i <= 255 ; i++)
			{
				if(HISTO_arr[i] > MAX)
				{
					MAX = HISTO_arr[i];
				}
			}
			if(HISTO_Img.Create(255, MAX, 24) != 0)
			{
			for(int x = 0 ; x <= 5 ; x++)
			{
				for(int y = 0 ; y < MAX ; y++)
				{
					if(y < HISTO_arr[0])
					{
						SetPixel(x+1,MAX-y-1,255,&HISTO_Img);
					}
					else
					{
						SetPixel(x+1,MAX-y-1,0,&HISTO_Img);
					}
				}
			}
			for(int x = 250 ; x <= 255 ; x++)
			{
				for(int y = 0 ; y < MAX ; y++)
				{
					if(y < HISTO_arr[255])
					{
						SetPixel(x-2,MAX-y-1,255,&HISTO_Img);
					}
					else
					{
						SetPixel(x-2,MAX-y-1,0,&HISTO_Img);
					}
				}
			}
		}
			break;
			}
	}
	UpdateAllViews(NULL);
}

void CMFCGAJADoc::HISTO_streching()
{
	int MAX = 0;
	int MIN = 255;
	int MULT;

	MAKE_GRAY();

	for(int x = 0 ; x < Second_Img.GetWidth() -1; x++)
	{
		for(int y = 0 ; y < Second_Img.GetHeight() -1; y++)
		{
			MAX = max(GRAYIMG[y][x],MAX);
			MIN = min(GRAYIMG[y][x],MIN);
		}
	}
	
	MULT = 255 / (MAX - MIN);
	if(!HISTO_Img.IsNull())
	{
		HISTO_Img.Destroy();
	}

//	if(HISTO_str_Img.Create(Second_Img.GetWidth(), Second_Img.GetHeight(), 24) != 0)
//	{
		for(int x = 0 ; x < Second_Img.GetWidth()-1 ; x++)
		{
			for(int y = 0 ; y < Second_Img.GetHeight()-1 ; y++)
			{
				int new_color = (GRAYIMG[y][x]-MIN)*MULT;
				GRAYIMG[y][x] = new_color;
				Second_Img.SetPixel(x,y,RGB(new_color,new_color,new_color));

			}
		}	
//	}
	mode = 0;
	HISTO();
	UpdateAllViews(NULL);
}

void CMFCGAJADoc::HISTO_equalization()
{
	MAKE_GRAY();
	int new_Img[256] = {0,};
	for(int y = 0; y < m_Img.GetHeight()-1;y++){
		for(int x = 0 ; x < m_Img.GetWidth()-1; x++){
			int num = GRAYIMG[y][x];
			HISTO_arr[num]++;
		}
	}
	int eq_Max = 0;
	for(int i = 0; i <256 ; i++)
	{
		if(eq_Max < HISTO_arr[i])
		{
			eq_Max = HISTO_arr[i];
		}
	}
	int temp;
	int sum = HISTO_arr[0];
	int color_sum[256] = {0,};
	color_sum[0] = HISTO_arr[0];
	int total_pixel = m_Img.GetWidth() * m_Img.GetHeight();
	//전체

	for(int i = 1; i < 256 ; i++)
	{
		sum += HISTO_arr[i];
		color_sum[i] = sum;
		//누적 배열
	}

	for(int i = 0 ; i < 256 ; i++)
	{
		new_Img[i] = ((float)color_sum[i] / total_pixel)*eq_Max;
		int img = new_Img[i]*10;
		if((img/5)%2 == 0)
		{
			img -= img%5;
			img /= 10;
		}
		else
		{
			img += img%5;
			img /= 10;
		}
		new_Img[i] = img;
	}
	memset(HISTO_arr, 0, 256 * sizeof(int));
	for(int y = 0; y < m_Img.GetHeight()-1;y++){
		for(int x = 0 ; x < m_Img.GetWidth()-1; x++){
			temp = GRAYIMG[y][x];
			Second_Img.SetPixel(x,y,RGB(new_Img[temp],new_Img[temp],new_Img[temp]));
			GRAYIMG[y][x] = new_Img[temp];
			HISTO_arr[GRAYIMG[y][x]]++;
		}
	}
	mode = 0;
	HISTO();
}

void CMFCGAJADoc::HISTO_RGB()
{
	MAKE_GRAY();
	int MAX_R = 0, MAX_G = 0, MAX_B =0;
	for(int i = 0 ; i <= 255 ; i++)
	{
		if(HISTO_R[i] > MAX_R)
		{
			MAX_R = HISTO_R[i];
		}
		if(HISTO_G[i] > MAX_G)
		{
			MAX_G = HISTO_G[i];
		}
		if(HISTO_B[i] > MAX_B)
		{
			MAX_B = HISTO_B[i];
		}
	}
	HISTO_R_Img.Create(256, MAX_R, 24);
	HISTO_G_Img.Create(256, MAX_G, 24);
	HISTO_B_Img.Create(256, MAX_B, 24);

	for(int x = 0 ; x < 256 ; x++)
		{
		for(int y = 0 ; y < MAX_R ; y++)
		{
			if(y < HISTO_R[x])
			{
				SetPixel(x,MAX_R-y-1,0,&HISTO_R_Img);
			}
			else
			{
				SetPixel(x,MAX_R-y-1,255,&HISTO_R_Img);
			}
		}
		for(int y = 0 ; y < MAX_G ; y++)
		{
			if(y < HISTO_G[x])
			{
				SetPixel(x,MAX_G-y-1,0,&HISTO_G_Img);
			}
			else
			{
				SetPixel(x,MAX_G-y-1,255,&HISTO_G_Img);
			}
		}
		for(int y = 0 ; y < MAX_B ; y++)
		{
			if(y < HISTO_B[x])
			{
				SetPixel(x,MAX_B-y-1,0,&HISTO_B_Img);
			}
			else
			{
				SetPixel(x,MAX_B-y-1,255,&HISTO_B_Img);
			}
		}
	}
	UpdateAllViews(NULL);
}

void CMFCGAJADoc::FIND()
{
	Sobel();
	if(start_x > end_x)
	{
		int temp = start_x;
		start_x = end_x;
		end_x = temp;
	}
	if(start_y > end_y)
	{
		int temp = start_y;
		start_y = end_y;
		end_y = temp;
	}

	//소벨을 먹인다음 시작점과 끝점의 크기값을 비교하고 크면 바꾸기.

	MONEY.Create(end_x - start_x, end_y - start_y, 24);

	MONEYIMG = new int*[end_y - start_y];

	for(int i = 0; i <  end_y - start_y; i++)
	{
		MONEYIMG[i] = new int[end_x - start_x];
	}
	//머니 비트맵 만들고 머니 더블포인터 만들기
	money_flag = true;
	for(int y =  start_y; y < end_y-1 ; y++)
	{
		for(int x = start_x ; x < end_x-1; x++)
		{
			int a = GRAYIMG[y][x];
			SetPixel(x-start_x,y-start_y,a,&MONEY);
			MONEYIMG[y-start_y][x-start_x] = a;
		}
	}
	//따온 돈 사진 출력 MONEY, MONEYIMG
	MONEY_Price.Create(MONEY.GetWidth()/3+1,MONEY.GetHeight()/4+1, 24);

	MONEYPRICEIMG = new int*[MONEY.GetHeight()/4+1];

	for(int i = 0; i <  MONEY.GetHeight()/4+1; i++)
	{
		MONEYPRICEIMG[i] = new int[MONEY.GetWidth()/3+1];
	}

	for(int y = MONEY.GetHeight()/4*3; y <MONEY.GetHeight()-1 ; y++)
	{
		for(int x = 0 ; x < MONEY.GetWidth()/3; x++)
		{
			int a = MONEYIMG[y][x];
			MONEYPRICEIMG[y-(MONEY.GetHeight()/4*3)][x] = a;
			SetPixel(x,y-(MONEY.GetHeight()/4*3),a,&MONEY_Price);
		}
	}
	//따온 돈에서 숫자부분 빼오기 MONEY_Price, MONEYPRICEIMG
	
	MONEY_BINARY.Create(MONEY_Price.GetWidth(), MONEY_Price.GetHeight(), 24);

	MONEY_BINARYIMG = new int*[MONEY_Price.GetHeight()];

	for(int i = 0; i < MONEY_Price.GetHeight(); i++)
		{
			MONEY_BINARYIMG[i] = new int[MONEY_Price.GetWidth()];
		}
		
		for(int y = 0; y < MONEY_Price.GetHeight()-1;y++){
			for(int x = 0 ; x < MONEY_Price.GetWidth()-1; x++)
			{
				if(MONEYPRICEIMG[y][x] > 110) //140
				{
					SetPixel(x,y,0,&MONEY_BINARY);
					MONEY_BINARYIMG[y][x] = 0;
				}
				else
				{
					SetPixel(x,y,255,&MONEY_BINARY);
					MONEY_BINARYIMG[y][x] = 255;
				}
			}
		}

	//바이러니화 하기

	int x_p_sum = 0;

	MONEY_Price_P.Create(MONEY_Price.GetWidth(), MONEY_Price.GetHeight(), 24);

	MONEYIMG_P = new int*[ MONEY_Price.GetHeight()];

	for(int i = 0; i <   MONEY_Price.GetHeight(); i++)
	{
		MONEYIMG_P[i] = new int[MONEY_Price.GetWidth()];
	}
	bool flag = false;
	int start = 0;
	int ax[300] = { 0,};
	int bx[268] = {3,3,2,5,4,1,2,4,1,2,4,1,1,3,3,5,25,36,29,31,30,31,29,28,28,2831,37,32,35,24,8,0,0,0,0,0,0,0,0,0,0,21,20,23,28,25,24,27,30,30,25,41,30,40,27,23,14,9,13,11,11,11,10,10,12,9,11,12,9,10,9,16,12,15,22,28,41,32,28,31,34,24,26,24,24,17,21,17,12,8,0,0,0,0,0,0,0,2,18,18,21,18,25,24,26,27,27,21,30,29,32,32,20,13,12,9,10,11,8,8,6,8,8,8,7,7,9,11,9,16,18,21,48,30,38,35,33,30,26,31,27,26,23,26,16,10,8,0,0,0,0,0,0,0,25,23,27,22,25,24,31,24,19,29,26,24,30,25,15,16,11,11,10,11,11,11,12,10,14,10,12,9,11,9,10,14,18,26,40,33,29,35,30,22,33,34,25,27,24,17,15,15,0,0,0,0,0,0,0,16,25,20,28,29,27,36,34,31,32,40,35,36,38,30,20,21,17,17,17,20,25,23,24,21,20,25,23,22,24,29,37,51,61,57,55,57,58,55,50,57,51,51,47,44,33,29,8,0,0,1,0,1,37,37,46,39,47,48};
	for(int x = MONEY_Price.GetWidth()-1 ; x > 0 ; x--)
		{

			for(int y = MONEY_Price.GetHeight()-1 ; y > 0; y--)
			{
				if(250 < MONEY_BINARYIMG[y][x])
				{
					x_p_sum++;
				}
			}
			ax[x] = x_p_sum;
			for(int yy = 0 ; yy <= MONEY_Price.GetHeight()-1 -x_p_sum ; yy++)
			{
				SetPixel(x,yy,0,&MONEY_Price_P);
				MONEYIMG_P[yy][x] = 0;
			}
			for(int yy = MONEY_Price.GetHeight()-1 -(x_p_sum + 1) ; yy < MONEY_Price.GetHeight()-1 ; yy++)
			{
				SetPixel(x,yy,255,&MONEY_Price_P);
				MONEYIMG_P[yy][x] = 255;
			}
			x_p_sum = 0;
		}
	//현금화한부분 프로젝션 만들기
	for(int x = 0 ; x < MONEY_Price.GetWidth()-1 ; x++)
	{
		if(ax[x] == 0){start++;}
		else{break;}
	}
	int count = 0, move = 0;
	for(int x = 0 ; x < 268 ; x++)
	{
		if(ax[x+start+move]+3 > bx[x] && ax[x+start+move]-3 < bx[x])
		{count++;}
		else if(ax[x+start+move+1]+3 > bx[x] && ax[x+start+move+1]-3 < bx[x])
		{
			count=count+2;
			move++;
		}
		else if(ax[x+start+move-1]+3 > bx[x] && ax[x+start+move-1]-3 < bx[x])
		{
			count=count+1;
			move--;
		}
	}
	if(count > 220)
	{
		MessageBox(NULL, _T("만원입니다"), _T("축하합니다!"), NULL);
	}
	else
	{
		MessageBox(NULL, _T("만원이 아닙니다"), _T("이런!"), NULL);
	}
	UpdateAllViews(NULL);
}
