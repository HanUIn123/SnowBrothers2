#include "pch.h"
#include "MonsterTwoBullet.h"
#include "BmpManager.h"

CMonsterTwoBullet::CMonsterTwoBullet() :
    m_iDirection((UINT)OBJECT_DIRECTION::DIR_END),
    m_eMonsterBulletCurState(BULLET_STATE::IDLE),
    m_eMonsterBulletPreState(BULLET_STATE::END),
    m_bFirstCreate(false),
    m_fPlayerPosY(0.0f)
{
    m_dwMonsterMissileExistingTime = GetTickCount64();
}

CMonsterTwoBullet::~CMonsterTwoBullet()
{
    Release();
}

void CMonsterTwoBullet::Initialize()
{
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Projectile/Monster_Two_Bullet_Right.bmp", L"Monster_Two_Bullet_Right");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Projectile/Monster_Two_Bullet_Left.bmp", L"Monster_Two_Bullet_Left");

    m_fSpeed = 10.0f;

    m_tInfo = { 610, WINCY / 2.0f, 81.0f,60.0f };

    m_pFrameKey = L"Monster_Two_Bullet_Right";

    m_tFrame = { 0,2,0,100,GetTickCount64() };
}

int CMonsterTwoBullet::Update()
{
    if (m_dwMonsterMissileExistingTime + 4000 < GetTickCount64())
    {
        m_dwMonsterMissileExistingTime = GetTickCount64();
        return (UINT)OBJECT_STATE::OBJ_DEAD;
    }
    else if (m_bDead)
        return (UINT)OBJECT_STATE::OBJ_DEAD;

    if (m_eDir == OBJECT_DIRECTION::DIR_LEFT)
    {
        m_pFrameKey = L"Monster_Two_Bullet_Left";
        m_tInfo.fX += float(cos(m_fAngle * (PI / 180.0f))) * -m_fSpeed;
        m_tInfo.fY -= float(sin(m_fAngle * (PI / 180.0f))) * -m_fSpeed;
    }
    else
    {
        m_pFrameKey = L"Monster_Two_Bullet_Right";
        m_tInfo.fX += float(cos(m_fAngle * (PI / 180.0f))) * m_fSpeed;
        m_tInfo.fY -= float(sin(m_fAngle * (PI / 180.0f))) * m_fSpeed;
    }

    return (UINT)OBJECT_STATE::OBJ_NOEVENT;
}

void CMonsterTwoBullet::Late_Update()
{
    __super::Update_Rect();

    Monster_BulletAnimation();

    Monster_BulletMoveFrame();
}

void CMonsterTwoBullet::Render(HDC _hDC)
{
    HDC	hMemDC = CBmpManager::Get_Instance()->Find_Img(m_pFrameKey);

    GdiTransparentBlt(_hDC,
        int(m_tRect.left),
        int(m_tRect.top),
        int(81),
        int(60),
        hMemDC,
        int(m_tInfo.fCX * m_tFrame.iStart),
        int(m_tInfo.fCY * m_tFrame.iMotion),
        int(81),
        int(60),
        RGB(255, 0, 255));
}

void CMonsterTwoBullet::Release()
{
}

void CMonsterTwoBullet::Monster_BulletAnimation()
{
    if (m_eMonsterBulletPreState != m_eMonsterBulletCurState)
    {
        switch (m_eMonsterBulletCurState)
        {
        case BULLET_STATE::IDLE:
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 2;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 60;
            m_tFrame.dwTime = GetTickCount64();
            break;
        }
        m_eMonsterBulletPreState = m_eMonsterBulletCurState;
    }
}

void CMonsterTwoBullet::Monster_BulletMoveFrame()
{
    if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount64())
    {
        ++m_tFrame.iStart;

        if (m_tFrame.iStart > m_tFrame.iEnd)
            m_tFrame.iStart = 0;

        m_tFrame.dwTime = GetTickCount64();
    }
}
