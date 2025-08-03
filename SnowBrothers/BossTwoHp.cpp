#include "pch.h"
#include "BossTwoHp.h"
#include "BmpManager.h"
#include "ObjectManager.h"
#include "BossTwo.h"

CBossTwoHp::CBossTwoHp()
{
    m_vecHDC.clear();
}

CBossTwoHp::~CBossTwoHp()
{
    Release();
}

void CBossTwoHp::Initialize()
{
    m_vecHDC.assign(10, nullptr);

    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Boss/BossHpBarBack.bmp", L"BossHpBack");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Boss/BossHpBarFront.bmp", L"BossHpFront");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Boss/TrainBoss_Image.bmp", L"BossTwoFace");

    m_vecHDC[0] = CBmpManager::Get_Instance()->Find_Img(L"BossHpBack");
    m_vecHDC[1] = CBmpManager::Get_Instance()->Find_Img(L"BossHpFront");
    
    m_tInfo = { 230.0f , 50.0f, 458.0f, 29.0f };
}

int CBossTwoHp::Update()
{
    Decrease_Hp();

    return 0;
}

void CBossTwoHp::Late_Update()
{
}

void CBossTwoHp::Render(HDC _hDC)
{
    m_vecHDC[0] = CBmpManager::Get_Instance()->Find_Img(L"BossHpBack");
    m_vecHDC[1] = CBmpManager::Get_Instance()->Find_Img(L"BossHpFront");

    HDC hBossTwoFaceDC = CBmpManager::Get_Instance()->Find_Img(L"BossTwoFace");

    GdiTransparentBlt
    (
        _hDC,
        int(230),
        int(50),
        int(100.0f),
        int(100.0f),
        hBossTwoFaceDC,
        0, 0,
        int(100.0f),
        int(100.0f),
        RGB(255, 0, 255)
    );


    GdiTransparentBlt
    (
        _hDC,
        int(330),
        int(80),
        int(458.0f),
        int(29.0f),
        m_vecHDC[0],
        0, 0,
        int(458.0f),
        int(29.0f),
        RGB(255, 255, 255)
    );

    //GdiTransparentBlt
    //(
    //    _hDC,
    //    //int(330),
    //    //int(80),
    //    int(m_tInfo.fX - (m_tInfo.fCX * 0.5f)),
    //    int(m_tInfo.fY - (m_tInfo.fCY * 0.5f)),
    //    int(m_tInfo.fCX),
    //    int(m_tInfo.fCY),
    //    m_vecHDC[1],
    //    0, 0,
    //    int(m_tInfo.fCX),
    //    int(m_tInfo.fCY),
    //    RGB(255, 255, 255)
    //);

    GdiTransparentBlt
    (
        _hDC,
        int(330),
        int(80),
        int(m_tInfo.fCX),
        int(m_tInfo.fCY),
        m_vecHDC[1],
        0, 0,
        int(m_tInfo.fCX),
        int(m_tInfo.fCY),
        RGB(255, 255, 255)
    );
}

void CBossTwoHp::Release()
{
}

void CBossTwoHp::Decrease_Hp()
{
    CObject* pBossTwoClass = CObjectManager::Get_Instance()->Get_ObjectList(OBJECT_LIST::BOSS).front();
    CBossTwo* pTempBossTwoClass = dynamic_cast<CBossTwo*>(pBossTwoClass);

    float fHPRatio = pTempBossTwoClass->Get_CurrentBossTwoHp() / pTempBossTwoClass->Get_MaxBossTwoHp() * 458.0f;

    if (fHPRatio >= 0) 
    {
        m_tInfo.fCX = fHPRatio;
        m_tInfo.fX = fHPRatio * 0.5f + 200.0f;
    }
}
