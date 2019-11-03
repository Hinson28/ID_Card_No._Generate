// ID_Generate.cpp : 实现文件
//

#include "stdafx.h"
#include "ID_Card_No_Generate.h"
#include "ID_Generate.h"
#include "afxdialogex.h"


// ID_Generate 对话框

IMPLEMENT_DYNAMIC(ID_Generate, CDialog)

ID_Generate::ID_Generate(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_ID_CARD_NO_GENERATE_DIALOG, pParent)
{

}

ID_Generate::~ID_Generate()
{
}

void ID_Generate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ID_Generate, CDialog)
END_MESSAGE_MAP()


// ID_Generate 消息处理程序
