#include "pch.h"
#include "MonsterTwo.h"
#include "BmpManager.h"
#include "MonsterTwoBullet.h"
#include "ObjectManager.h"

#include "AbstractFactory.h"
#include "SpeedItem.h"
#include "PowerItem.h"
#include "RangeItem.h"
#include "PointItem.h"

CMonsterTwo::CMonsterTwo() :
    m_eMTCurState(MONSTERTWO_STATE::IDLE),
    m_eMTPreState(MONSTERTWO_STATE::END),
    m_bShoot(false),
    m_bItemCalled(false)
{
    m_pCollisionName = L"ENEMYONE";

    m_vecHDC.clear();

    m_dwIdleTime = GetTickCount64();

    m_dwDieCoolTime = GetTickCount64();

    m_dwShootTime = GetTickCount64();

    m_dwBulletCoolTime = GetTickCount64();

    m_dwJumpTime = GetTickCount64();
}

CMonsterTwo::~CMonsterTwo()
{
    Release();
}

void CMonsterTwo::Initialize()
{
    m_vecHDC.assign(10, nullptr);

    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Snow/0.bmp", L"0");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Snow/1.bmp", L"1");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Snow/2.bmp", L"2");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Snow/3.bmp", L"3");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Snow/4.bmp", L"4");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Snow/5.bmp", L"5");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Snow/6.bmp", L"6");

    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Snow/Rolling_Snow.bmp", L"Rolling_Snow2");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Snow/Player_With_Snow.bmp", L"Player_With_Snow");

    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Monster/mons3_idle.bmp", L"mons3_idle");

    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Monster/mons3_left_walk.bmp", L"mons3_left_walk");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Monster/mons3_right_walk.bmp", L"mons3_right_walk");

    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Monster/mons3_shoot_left2.bmp", L"mons3_shoot_left");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Monster/mons3_shoot_right2.bmp", L"mons3_shoot_right");

    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Monster/Minion_Die2.bmp", L"Minion_Die");

    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Snow/Rolling_Snow2.bmp", L"Rolling_Snow3");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Snow/Player_With_Snow.bmp", L"Player_With_Snow");

    m_tInfo = { 100.0f, 0.0f, 64.0f, 64.0f };

    m_fSpeed = 1.7f;

    m_pFrameKey = L"mons3_idle";

    // Monster Snow State
    for (int i = 0; i < 7; ++i)
    {
        TCHAR m_strName[7] = L"";

        swprintf_s(m_strName, L"%d", i);

        m_vecHDC[i] = CBmpManager::Get_Instance()->Find_Img(m_strName);
    }

    m_pSnowFrameKey = L"Rolling_Snow3";
    m_tSnowFrame = { 0,3,0,10,GetTickCount64() };
}

int CMonsterTwo::Update()
{
    if (m_bDead)
        return (UINT)OBJECT_STATE::OBJ_DEAD;

    if (m_bReadyToDie == false)
    {
        m_tInfo.fY += 6.0f;
    }
    else
    {
        m_tInfo.fY -= 5.0f;
    }

    if (m_bSnowBallMove)
    {
        if ((UINT)m_eDir == (UINT)OBJECT_DIRECTION::DIR_RIGHT)
        {
            m_tInfo.fX += m_fSnowBallSpeed;
        }
        else if ((UINT)m_eDir == (UINT)OBJECT_DIRECTION::DIR_LEFT)
        {
            m_tInfo.fX -= m_fSnowBallSpeed;
        }
    }

    return (UINT)OBJECT_STATE::OBJ_NOEVENT;
}

void CMonsterTwo::Late_Update()
{
    __super::Update_Rect();

    if (m_iMaxSnowStat >= 6)
    {
        m_pCollisionName = L"ENEMYONESNOW";
    }

    Set_TobeRoll();

    SnowBall_Roll();

    Monster_Snow_Ani();

    MT_Animation();

    if (m_tInfo.fX > WINCX - 70)
        m_eMonsterDirection = OBJECT_DIRECTION::DIR_LEFT;
    if (m_tInfo.fX < 70)
        m_eMonsterDirection = OBJECT_DIRECTION::DIR_RIGHT;

    if ((m_tInfo.fX < WINCX - 10 && m_tInfo.fX > 10))
    {
        MT_FSM();
    }
    else
    {
        if (m_tInfo.fX > 10)
            m_tInfo.fX = WINCX - 10.1f;
        else if (m_tInfo.fX < WINCX - 10)
            m_tInfo.fX = 10.1f;
    }

    if (m_bWithPlayer)
    {
        m_pSnowFrameKey = L"Player_With_Snow";
    }
    else
    {
        m_pSnowFrameKey = L"Rolling_Snow3";
    }

    MT_Move_Frame();
    CMonster::Snow_Move_Frame();
}

void CMonsterTwo::Render(HDC _hDC)
{
    HDC	hMonsterTwoDC = CBmpManager::Get_Instance()->Find_Img(m_pFrameKey);
    HDC hSnowRoll3DC = CBmpManager::Get_Instance()->Find_Img(m_pSnowFrameKey);

    if (!m_bSnowBallMove)
    {
        GdiTransparentBlt
        (
            _hDC,
            int(m_tRect.left),
            int(m_tRect.top),
            int(64),
            int(64),
            hMonsterTwoDC,
            int(m_tInfo.fCX * m_tFrame.iStart),
            int(m_tInfo.fCY * m_tFrame.iMotion),
            int(64),
            int(64),
            RGB(255, 0, 255)
        );
    }

    if (m_bHited && !m_bSnowBallMove && !m_bReadyToDie)
    {
        GdiTransparentBlt
        (
            _hDC,
            int(m_tRect.left),
            int(m_tRect.top),
            int(64),
            int(64),
            m_vecHDC[m_iMaxSnowStat],
            0, 0,
            int(64),
            int(64),
            RGB(255, 0, 255)
        );
    }

    if (m_bSnowBallMove)
    {
        GdiTransparentBlt
        (
            _hDC,
            int(m_tRect.left),
            int(m_tRect.top),
            int(64),
            int(64),
            hSnowRoll3DC,
            int(m_tInfo.fCX * m_tSnowFrame.iStart),
            int(m_tInfo.fCY * m_tSnowFrame.iMotion),
            int(64),
            int(64),
            RGB(255, 0, 255)
        );
    }
}

void CMonsterTwo::Release()
{
}

void CMonsterTwo::MT_Animation()
{
    // enum class MONSTERMINION_STATE { IDLE, WALK, SHOOT, CHANGE, DEAD, END};
    if (m_eMTPreState != m_eMTCurState)
    {
        switch (m_eMTCurState)
        {
        case MONSTERTWO_STATE::IDLE:
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 0;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 200;
            m_tFrame.dwTime = GetTickCount64();
            break;
        case MONSTERTWO_STATE::WALK:
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 3;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 200;
            m_tFrame.dwTime = GetTickCount64();
            break;
        case MONSTERTWO_STATE::JUMP:
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 3;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 200;
            m_tFrame.dwTime = GetTickCount64();
            break;
        case MONSTERTWO_STATE::SHOOT:
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 2;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 1000;
            m_tFrame.dwTime = GetTickCount64();
            break;
        case MONSTERTWO_STATE::DEAD:
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 3;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 200;
            m_tFrame.dwTime = GetTickCount64();
            break;
        }
    }
    m_eMTPreState = m_eMTCurState;
}

void CMonsterTwo::MT_FSM()
{
    if (m_iMaxSnowStat == 0 && !m_bReadyToDie)
    {
        Jump();
    }

    if (m_bReadyToDie)
    {
        m_pFrameKey = L"Minion_Die";
        m_eMTCurState = MONSTERTWO_STATE::DEAD;
    }
    switch (m_eMTCurState)
    {
    case CMonsterTwo::MONSTERTWO_STATE::IDLE:
        if (m_dwIdleTime + 1500 < GetTickCount64())
        {
            m_eMTCurState = MONSTERTWO_STATE::WALK;

            if (m_eMonsterDirection == OBJECT_DIRECTION::DIR_LEFT)
                m_pFrameKey = L"mons3_left_walk";
            else
                m_pFrameKey = L"mons3_right_walk";
        }

        if (m_dwJumpTime + 5000 < GetTickCount64())
        {
            if (((int)m_tInfo.fX % 10) > 4)
            {
                m_bMonsterJump = true;
                m_fTime = 0.0f;

                m_eMTCurState = MONSTERTWO_STATE::JUMP;

                if (m_eMTCurState == MONSTERTWO_STATE::JUMP)
                {
                    if (m_tFrame.iStart >= m_tFrame.iEnd)
                    {
                        m_tFrame.iStart = m_tFrame.iEnd;
                    }
                }
                if (m_eMonsterDirection == OBJECT_DIRECTION::DIR_RIGHT)
                {
                    m_pFrameKey = L"mons3_right_walk";
                    m_fSpeed = 0;
                }
                else if (m_eMonsterDirection == OBJECT_DIRECTION::DIR_LEFT)
                {
                    m_pFrameKey = L"mons3_left_walk";
                    m_fSpeed = 0;
                }
            }
        }

        break;
    case CMonsterTwo::MONSTERTWO_STATE::WALK:
        if (m_iMaxSnowStat == 0)
        {
            if (m_eMonsterDirection == OBJECT_DIRECTION::DIR_LEFT)
            {
                m_pFrameKey = L"mons3_left_walk";
                m_tInfo.fX -= 1.7f;
            }
            else
            {
                m_pFrameKey = L"mons3_right_walk";
                m_tInfo.fX += 1.7f;
            }

            if (m_dwShootTime + 4500 < GetTickCount64())
            {
                if (((int)m_tInfo.fX % 10) > 2)
                {
                    m_eMTCurState = MONSTERTWO_STATE::SHOOT;

                    if (m_tFrame.iStart >= m_tFrame.iEnd - 1)
                    {
                        m_tFrame.iStart = m_tFrame.iEnd;
                    }
                    if (m_eMonsterDirection == OBJECT_DIRECTION::DIR_LEFT)
                    {
                        m_pFrameKey = L"mons3_shoot_left";
                    }
                    else
                    {
                        m_pFrameKey = L"mons3_shoot_right";
                    }
                    m_dwIdleTime = GetTickCount64();
                }
                else
                {
                    m_dwShootTime = GetTickCount64();
                }
            }
        }
        break;
    case CMonsterTwo::MONSTERTWO_STATE::SHOOT:

        if (m_dwBulletCoolTime + 500 < GetTickCount64())
        {
            if (m_tFrame.iStart == m_tFrame.iEnd - 1)
            {
                m_tFrame.iStart = m_tFrame.iEnd;

                Create_MonsterBullet(m_eMonsterDirection);

                m_dwBulletCoolTime = GetTickCount64();
            }
        }

        if (m_dwIdleTime + 3000 < GetTickCount64())
        {
            m_eMTCurState = MONSTERTWO_STATE::IDLE;

            m_pFrameKey = L"mons3_idle";

            m_dwIdleTime = GetTickCount64();

            m_dwShootTime = GetTickCount64();
        }

        break;
    case CMonsterTwo::MONSTERTWO_STATE::JUMP:
        m_eMTCurState = MONSTERTWO_STATE::IDLE;
        m_pFrameKey = L"mons3_idle";
        m_dwJumpTime = GetTickCount64();

        break;
    case CMonsterTwo::MONSTERTWO_STATE::DEAD:
        if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount64())
        {
            ++m_tFrame.iStart;

            if (m_tFrame.iStart >= m_tFrame.iEnd - 1)
            {
                m_tFrame.iStart = m_tFrame.iEnd - 1;
            }
            m_tFrame.dwTime = GetTickCount64();
        }
        if (m_dwDieCoolTime + 500 < GetTickCount64())
        {
            m_bDead = true;
        }
        break;
    }
}

CObject* CMonsterTwo::Create_MonsterBullet(OBJECT_DIRECTION _eDirection)
{
    CObject* pMonsterTwoBullet = new CMonsterTwoBullet;

    pMonsterTwoBullet->Initialize();

    pMonsterTwoBullet->Set_Direction(_eDirection);

    if (_eDirection == OBJECT_DIRECTION::DIR_LEFT)
    {
        pMonsterTwoBullet->Set_Pos(m_tInfo.fX, m_tInfo.fY);
    }
    else
        pMonsterTwoBullet->Set_Pos(m_tInfo.fX, m_tInfo.fY);


    CObjectManager::Get_Instance()->Add_Object(OBJECT_LIST::MONSTERBULLET, pMonsterTwoBullet);

    return pMonsterTwoBullet;
}


void CMonsterTwo::MT_Move_Frame()
{
    if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount64())
    {
        ++m_tFrame.iStart;

        if (m_tFrame.iStart > m_tFrame.iEnd)
            m_tFrame.iStart = 0;

        m_tFrame.dwTime = GetTickCount64();
    }
}

void CMonsterTwo::Jump()
{
    if (m_bMonsterJump)
    {
        if (m_fGravityValue < 4.0f)
        {
            m_bFalling = true;
        }
        m_tInfo.fY -= m_fGravityValue;

        m_fGravityValue -= 0.35f;

        m_eMTCurState = MONSTERTWO_STATE::JUMP;

        if (m_eMonsterDirection == OBJECT_DIRECTION::DIR_RIGHT)
        {
            m_pFrameKey = L"mons3_shoot_right";
        }
        else if (m_eMonsterDirection == OBJECT_DIRECTION::DIR_LEFT)
        {
            m_pFrameKey = L"mons3_shoot_left";
        }
    }
}

void CMonsterTwo::Set_ReadyToDie(bool _bReadyToDie)
{
    m_bReadyToDie = _bReadyToDie;

    if (!m_bItemCalled)
    {
        switch (GetTickCount64() % 4)
        {
        case 0:
            CObjectManager::Get_Instance()->Add_Object(OBJECT_LIST::ITEM,
                CAbstractFactory<CSpeedItem>::Create(m_tInfo.fX, m_tInfo.fY));
            m_bItemCalled = true;
            break;
        case 1:
            CObjectManager::Get_Instance()->Add_Object(OBJECT_LIST::ITEM,
                CAbstractFactory<CPowerItem>::Create(m_tInfo.fX, m_tInfo.fY));
            m_bItemCalled = true;
            break;
        case 2:
            CObjectManager::Get_Instance()->Add_Object(OBJECT_LIST::ITEM,
                CAbstractFactory<CRangeItem>::Create(m_tInfo.fX, m_tInfo.fY));
            m_bItemCalled = true;
            break;
        case 3:
            CObjectManager::Get_Instance()->Add_Object(OBJECT_LIST::ITEM,
                CAbstractFactory<CPointItem>::Create(m_tInfo.fX, m_tInfo.fY));
            m_bItemCalled = true;
            break;
        }
    }
}
