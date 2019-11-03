
// ID_Card_No_GenerateDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CID_Card_No_GenerateDlg �Ի���
class CID_Card_No_GenerateDlg : public CDialogEx
{
// ����
public:
	CID_Card_No_GenerateDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ID_CARD_NO_GENERATE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
    void OnClose();
    void UpdateUI();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg
        void LoadIDInfo();
    void OnBnClickedButtonGenerate();
    CComboBox m_comboYear;
    CComboBox m_comboMonth;
    CComboBox m_comboDay;
    CComboBox m_comboProvincial;
    CComboBox m_comboMunicipal;
    CComboBox m_comboCounty;
    CComboBox m_comboCount;
    CComboBox m_comboMale;
    CEdit m_editIDNumber;
    CEdit m_editIDNumberInput;
    CEdit m_editIDInfo;
    CString m_strModulePath;
    CString m_strCacheFilePath;
    CMap < INT, INT, CString, LPCTSTR > mapProvincial;
    CMap < INT, INT, CString, LPCTSTR > mapMunicipal;
    CMap < INT, INT, CString, LPCTSTR > mapCounty;
    CMap < CString, LPCTSTR, INT, INT > mapProvincialReverse;
    CMap < CString, LPCTSTR, INT, INT > mapMunicipalReverse;
    CMap < CString, LPCTSTR, INT, INT > mapCountyReverse;
    CMap < INT, INT, CString, LPCTSTR > mapCountyAll;
    afx_msg void OnCbnSelchangeComboProvinical();
    afx_msg void OnCbnSelchangeComboMunicipal();
    afx_msg void OnBnClickedButtonStart();
    BOOL IDNumberVerify(CString strIDNumber);
};
