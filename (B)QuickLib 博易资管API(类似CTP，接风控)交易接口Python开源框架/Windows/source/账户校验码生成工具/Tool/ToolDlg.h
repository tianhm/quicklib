
// ReportToolDlg.h : 头文件
//

#pragma once
#include "Aes.h"

class CReportToolDlg : public CDialogEx
{
// 构造
public:

 

	//AES加密
	int char2num(TCHAR ch);
	BOOL WCharToMByte(LPCWSTR lpcwszStr, LPSTR lpszStr, DWORD dwSize);
	BOOL MByteToWChar(LPCSTR lpcszStr, LPWSTR lpwszStr, DWORD dwSize);
	BSTR OnBAesEn(wchar_t *wText);
	BSTR OnBAesDe(wchar_t *wText);
	BSTR MoreStrOnBAesEn(CString leftstr);
	BSTR MoreStrOnBAesDe(CString leftstr);
	//AES加密





	BOOL ReadConfigFile();

	CReportToolDlg(CWnd* pParent = NULL);	// 标准构造函数
 
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REPORTTOOL_DIALOG };
#endif

	void OnTimer(UINT_PTR nIDEvent);


	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


	//bool DLL_Create();
 
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
