#pragma once


// ID_Generate �Ի���

class ID_Generate : public CDialog
{
	DECLARE_DYNAMIC(ID_Generate)

public:
	ID_Generate(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ID_Generate();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ID_CARD_NO_GENERATE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
