#include "pch.h"
#include "Life.h"
#include "BmpManager.h"
#include "Player.h"
#include "ObjectManager.h"

CLife::CLife() :
    m_iHuns_Digit(0),
    m_iTens_Digit(0),
    m_iOne_Digit(0)
{
    m_vecHDC.clear();
    m_vecHDC2.clear();
}

CLife::~CLife()
{
    Release();
}

void CLife::Initialize()
{
    m_vecHDC.assign(7, nullptr);
    m_vecHDC2.assign(11, nullptr);

    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Score_UI/Profile_UI.bmp", L"Profile");

    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Score_UI/00.bmp", L"zero");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Score_UI/11.bmp", L"11");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Score_UI/22.bmp", L"22");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Score_UI/33.bmp", L"33");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Score_UI/44.bmp", L"44");

    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Score_UI/000.bmp", L"zero2");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Score_UI/111.bmp", L"111");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Score_UI/222.bmp", L"222");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Score_UI/333.bmp", L"333");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Score_UI/444.bmp", L"444");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Score_UI/555.bmp", L"555");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Score_UI/666.bmp", L"666");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Score_UI/777.bmp", L"777");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Score_UI/888.bmp", L"888");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Score_UI/999.bmp", L"999");

    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Score_UI/Player1.bmp", L"PlayerOne");

    m_tInfo = { 50.0f,0.0f,64.0f,64.0f };

    m_vecHDC[0] = CBmpManager::Get_Instance()->Find_Img(L"zero");

    for (int i = 1; i < 5; ++i)
    {
        TCHAR m_strName[3] = L"";

        swprintf_s(m_strName, L"%d", (i * 11));

        m_vecHDC[i] = CBmpManager::Get_Instance()->Find_Img(m_strName);
    }


    m_vecHDC2[0] = CBmpManager::Get_Instance()->Find_Img(L"zero2");

    for (int i = 1; i < 10; ++i)
    {
        TCHAR m_strName[10] = L"";

        swprintf_s(m_strName, L"%d", (i * 111));

        m_vecHDC2[i] = CBmpManager::Get_Instance()->Find_Img(m_strName);
    }
}

int CLife::Update()
{
    CObject* pTempPlayerClass = CObjectManager::Get_Instance()->Get_ObjectList(OBJECT_LIST::PLAYER).front();
    CPlayer* pPlayerClass = dynamic_cast<CPlayer*>(pTempPlayerClass);

    // 백의자리
    m_iHuns_Digit = pPlayerClass->Get_Count() / 100;
    // 십의 자리 
    m_iTens_Digit = pPlayerClass->Get_Count() / 10;

    if (m_iTens_Digit >= 10)
    {
        m_iTens_Digit = m_iTens_Digit % 10;
    }

    // 일의자리
    m_iOne_Digit = pPlayerClass->Get_Count() % 10;

    return 0;
}   

void CLife::Late_Update()
{

}

void CLife::Render(HDC _hDC)
{
    CObject* pTempPlayerClass = CObjectManager::Get_Instance()->Get_ObjectList(OBJECT_LIST::PLAYER).front();
    CPlayer* pPlayerClass = dynamic_cast<CPlayer*>(pTempPlayerClass);

    HDC hMemDC = CBmpManager::Get_Instance()->Find_Img(L"Profile");
    HDC hMemDC2 = CBmpManager::Get_Instance()->Find_Img(L"PlayerOne");

    GdiTransparentBlt
    (
        _hDC,
        int(0),
        int(0),
        int(64),
        int(64),
        hMemDC,
        0, 0,
        int(64),
        int(64),
        RGB(255, 0, 255)
    );

    for (int i = 0; i < pPlayerClass->Get_Life(); ++i)
    {
        GdiTransparentBlt
        (
            _hDC,
            int(m_tRect.left + 70),
            int(m_tRect.top),
            int(64),
            int(64),
            //m_vecHDC[i],
            m_vecHDC[pPlayerClass->Get_Life() - 1],
            0, 0,
            int(64),
            int(64),
            RGB(255, 0, 255)
        );
    }


    GdiTransparentBlt
    (
        _hDC,
        int(m_tRect.left + 140),
        int(m_tRect.top + 20),
        int(113),
        int(32),
        hMemDC2,
        0, 0,
        int(113),
        int(32),
        RGB(255, 0, 255)
    );


    GdiTransparentBlt
    (
        _hDC,
        int(m_tRect.left + 210),
        int(m_tRect.top + 70),
        int(23),
        int(32),
        m_vecHDC2[m_iOne_Digit],
        0, 0,
        int(23),
        int(32),
        RGB(255, 0, 255)
    );


    GdiTransparentBlt
    (
        _hDC,
        int((m_tRect.left + 210) - 26),
        int(m_tRect.top + 70),
        int(23),
        int(32),
        m_vecHDC2[m_iTens_Digit],
        0, 0,
        int(23),
        int(32),
        RGB(255, 0, 255)
    );



    GdiTransparentBlt
    (
        _hDC,
        int(m_tRect.left + 210 - 52),
        int(m_tRect.top + 70),
        int(23),
        int(32),
        m_vecHDC2[m_iHuns_Digit],
        0, 0,
        int(23),
        int(32),
        RGB(255, 0, 255)
    );


}

void CLife::Release()
{
}

void CLife::Lose_LifeCount()
{
}
