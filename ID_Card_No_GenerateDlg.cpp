
// ID_Card_No_GenerateDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ID_Card_No_Generate.h"
#include "ID_Card_No_GenerateDlg.h"
#include "afxdialogex.h"
#include <locale>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CID_Card_No_GenerateDlg 对话框



CID_Card_No_GenerateDlg::CID_Card_No_GenerateDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ID_CARD_NO_GENERATE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CID_Card_No_GenerateDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_YEAR, m_comboYear);
    DDX_Control(pDX, IDC_COMBO_MONTH, m_comboMonth);
    DDX_Control(pDX, IDC_COMBO_DAY, m_comboDay);
    DDX_Control(pDX, IDC_COMBO_PROVINICAL, m_comboProvincial);
    DDX_Control(pDX, IDC_COMBO_MUNICIPAL, m_comboMunicipal);
    DDX_Control(pDX, IDC_COMBO_COUNTY, m_comboCounty);
    DDX_Control(pDX, IDC_COMBO_COUNT, m_comboCount);
    DDX_Control(pDX, IDC_COMBO_MALE, m_comboMale);
    DDX_Control(pDX, IDC_EDIT_ID_NUMBER, m_editIDNumber);
    DDX_Control(pDX, IDC_EDIT_ID_NUMBER_INPUT, m_editIDNumberInput);
    DDX_Control(pDX, IDC_EDIT_ID_INFO, m_editIDInfo);
}

BEGIN_MESSAGE_MAP(CID_Card_No_GenerateDlg, CDialogEx)
	ON_WM_PAINT()
    ON_WM_CLOSE()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BUTTON_GENERATE, &CID_Card_No_GenerateDlg::OnBnClickedButtonGenerate)
    ON_CBN_SELCHANGE(IDC_COMBO_PROVINICAL, &CID_Card_No_GenerateDlg::OnCbnSelchangeComboProvinical)
    ON_CBN_SELCHANGE(IDC_COMBO_MUNICIPAL, &CID_Card_No_GenerateDlg::OnCbnSelchangeComboMunicipal)
    ON_BN_CLICKED(IDC_BUTTON_START, &CID_Card_No_GenerateDlg::OnBnClickedButtonStart)
END_MESSAGE_MAP()


// CID_Card_No_GenerateDlg 消息处理程序

BOOL CID_Card_No_GenerateDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
    //获取程序运行目录
    TCHAR cszModulePath[_MAX_PATH];
    GetModuleFileName(NULL, cszModulePath, _MAX_PATH);
    m_strModulePath = cszModulePath;
    m_strModulePath = m_strModulePath.Left(m_strModulePath.ReverseFind(_T('\\')));
    m_strCacheFilePath = m_strModulePath + _T("\\Cache");
    LoadIDInfo();
    UpdateUI();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CID_Card_No_GenerateDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CID_Card_No_GenerateDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CID_Card_No_GenerateDlg::OnClose()
{
    if(PathFileExists(m_strCacheFilePath))
    {
        DeleteFile(m_strCacheFilePath);
    }
    CDialogEx::OnClose();
}

void CID_Card_No_GenerateDlg::UpdateUI()
{
    INT nAddrID = 0;
    CString strAddrInfo, strTemp, strYear, strMonth, strDay;

    //初始化地址、出生日期、性别以及数量
    for(INT i = 2020; i >= 1920; i--)
    {
        strTemp.Format(_T("%d"), i);
        m_comboYear.AddString(strTemp);
    }
    m_comboYear.SetCurSel(19);
    m_comboMonth.SetCurSel(0);
    for(INT i = 1; i<=31; i++)
    {
        strTemp.Format(_T("%d"), i);
        m_comboDay.AddString(strTemp);
    }
    m_comboDay.SetCurSel(0);
    m_comboMale.SetCurSel(0);
    m_comboCount.SetCurSel(0);

    POSITION pos = mapProvincial.GetStartPosition();
    while(pos)
    {
        mapProvincial.GetNextAssoc(pos, nAddrID, strAddrInfo);
        m_comboProvincial.AddString(strAddrInfo);
    }
    m_comboProvincial.SetCurSel(0);

    OnCbnSelchangeComboProvinical();
}

void CID_Card_No_GenerateDlg::LoadIDInfo()
{
    CStdioFile stdioFile;
    CString strText, strAddrInfo;
    CString strProvinical, strMunicipal, strCounty;
    INT nPos, nAddrID, nReadPos = 0;
    BOOL bFlag;
    HINSTANCE hInstance = AfxFindResourceHandle(MAKEINTRESOURCE(IDR_TXT), RT_RCDATA);
    HRSRC hRes = FindResource(hInstance, MAKEINTRESOURCE(IDR_TXT), _T("TXT"));
    HGLOBAL hResData = LoadResource(hInstance, hRes);
    void * lpvData = LockResource(hResData);
    int cbSize = SizeofResource(hInstance, hRes);

    CFile file(m_strCacheFilePath, CFile::modeCreate | CFile::modeWrite);
    file.SetLength(cbSize);
    file.SeekToBegin();
    file.Write(lpvData, cbSize);
    file.Close();

    SetFileAttributes(m_strCacheFilePath, FILE_ATTRIBUTE_HIDDEN);
    bFlag = stdioFile.Open(m_strCacheFilePath, CFile::modeRead);

    if(bFlag == FALSE)
    {
        AfxMessageBox(_T("文件打开失败"));
        return;
    }

    // 设定区域及语言，为了处理Unicode下中文乱码问题
    char* old_locale=_strdup(setlocale(LC_CTYPE, NULL));
    setlocale(LC_CTYPE, "chs");

    stdioFile.Seek(0, CFile::begin);

    while(stdioFile.ReadString(strText))
    {
        nReadPos++;
        nPos = strText.ReverseFind(' ');

        if(nPos != -1)
        {
            nAddrID= _wtoi(strText.Left(nPos));
            strAddrInfo = strText.Right(strText.GetLength() - nPos - 1);
            mapCountyAll.SetAt(nAddrID, strAddrInfo);
            
            if(nReadPos > 3520)
            {
                continue;
            }
            // 获取省级行政区信息
            if(nAddrID % 10000 == 0)
            {
                strProvinical = strAddrInfo;
                mapProvincial.SetAt(nAddrID, strProvinical);
                mapProvincialReverse.SetAt(strProvinical, nAddrID);
            }

            // 获取市级行政区信息
            else if(nAddrID % 100 == 0)
            {
                strAddrInfo.Replace(strProvinical, _T(""));
                strMunicipal = strAddrInfo;
                mapMunicipal.SetAt(nAddrID, strMunicipal);
                mapMunicipalReverse.SetAt(strMunicipal, nAddrID);
            }

            //获取县级行政区
            else
            {
                strAddrInfo.Replace(strProvinical, _T(""));
                strAddrInfo.Replace(strMunicipal, _T(""));
                mapCounty.SetAt(nAddrID, strAddrInfo);
                mapCountyReverse.SetAt(strAddrInfo, nAddrID);
            }
        }
    }

    //还原语言区域的设置、还原区域设定
    setlocale(LC_CTYPE, old_locale);
    free(old_locale);

    stdioFile.Close();
}
void CID_Card_No_GenerateDlg::OnBnClickedButtonGenerate()
{
    CString strIDNumber = _T(""), strTemp = _T("");
    CString strProvinical, strMunicipal, strCounty, strYear, strCheckSum;
    INT nProvinical, nMunicipal = 0, nCounty = 0, nSum = 0;
    INT nMale,nYear, nMonth, nDay, nCount, nAddrID, nMod;
    BYTE ucIDInfo[17] ={ NULL };
    BYTE  ucCoefficient[17] ={7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9,10, 5, 8, 4, 2};
    TCHAR cszMod[11] ={'1', '0', 'X', '9', '8', '7', '6', '5', '4', '3', '2'};

    SetDlgItemText(IDC_EDIT_ID_NUMBER, _T(""));

    GetDlgItemText(IDC_COMBO_PROVINICAL, strProvinical);
    mapProvincialReverse.Lookup(strProvinical, nProvinical);

    GetDlgItemText(IDC_COMBO_MUNICIPAL, strMunicipal);
    mapMunicipalReverse.Lookup(strMunicipal, nMunicipal);

    GetDlgItemText(IDC_COMBO_COUNTY, strCounty);
    mapCountyReverse.Lookup(strCounty, nCounty);
    
    // 判断是否是特别行政区
    if(nMunicipal == 0)
    {
        nAddrID = nProvinical;
    }
    //判断是否是直辖市
    else if(nCounty == 0)
    {
        nAddrID = nMunicipal;
    }
    // 判断是否是市辖区
    else if((nCounty / 100) != (nMunicipal / 100))
    {
        nAddrID = nMunicipal;
    }
    else
    {
        nAddrID = nCounty;
    }

    ucIDInfo[0] = nAddrID / 100000;
    ucIDInfo[1] = nAddrID / 10000 % 10;
    ucIDInfo[2] = nAddrID / 1000 % 10;
    ucIDInfo[3] = nAddrID / 100 % 10;
    ucIDInfo[4] = nAddrID / 10 % 10;
    ucIDInfo[5] = nAddrID % 10;

    GetDlgItemText(IDC_COMBO_YEAR, strYear);
    nYear = _wtoi(strYear);
    ucIDInfo[6] = nYear / 1000;
    ucIDInfo[7] = nYear / 100 % 10;
    ucIDInfo[8] = nYear / 10 % 10;
    ucIDInfo[9] = nYear % 10;

    nMonth = m_comboMonth.GetCurSel() + 1;
    ucIDInfo[10] = nMonth / 10;
    ucIDInfo[11] = nMonth % 10;

    nDay  = m_comboDay.GetCurSel() + 1;
    ucIDInfo[12] = nDay / 10;
    ucIDInfo[13] = nDay % 10;

    nMale = m_comboMale.GetCurSel() + 1;
    ucIDInfo[16] = nMale;

    nCount = m_comboCount.GetCurSel() + 1;
    for(BYTE x = 0; x < nCount; x++)
    {
        nSum = 0;
        ucIDInfo[14] = rand() % 10;
        ucIDInfo[15] = rand() % 10;
        for(BYTE i = 0; i < 17; i++)
        {
            nSum += ucCoefficient[i] * ucIDInfo[i];
            strTemp.Format(_T("%d"), ucIDInfo[i]);
            strIDNumber += strTemp;
        }
        nMod = nSum % 11;
        strCheckSum = cszMod[nMod];

        strIDNumber += strCheckSum;
        GetDlgItemText(IDC_EDIT_ID_NUMBER, strTemp);
        strIDNumber = strIDNumber + _T("\r\n");
        SetDlgItemText(IDC_EDIT_ID_NUMBER, strIDNumber);
    }
}


void CID_Card_No_GenerateDlg::OnCbnSelchangeComboProvinical()
{
    INT nAddrID, nProvinicalID;
    CString strPorvinical, strMunicipal;
    m_comboMunicipal.ResetContent();

    GetDlgItemText(IDC_COMBO_PROVINICAL, strPorvinical);

    mapProvincialReverse.Lookup(strPorvinical, nProvinicalID);
    
    //根据省级行政区，遍历市级行政区 
    for(INT i = 1; i < 30; i++)
    {
        nAddrID = nProvinicalID + 100 * i;
        if(mapMunicipal.Lookup(nAddrID, strMunicipal))
        {
            m_comboMunicipal.AddString(strMunicipal);
        }
    }

    // 判断是否是直辖市
    if(strPorvinical.Find(_T("市")) != -1)
    {
        for(INT i = 101; i < 130; i++)
        {
            nAddrID = nProvinicalID + i;
            if(mapCounty.Lookup(nAddrID, strPorvinical))
            {
                m_comboMunicipal.AddString(strPorvinical);
            }
        }
    }
    m_comboMunicipal.SetCurSel(0);

    OnCbnSelchangeComboMunicipal();
}


void CID_Card_No_GenerateDlg::OnCbnSelchangeComboMunicipal()
{
    CString strProvinical, strMunicipal;
    INT nProvinical = 0, nMunicipal, nAddrID;

    m_comboCounty.ResetContent();
    GetDlgItemText(IDC_COMBO_PROVINICAL, strProvinical);
    GetDlgItemText(IDC_COMBO_MUNICIPAL, strMunicipal);
    
    // 判断是否是直辖市
    if(strProvinical.Find(_T("市")) != -1)
    {
        return;
    }

    //根据市级行政区，遍历县级行政区
    mapProvincial.Lookup(nProvinical, strProvinical);
    mapMunicipalReverse.Lookup(strMunicipal, nMunicipal);  
    for(INT i = 1; i < 30; i++)
    {
        nAddrID = nMunicipal + i;
        if(mapCounty.Lookup(nAddrID, strMunicipal))
        {
            m_comboCounty.AddString(strMunicipal);
        }
    }
    m_comboCounty.SetCurSel(0);
}


void CID_Card_No_GenerateDlg::OnBnClickedButtonStart()
{
    CString strIDNumber = _T(""), strIDNumberInfo, strTemp;
    CString strAddrInfo = _T(""), strYear, strMonth, strDay, strMale, strAge;
    INT nAddrID, nMale, nAge;
    BOOL nValid;
    CTime time;
    GetDlgItemText(IDC_EDIT_ID_NUMBER_INPUT, strIDNumber);


    time = CTime::GetCurrentTime();
    strAge = time.Format(_T("%Y"));

    nValid = IDNumberVerify(strIDNumber);
    if(!nValid)
    {
        return;
    }
    nAddrID = _wtoi(strIDNumber.Left(6));
    mapCountyAll.Lookup(nAddrID, strAddrInfo);

    strYear = strIDNumber.Mid(6, 4);
    nAge = _wtoi(strAge) - _wtoi(strYear);

    strMonth = strIDNumber.Mid(10, 2);
    strDay = strIDNumber.Mid(12, 2);
    nMale = _wtoi(strIDNumber.Mid(16, 1));
    strMale = nMale % 2 ? _T("男") : _T("女");
    strIDNumberInfo.Format(_T("%s, %d岁, %s, %s年%s月%s日"), strAddrInfo, nAge, strMale, strYear, strMonth, strDay);
    SetDlgItemText(IDC_EDIT_ID_INFO, strIDNumberInfo);
}

BOOL CID_Card_No_GenerateDlg::IDNumberVerify(CString strIDNumber)
{
    CString strIDNumberInfo, strTemp = _T("");
    CString strAddrInfo = _T(""), strYear, strMonth, strDay, strMale, strCheckSum;
    INT nAddrID, nMonth, nDay, nSum = 0, nMod;
    BYTE ucIDInfo[17] ={ NULL };
    BYTE  ucCoefficient[17] ={7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9,10, 5, 8, 4, 2};
    TCHAR cszMod[11] ={'1', '0', 'X', '9', '8', '7', '6', '5', '4', '3', '2'};

    for(INT i = 0; i< 17; i++)
    {
        ucIDInfo[i] = _wtoi(strIDNumber.Mid(i, 1));
    }
    // 判断号码长度是否符合要求
    if(strIDNumber.GetLength() != 18)
    {
        SetDlgItemText(IDC_EDIT_ID_INFO, _T("请输入18位有效身份证号"));
        return FALSE;
    }

    //判断地址码是否存在
    nAddrID = _wtoi(strIDNumber.Left(6));
    mapCountyAll.Lookup(nAddrID, strAddrInfo);
    if(strAddrInfo == _T(""))
    {
        SetDlgItemText(IDC_EDIT_ID_INFO, _T("无法查询到地址信息,请输入有效身份证号"));
        return FALSE;
    }
    
    //判断出生日期是否正常
    nMonth = _wtoi(strIDNumber.Mid(10, 2));
    nDay = _wtoi(strIDNumber.Mid(12, 2));
    if((nMonth > 12) || (nDay>31))
    {
        SetDlgItemText(IDC_EDIT_ID_INFO, _T("无效的出生日期, 请输入有效身份证号"));
        return FALSE;
    }

    //判断校验码是否符合要求
    for(BYTE i = 0; i < 17; i++)
    {
        nSum += ucCoefficient[i] * ucIDInfo[i];
        strTemp.Format(_T("%d"), ucIDInfo[i]);
    }
    nMod = nSum % 11;
    strCheckSum = cszMod[nMod];
    if(strCheckSum != strIDNumber.Right(1))
    {
        SetDlgItemText(IDC_EDIT_ID_INFO, _T("校验码错误，请输入有效身份证号"));
        return FALSE;
    }
    return TRUE;
}