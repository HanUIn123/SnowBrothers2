#include "pch.h"
#include "MonsterOne.h"
#include "BmpManager.h"
#include "SpawnManager.h"
#include "Player.h"
#include "PlayerManager.h"
#include "CollisionManager.h"
#include "ObjectManager.h"
#include "AbstractFactory.h"
#include "SpeedItem.h"
#include "PowerItem.h"
#include "RangeItem.h"
#include "PointItem.h"

CMonsterOne::CMonsterOne() :
    m_iRandNum(0),
    m_eMonsterCurState(MONSTER_STATE::MS_IDLE),
    m_eMonsterPreState(MONSTER_STATE::MS_END),
    m_eMonsterDirection(OBJECT_DIRECTION::DIR_LEFT),
    m_fPower(16.0f),
    m_fTime(0.0f),
    m_bItemCalled(false)
{
    m_pCollisionName = L"ENEMYONE";

    m_vecHDC.clear();

    m_dwWalkingTime = GetTickCount64();
    m_dwIdleTime = GetTickCount64();
    m_dwJumpingTime = GetTickCount64();
    m_dwDieCoolTime = GetTickCount64();
}

CMonsterOne::~CMonsterOne()
{
    Release();
}

void CMonsterOne::Initialize()
{
    m_vecHDC.assign(10, nullptr);


    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Monster/Stand_front.bmp", L"Monster_One_Idle");

    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Monster/Monster_Stand_Left.bmp", L"Monster_Stand_Left");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Monster/Monster_Stand_Right.bmp", L"Monster_Stand_Right");

    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Monster/Monster_Walk_Left.bmp", L"Monster_Walk_Left");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Monster/Monster_Walk_Right.bmp", L"Monster_Walk_Right");

    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Monster/Monster_Jump_Right2.bmp", L"Monster_Jump_Right");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Monster/Monster_Jump_Left2.bmp", L"Monster_Jump_Left");

    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Monster/MonsterOne_Dead.bmp", L"MonsterOne_Dead");

    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Snow/0.bmp", L"0");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Snow/1.bmp", L"1");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Snow/2.bmp", L"2");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Snow/3.bmp", L"3");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Snow/4.bmp", L"4");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Snow/5.bmp", L"5");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Snow/6.bmp", L"6");

    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Snow/Rolling_Snow2.bmp", L"Rolling_Snow");

    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Snow/Player_With_Snow.bmp", L"Player_With_Snow");

    m_tInfo = { 660.0f, 100.0f, 64.0f,64.0f };

    m_fSpeed = 1.7f;

    m_pFrameKey = L"Monster_One_Idle";

    m_tFrame = { 0,0,0,100,GetTickCount64() };

    // Monster Snow State
    for (int i = 0; i < 7; ++i)
    {
        TCHAR m_strName[7] = L"";

        swprintf_s(m_strName, L"%d", i);

        m_vecHDC[i] = CBmpManager::Get_Instance()->Find_Img(m_strName);
    }

    m_pSnowFrameKey = L"Rolling_Snow";
    m_tSnowFrame = { 0,3,0,10,GetTickCount64() };
}

int CMonsterOne::Update()
{
    if (m_bDead)
        return (UINT)OBJECT_STATE::OBJ_DEAD;

    if (m_bReadyToDie == false)
        m_tInfo.fY += 7.0f;
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

void CMonsterOne::Late_Update()
{
    __super::Update_Rect();

    if (m_iMaxSnowStat >= 6)
    {
        m_pCollisionName = L"ENEMYONESNOW";
    }

    Set_TobeRoll();

    SnowBall_Roll();

    MonsterOne_Animation();

    Monster_Snow_Ani();

    if (m_tInfo.fX > WINCX - 70)
        m_eMonsterDirection = OBJECT_DIRECTION::DIR_LEFT;
    if (m_tInfo.fX < 70)
        m_eMonsterDirection = OBJECT_DIRECTION::DIR_RIGHT;

    if ((m_tInfo.fX < WINCX - 10 && m_tInfo.fX > 10))
    {
        MonsterOne_FSM();
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
        m_pSnowFrameKey = L"Rolling_Snow";
    }

    CObject::Move_Frame();
    CMonster::Snow_Move_Frame();
}

void CMonsterOne::Render(HDC _hDC)
{
    //Rectangle(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

    HDC	hMonsterOneDC = CBmpManager::Get_Instance()->Find_Img(m_pFrameKey);

    HDC hSnowRollDC = CBmpManager::Get_Instance()->Find_Img(m_pSnowFrameKey);

    GdiTransparentBlt
    (
        _hDC,
        int(m_tRect.left),
        int(m_tRect.top),
        int(64),
        int(64),
        hMonsterOneDC,
        int(m_tInfo.fCX * m_tFrame.iStart),
        int(m_tInfo.fCY * m_tFrame.iMotion),
        int(64),
        int(64),
        RGB(255, 0, 255)
    );


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
            hSnowRollDC,
            int(m_tInfo.fCX * m_tSnowFrame.iStart),
            int(m_tInfo.fCY * m_tSnowFrame.iMotion),
            int(64),
            int(64),
            RGB(255, 0, 255)
        );
    }
}

void CMonsterOne::Release()
{
}

void CMonsterOne::MonsterOne_Animation()
{
    if (m_eMonsterPreState != m_eMonsterCurState)
    {
        switch (m_eMonsterCurState)
        {
        case MONSTER_STATE::MS_IDLE:
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 0;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 200;
            m_tFrame.dwTime = GetTickCount64();
            break;

        case MONSTER_STATE::MS_WALK:
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 1;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 100;
            m_tFrame.dwTime = GetTickCount64();
            break;

        case MONSTER_STATE::MS_JUMP:
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 3;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 350;
            m_tFrame.dwTime = GetTickCount64();
            break;

        case MONSTER_STATE::MS_DEAD:
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 5;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 70;
            m_tFrame.dwTime = GetTickCount64();
            break;
        case MONSTER_STATE::MS_END:
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 0;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 35;
            m_tFrame.dwTime = GetTickCount64();
            break;
        }
    }
    m_eMonsterPreState = m_eMonsterCurState;
}

void CMonsterOne::MonsterOne_FSM()
{
    if (m_iMaxSnowStat == 0 && !m_bReadyToDie)
    {
        Walk();
        Jump();
    }
    if (m_bReadyToDie)
    {
        m_pFrameKey = L"MonsterOne_Dead";
        m_eMonsterCurState = MONSTER_STATE::MS_DEAD;
    }

    if (m_eMonsterCurState == MONSTER_STATE::MS_DEAD)
    {
        if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount64())
        {
            ++m_tFrame.iStart;

            if (m_tFrame.iStart >= m_tFrame.iEnd)
            {
                m_tFrame.iStart = m_tFrame.iEnd;
                m_tFrame.iStart = 0;
            }
            m_tFrame.dwTime = GetTickCount64();

            if ((UINT)m_eDir == (UINT)OBJECT_DIRECTION::DIR_RIGHT)
                m_tInfo.fX += 15.0f;
            else
                m_tInfo.fX -= 15.0f;
        }
        if (m_dwDieCoolTime + 2500 < GetTickCount64())
        {
            m_bDead = true;
            CSpawnManager::Get_Instance()->Decrease_MonsterCount(1);
        }
    }
}

void CMonsterOne::Walk()
{
    m_fTime += 0.2f;
    if (m_dwIdleTime + 1500 < GetTickCount64())
    {
        m_bMonsterJump = false;
        m_bMonsterWalk = true;

        if (m_bMonsterWalk = true)
        {
            m_fSpeed = 1.7f;
            m_eMonsterCurState = MONSTER_STATE::MS_WALK;

            if (m_eMonsterDirection == OBJECT_DIRECTION::DIR_RIGHT)
            {
                m_pFrameKey = L"Monster_Walk_Right";
                m_tInfo.fX += m_fSpeed;
            }
            else if (m_eMonsterDirection == OBJECT_DIRECTION::DIR_LEFT)
            {
                m_pFrameKey = L"Monster_Walk_Left";
                m_tInfo.fX -= m_fSpeed;
            }
        }

        if (m_dwIdleTime + 5500 < GetTickCount64())
            m_bMonsterWalk = false;

        if (m_bMonsterWalk == false)
        {
            m_eMonsterCurState = MONSTER_STATE::MS_IDLE;

            if (m_eMonsterDirection == OBJECT_DIRECTION::DIR_RIGHT)
            {
                m_pFrameKey = L"Monster_Stand_Right";
                m_fSpeed = 0;
            }
            else if (m_eMonsterDirection == OBJECT_DIRECTION::DIR_LEFT)
            {
                m_pFrameKey = L"Monster_Stand_Left";
                m_fSpeed = 0;
            }

            m_dwIdleTime = GetTickCount64();
        }

        if (m_bMonsterWalk == false)
        {
            if (m_dwJumpingTime + 500 < GetTickCount64())
            {
                if (((int)m_tInfo.fX % 10) > 4)
                {
                    m_bMonsterJump = true;
                    m_fTime = 0.f;

                    m_eMonsterCurState = MONSTER_STATE::MS_JUMP;

                    if (m_eMonsterCurState == MONSTER_STATE::MS_JUMP)
                    {
                        if (m_tFrame.iStart >= m_tFrame.iEnd)
                        {
                            m_tFrame.iStart = m_tFrame.iEnd;
                        }
                    }

                    if (m_eMonsterDirection == OBJECT_DIRECTION::DIR_RIGHT)
                    {
                        m_pFrameKey = L"Monster_Jump_Right";
                        m_fSpeed = 0;
                    }
                    else if (m_eMonsterDirection == OBJECT_DIRECTION::DIR_LEFT)
                    {
                        m_pFrameKey = L"Monster_Jump_Left";
                        m_fSpeed = 0;
                    }
                }
            }
            m_dwIdleTime = GetTickCount64();
        }
    }


}

void CMonsterOne::Jump()
{
    if (m_bMonsterJump)
    {
        if (m_fGravityValue < 4.0f)
        {
            m_bFalling = true;
        }
        m_tInfo.fY -= m_fGravityValue;

        m_fGravityValue -= 0.35f;

        m_eMonsterCurState = MONSTER_STATE::MS_JUMP;

        if (m_eMonsterDirection == OBJECT_DIRECTION::DIR_RIGHT)
        {
            m_pFrameKey = L"Monster_Jump_Right";
        }
        else if (m_eMonsterDirection == OBJECT_DIRECTION::DIR_LEFT)
        {
            m_pFrameKey = L"Monster_Jump_Left";
        }
    }
}

void CMonsterOne::DropItem()
{
    
}


void CMonsterOne::Set_ReadyToDie(bool _bReadyToDie)
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
    m_dwDieCoolTime = GetTickCount64();
}

