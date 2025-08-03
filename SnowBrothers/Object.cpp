#include "pch.h"
#include "Object.h"

CObject::CObject() :
    m_bDead(false),
    m_bLookingRight(true),
    m_bCanKick(false),
    m_bRealPush(false),
    m_fSpeed(0.0f),
    m_fAngle(0.0f),
    m_fDistance(0.0f),
    m_fGravity(0.0f)
    , m_fJumpSpeed(0.f)
    , m_fJumpAccel(0.f)
    , m_fJumpTime(0.f)
    , m_fAccel(0.0f)
    , m_eDir(OBJECT_DIRECTION::DIR_END),
    m_pTarget(nullptr),
    m_pCollisionName(nullptr),
    m_pCollisionSnowName(nullptr),
    m_fSnowBallSpeed(0.0f),
    m_pFrameKey(nullptr),
    m_pSnowFrameKey(nullptr),
    m_bIsBulletRanged(false),
    m_bIsBulletUpgraded(false),
    m_dwFameControllTime(GetTickCount64())
{
    ZeroMemory(&m_tInfo, sizeof(m_tInfo));
    ZeroMemory(&m_tRect, sizeof(RECT));
    ZeroMemory(&m_tFrame, sizeof(FRAME));
    ZeroMemory(&m_tSnowFrame, sizeof(FRAME));

}

CObject::~CObject()
{
}

void CObject::Update_Rect()
{
    m_tRect.left = LONG(m_tInfo.fX - (m_tInfo.fCX / 2.0f));
    m_tRect.top = LONG(m_tInfo.fY - (m_tInfo.fCY / 2.0f));
    m_tRect.right = LONG(m_tInfo.fX + (m_tInfo.fCX / 2.0f));
    m_tRect.bottom = LONG(m_tInfo.fY + (m_tInfo.fCY / 2.0f));
}

void CObject::Move_Frame()
{
    if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount64())
    {
        ++m_tFrame.iStart;

        if (m_tFrame.iStart > m_tFrame.iEnd)
            m_tFrame.iStart = 0;

        m_tFrame.dwTime = GetTickCount64();
    }
}
