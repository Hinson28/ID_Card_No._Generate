
// ID_Card_No_Generate.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CID_Card_No_GenerateApp: 
// �йش����ʵ�֣������ ID_Card_No_Generate.cpp
//

class CID_Card_No_GenerateApp : public CWinApp
{
public:
	CID_Card_No_GenerateApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CID_Card_No_GenerateApp theApp;