#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// SLD 대화 상자입니다.

class SLD : public CDialogEx
{
	DECLARE_DYNAMIC(SLD)

public:
	SLD(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~SLD();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SLIDER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl slider_im;
	CEdit box_im;
	int SS;
	afx_msg BOOL OnInitDialog();
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
};
