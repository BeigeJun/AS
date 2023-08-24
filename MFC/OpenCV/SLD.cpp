// SLD.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFCGAJA.h"
#include "SLD.h"
#include "afxdialogex.h"
#include "MFCGAJADoc.h"

// SLD 대화 상자입니다.

IMPLEMENT_DYNAMIC(SLD, CDialogEx)

SLD::SLD(CWnd* pParent /*=NULL*/)
	: CDialogEx(SLD::IDD, pParent)
{

}

SLD::~SLD()
{
}

void SLD::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, slider_im);
	DDX_Control(pDX, IDC_EDIT1, box_im);
}


BEGIN_MESSAGE_MAP(SLD, CDialogEx)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &SLD::OnNMCustomdrawSlider1)
	ON_BN_CLICKED(IDOK, &SLD::OnBnClickedOk)
END_MESSAGE_MAP()


// SLD 메시지 처리기입니다.



BOOL SLD::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	slider_im.SetRange(0,255);
	slider_im.SetRangeMax(255);
	slider_im.SetRangeMin(0);
	slider_im.SetPos(125);
	slider_im.SetLineSize(5);
	slider_im.SetPageSize(5);
	
	return TRUE;

}



void SLD::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	int i = slider_im.GetPos();
	CString Pos;
	Pos.Format(_T("%d"),i);
	box_im.SetWindowText(Pos);
	SS = slider_im.GetPos();
	*pResult = 0;
}


void SLD::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	slider_im.SetPos(SS);
	CDialogEx::OnOK();
}
