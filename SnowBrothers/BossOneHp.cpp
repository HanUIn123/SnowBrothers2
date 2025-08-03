#include "pch.h"
#include "BossOneHp.h"
#include "BmpManager.h"
#include "ObjectManager.h"
#include "BossOne.h"

CBossOneHp::CBossOneHp()
{
    m_vecHDC.clear();
}

CBossOneHp::~CBossOneHp()
{
    Release();
}

void CBossOneHp::Initialize()
{
    m_vecHDC.assign(10, nullptr);

    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Boss/BossHpBarBack.bmp", L"BossHpBack");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Boss/BossHpBarFront.bmp", L"BossHpFront");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Boss/SlotBoss_Image.bmp", L"SlotBoss_Image");

    m_vecHDC[0] = CBmpManager::Get_Instance()->Find_Img(L"BossHpBack");
    m_vecHDC[1] = CBmpManager::Get_Instance()->Find_Img(L"BossHpFront");

    m_tInfo = { 230.0f , 50.0f, 458.0f, 29.0f };
}

int CBossOneHp::Update()
{
    Decrease_Hp();

    return 0;
}

void CBossOneHp::Late_Update()
{
}

void CBossOneHp::Render(HDC _hDC)
{
    m_vecHDC[0] = CBmpManager::Get_Instance()->Find_Img(L"BossHpBack");
    m_vecHDC[1] = CBmpManager::Get_Instance()->Find_Img(L"BossHpFront");

    HDC hBossTwoFaceDC = CBmpManager::Get_Instance()->Find_Img(L"SlotBoss_Image");

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

void CBossOneHp::Release()
{
}

void CBossOneHp::Decrease_Hp()
{
    CObject* pBossOneClass = CObjectManager::Get_Instance()->Get_ObjectList(OBJECT_LIST::BOSS).front();
    CBossOne* pTempBossOneClass = dynamic_cast<CBossOne*>(pBossOneClass);

    float fHPRatio = pTempBossOneClass->Get_CurrentBossOneHp() / pTempBossOneClass->Get_MaxBossOneHp() * 458.0f;

    if (fHPRatio >= 0)
    {
        m_tInfo.fCX = fHPRatio;
        m_tInfo.fX = fHPRatio * 0.5f + 200.0f;
    }
}
