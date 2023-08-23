
// MFCGAJADoc.h : CMFCGAJADoc 클래스의 인터페이스
//


#pragma once
#include <atlimage.h>
#include "SLD.h"

class CMFCGAJADoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CMFCGAJADoc();
	DECLARE_DYNCREATE(CMFCGAJADoc)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CMFCGAJADoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	bool ZOOM_flag;
	double average;
	int HISTO_arr[256];
	int HISTO_R[256];
	int HISTO_G[256];
	int HISTO_B[256];
	CImage m_Img;
	CImage Second_Img;
	CImage Pro_w;
	CImage Pro_h;
	CImage HISTO_Img;
	CImage HISTO_str_Img;
	CImage HISTO_R_Img;
	CImage HISTO_G_Img;
	CImage HISTO_B_Img;
	int** GRAYIMG;
	void CMFCGAJADoc::SetPixel(int x, int y, BYTE color, CImage * image);
	void CMFCGAJADoc::OnFileOpen();
	void CMFCGAJADoc::GRAY();
	void CMFCGAJADoc::MAKE_GRAY();
	void CMFCGAJADoc::Binary();
	void CMFCGAJADoc::Slider();
	void CMFCGAJADoc::Sobel();
	void CMFCGAJADoc::PROJECTION(int select);
	void CMFCGAJADoc::HISTO();
	void CMFCGAJADoc::HISTO_streching();
	void CMFCGAJADoc::HISTO_equalization();
	void CMFCGAJADoc::HISTO_RGB();
	void CMFCGAJADoc::ZOOM();
#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);

#endif // SHARED_HANDLERS
};
