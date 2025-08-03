#include "pch.h"
#include "Bullet.h"
#include "BmpManager.h"

CBullet::CBullet() :
    m_iDirection((UINT)OBJECT_DIRECTION::DIR_END),
    m_dwStartFallingTime(GetTickCount64()),
    m_dwExistTime(GetTickCount64())
{
}

CBullet::~CBullet()
{
    Release();
}

void CBullet::Initialize()
{
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Projectile/basic_shot_right.bmp", L"Basic_Bullet_right");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Projectile/basic_shot_left.bmp", L"Basic_Bullet_left");

    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Projectile/Power_shot_right.bmp", L"Power_Bullet_right");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Projectile/Power_shot_left.bmp", L"Power_Bullet_left");

    m_fSpeed = 7.f;
}

int CBullet::Update()
{
    if (m_dwExistTime + 1000 < GetTickCount64())
    {
        m_dwExistTime = GetTickCount64();
        return (UINT)OBJECT_STATE::OBJ_DEAD;
    }
    else if (m_bDead)
        return (UINT)OBJECT_STATE::OBJ_DEAD;

    switch (m_eDir)
    {
    case OBJECT_DIRECTION::DIR_LEFT:

        m_tInfo.fX += float(cos(m_fAngle * (PI / 180.0f))) * -m_fSpeed;
        m_tInfo.fY -= float(sin(m_fAngle * (PI / 180.0f))) * -m_fSpeed;

        if (m_dwStartFallingTime + 400 < GetTickCount64())
        {
            m_fAngle = 90.0f;
            m_fSpeed = 2.0f;

            m_dwStartFallingTime = GetTickCount64();
        }

        break;

    case OBJECT_DIRECTION::DIR_RIGHT:

        m_tInfo.fX += float(cos(m_fAngle * (PI / 180.0f))) * m_fSpeed;
        m_tInfo.fY -= float(sin(m_fAngle * (PI / 180.0f))) * m_fSpeed;

        if (m_dwStartFallingTime + 400 < GetTickCount64())
        {
            m_fAngle = -90.0f;
            m_fSpeed = 2.0f;

            m_dwStartFallingTime = GetTickCount64();
        }

        break;
    }

    return (UINT)OBJECT_STATE::OBJ_NOEVENT;
}

void CBullet::Late_Update()
{
    __super::Update_Rect();
}

void CBullet::Render(HDC _hDC)
{
    HDC	hMemDC = CBmpManager::Get_Instance()->Find_Img(L"Basic_Bullet_right");
    HDC	hMemDC2 = CBmpManager::Get_Instance()->Find_Img(L"Basic_Bullet_left");
    HDC	hMemDC3 = CBmpManager::Get_Instance()->Find_Img(L"Power_Bullet_right");
    HDC	hMemDC4 = CBmpManager::Get_Instance()->Find_Img(L"Power_Bullet_left");

    // Rectangle(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

    if ((UINT)m_eDir == (UINT)OBJECT_DIRECTION::DIR_RIGHT)
    {
        if (!m_bIsBulletUpgraded)
        {
            GdiTransparentBlt(_hDC,
                int(m_tRect.left),
                int(m_tRect.top),
                int(32),
                int(64),
                hMemDC,
                0, 0,
                int(32),
                int(64),
                RGB(255, 0, 255));
        }
        else
        {
            GdiTransparentBlt(_hDC,
                int(m_tRect.left),
                int(m_tRect.top),
                int(64),
                int(64),
                hMemDC3,
                0, 0,
                int(64),
                int(64),
                RGB(255, 0, 255));
        }
    }

    if ((UINT)m_eDir == (UINT)OBJECT_DIRECTION::DIR_LEFT)
    {
        if (!m_bIsBulletUpgraded)
        {
            GdiTransparentBlt(_hDC,
                int(m_tRect.left),
                int(m_tRect.top),
                int(32),
                int(64),
                hMemDC2,
                0, 0,
                int(32),
                int(64),
                RGB(255, 0, 255));
        }
        else
        {
            GdiTransparentBlt(_hDC,
                int(m_tRect.left),
                int(m_tRect.top),
                int(64),
                int(64),
                hMemDC4,
                0, 0,
                int(64),
                int(64),
                RGB(255, 0, 255));
        }
    }
}

void CBullet::Release()
{
}
