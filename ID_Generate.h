#pragma once


// ID_Generate 对话框

class ID_Generate : public CDialog
{
	DECLARE_DYNAMIC(ID_Generate)

public:
	ID_Generate(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ID_Generate();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ID_CARD_NO_GENERATE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
