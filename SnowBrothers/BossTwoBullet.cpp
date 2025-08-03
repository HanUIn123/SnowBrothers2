#include "pch.h"
#include "BossTwoBullet.h"
#include "BmpManager.h"
#include "PlayerManager.h"

CBossTwoBullet::CBossTwoBullet() :
    m_iDirection((UINT)OBJECT_DIRECTION::DIR_END),
    m_eBulletCurState(BULLET_STATE::IDLE),
    m_eBulletPreState(BULLET_STATE::END),
    m_bFirstCreate(false),
    m_bIsUnder(false),
    m_fPlayerPosY(0.0f)
{
    m_dwBossMissileExistingTime = GetTickCount64();
    m_dwBulletExistingTimeWithNose = GetTickCount64();
}

CBossTwoBullet::~CBossTwoBullet()
{
    Release();
}

void CBossTwoBullet::Initialize()
{
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Projectile/BossTwoMissile.bmp", L"BossTwoMissile");
    
    m_fSpeed = 10.0f;

    m_tInfo = { 610, WINCY / 2.0f, 128.0f,108.0f };

    m_pFrameKey = L"BossTwoMissile";

    m_tFrame = { 0,1,0,100,GetTickCount64() };

    m_bFirstCreate = true;

    m_fPlayerPosY = CPlayerManager::Get_Instance()->Get_PlayerPosY();

    if (m_tInfo.fY > m_fPlayerPosY)
    {
        m_bIsUnder = true;
    }
    else
    {
        m_bIsUnder = false;
    }
}

int CBossTwoBullet::Update()
{
    if (m_dwBossMissileExistingTime + 4000 < GetTickCount64())
    {
        m_dwBossMissileExistingTime = GetTickCount64();
        return (UINT)OBJECT_STATE::OBJ_DEAD;
    }
    else if (m_bDead)
        return (UINT)OBJECT_STATE::OBJ_DEAD;


    if (m_bFirstCreate)
    {
        if (m_bIsUnder)
        {
            if (m_tInfo.fY >= m_fPlayerPosY)
                    m_tInfo.fY -= 3.0f;
        }
        else
        {
            if (m_tInfo.fY <= m_fPlayerPosY)
                    m_tInfo.fY += 3.0f;
        }

        if (m_dwBulletExistingTimeWithNose + 1500 < GetTickCount64())
        {
            m_bFirstCreate = false;
        }
    }


    if (!m_bFirstCreate)
    {
        if (m_eDir == OBJECT_DIRECTION::DIR_LEFT)
        {
            m_tInfo.fX += float(cos(m_fAngle * (PI / 180.0f))) * -m_fSpeed;
            m_tInfo.fY -= float(sin(m_fAngle * (PI / 180.0f))) * -m_fSpeed;
        }
    }


    return (UINT)OBJECT_STATE::OBJ_NOEVENT;
}

void CBossTwoBullet::Late_Update()
{
    __super::Update_Rect();

    BulletAnimation();

    BulletMoveFrame();
}

void CBossTwoBullet::Render(HDC _hDC)
{
    HDC	hMemDC = CBmpManager::Get_Instance()->Find_Img(L"BossTwoMissile");

    //Rectangle(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

    GdiTransparentBlt(_hDC,
        int(m_tRect.left),
        int(m_tRect.top),
        int(128),
        int(108.0f),
        hMemDC,
        int(m_tInfo.fCX * m_tFrame.iStart),
        int(m_tInfo.fCY * m_tFrame.iMotion),
        int(128),
        int(108.0f),
        RGB(255, 0, 255));
}

void CBossTwoBullet::Release()
{
}

void CBossTwoBullet::BulletAnimation()
{
    if (m_eBulletPreState != m_eBulletCurState)
    {
        switch (m_eBulletCurState)
        {
        case BULLET_STATE::IDLE:
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 1;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 60;
            m_tFrame.dwTime = GetTickCount64();
            break;
        }
        m_eBulletPreState = m_eBulletCurState;
    }
}

void CBossTwoBullet::BulletMoveFrame()
{
    if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount64())
    {
        ++m_tFrame.iStart;

        if (m_tFrame.iStart > m_tFrame.iEnd)
            m_tFrame.iStart = 0;

        m_tFrame.dwTime = GetTickCount64();
    }
}
