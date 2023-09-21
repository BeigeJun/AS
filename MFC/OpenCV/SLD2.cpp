// SLD2.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFCGAJA.h"
#include "SLD2.h"
#include "afxdialogex.h"
#include "MFCGAJADoc.h"

// SLD2 대화 상자입니다.

IMPLEMENT_DYNAMIC(SLD2, CDialogEx)

SLD2::SLD2(CWnd* pParent /*=NULL*/)
	: CDialogEx(SLD2::IDD, pParent)
{

}

SLD2::~SLD2()
{
}

void SLD2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, box_im1);
	DDX_Control(pDX, IDC_SLIDER1, slider_im1);
}


BEGIN_MESSAGE_MAP(SLD2, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &SLD2::OnEnChangeEdit1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &SLD2::OnNMCustomdrawSlider1)
END_MESSAGE_MAP()

BOOL SLD2::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	slider_im1.SetRange(-255,255);
	slider_im1.SetRangeMax(255);
	slider_im1.SetRangeMin(-255);
	slider_im1.SetPos(0);
	slider_im1.SetLineSize(5);
	slider_im1.SetPageSize(5);
	
	return TRUE;

}
// SLD2 메시지 처리기입니다.


void SLD2::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void SLD2::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int i = slider_im1.GetPos();
	CString Pos;
	Pos.Format(_T("%d"),i);
	box_im1.SetWindowText(Pos);
	SS1 = slider_im1.GetPos();
	*pResult = 0;
	*pResult = 0;
}
