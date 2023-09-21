#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// SLD2 대화 상자입니다.

class SLD2 : public CDialogEx
{
	DECLARE_DYNAMIC(SLD2)

public:
	SLD2(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~SLD2();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SLIDE2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int SS1;
	afx_msg BOOL OnInitDialog();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	CEdit box_im1;
	CSliderCtrl slider_im1;
};
