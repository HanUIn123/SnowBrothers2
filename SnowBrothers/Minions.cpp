#include "pch.h"
#include "Minions.h"
#include "BmpManager.h"

#include "ObjectManager.h"
#include "AbstractFactory.h"
#include "SpeedItem.h"
#include "PowerItem.h"
#include "RangeItem.h"
#include "PointItem.h"


CMinions::CMinions() :
    m_eMinionCurState(MONSTERMINION_STATE::LANDING),
    m_eMinionPreState(MONSTERMINION_STATE::END),
    m_eMinionDirection(OBJECT_DIRECTION::DIR_LEFT),
    m_iRandDirection(0),
    m_bItemCalled(false)
{
    m_pCollisionName = L"MINION";

    m_vecHDC.clear();

    m_dwIdleTime = GetTickCount64();

    m_dwDieCoolTime = GetTickCount64();
}

CMinions::~CMinions()
{
    Release();
}

void CMinions::Initialize()
{
    m_vecHDC.assign(10, nullptr);

    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Monster/Minion1.bmp", L"Minion1");

    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Snow/0.bmp", L"0");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Snow/1.bmp", L"1");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Snow/2.bmp", L"2");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Snow/3.bmp", L"3");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Snow/4.bmp", L"4");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Snow/5.bmp", L"5");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Snow/6.bmp", L"6");

    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Monster/Minioin_Idle.bmp", L"Minioin_Idle");

    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Monster/Minioin_Falling3.bmp", L"Minioin_Falling");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Monster/Minion_Walk_Left.bmp", L"Minion_Walk_Left");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Monster/Minion_Walk_Right.bmp", L"Minion_Walk_Right");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Monster/Minion_Die2.bmp", L"Minion_Die");


    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Snow/Rolling_Snow.bmp", L"Rolling_Snow2");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Snow/Player_With_Snow.bmp", L"Player_With_Snow");


    m_tInfo = { 100.0f, 0.0f, 64.0f,64.0f };

    m_fSpeed = 1.7f;

    m_iRandDirection = rand() % 2 + 1;

    m_pFrameKey = L"Minioin_Falling";

    m_bFalling = true;


    // Monster Snow State
    for (int i = 0; i < 7; ++i)
    {
        TCHAR m_strName[7] = L"";

        swprintf_s(m_strName, L"%d", i);

        m_vecHDC[i] = CBmpManager::Get_Instance()->Find_Img(m_strName);
    }

    m_pSnowFrameKey = L"Rolling_Snow2";
    m_tSnowFrame = { 0,3,0,10,GetTickCount64() };
}

int CMinions::Update()
{
    if (m_bDead)
        return (UINT)OBJECT_STATE::OBJ_DEAD;

    if (m_bFalling)
        m_tInfo.fY += 2.0f;

    if (m_bAfterLanding)
    {
        if (m_bReadyToDie == false)
        {
            m_tInfo.fY += 6.0f;
        }
        else
        {
           // m_tInfo.fY -= 5.0f;
        }
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

void CMinions::Late_Update()
{
    __super::Update_Rect();

    if (m_iMaxSnowStat >= 6)
    {
        m_pCollisionName = L"MINIONSNOW";
    }

    Set_TobeRoll();

    SnowBall_Roll();

    Monster_Snow_Ani();

    //Minion_FSM();

    Minion_Animation();

    if (m_tInfo.fX > WINCX - 70)
        m_eMinionDirection = OBJECT_DIRECTION::DIR_LEFT;
    if (m_tInfo.fX < 70)
        m_eMinionDirection = OBJECT_DIRECTION::DIR_RIGHT;

    if ((m_tInfo.fX < WINCX - 10 && m_tInfo.fX > 10))
    {
        Minion_FSM();
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
        m_pSnowFrameKey = L"Rolling_Snow2";
    }


    Minion_Move_Frame();
    CMonster::Snow_Move_Frame();
}

void CMinions::Render(HDC _hDC)
{
    //Rectangle(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

    HDC	hMinionDC = CBmpManager::Get_Instance()->Find_Img(m_pFrameKey);
    HDC hSnowRoll2DC = CBmpManager::Get_Instance()->Find_Img(m_pSnowFrameKey);

    if (!m_bSnowBallMove)
    {
        GdiTransparentBlt
        (
            _hDC,
            int(m_tRect.left),
            int(m_tRect.top),
            int(64),
            int(64),
            hMinionDC,
            int(m_tInfo.fCX * m_tFrame.iStart),
            int(m_tInfo.fCY * m_tFrame.iMotion),
            int(64),
            int(64),
            RGB(255, 0, 255)
        );
    }

    if (m_bHited)
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
            hSnowRoll2DC,
            int(m_tInfo.fCX * m_tSnowFrame.iStart),
            int(m_tInfo.fCY * m_tSnowFrame.iMotion),
            int(64),
            int(64),
            RGB(255, 0, 255)
        );
    }
}

void CMinions::Release()
{
}

void CMinions::Minion_Animation()
{
    // enum class MONSTERMINION_STATE { IDLE, WALK, DEAD, END};
    if (m_eMinionPreState != m_eMinionCurState)
    {
        switch (m_eMinionCurState)
        {
        case MONSTERMINION_STATE::IDLE:
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 2;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 200;
            m_tFrame.dwTime = GetTickCount64();
            break;
        case MONSTERMINION_STATE::LANDING:
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 3;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 200;
            m_tFrame.dwTime = GetTickCount64();
            break;

        case MONSTERMINION_STATE::WALK:
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 2;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 100;
            m_tFrame.dwTime = GetTickCount64();
            break;

        case MONSTERMINION_STATE::DEAD:
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 3;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 200;
            m_tFrame.dwTime = GetTickCount64();
            break;
        }
    }
    m_eMinionPreState = m_eMinionCurState;
}

void CMinions::Minion_FSM()
{
    if (m_bReadyToDie)
    {
        m_pFrameKey = L"Minion_Die";
        m_eMinionCurState = MONSTERMINION_STATE::DEAD;
    }

    switch (m_eMinionCurState)
    {
    case CMinions::MONSTERMINION_STATE::IDLE:
        
        break;
    case CMinions::MONSTERMINION_STATE::LANDING:
        if (m_tFrame.iStart >= m_tFrame.iEnd - 1)
        {
            m_tFrame.iStart = m_tFrame.iEnd - 1;
        }

        if (m_dwIdleTime + 1500 < GetTickCount64())
        {
            m_eMinionCurState = MONSTERMINION_STATE::WALK;

            if (m_eMinionDirection == OBJECT_DIRECTION::DIR_LEFT)
                m_pFrameKey = L"Minion_Walk_Left";
            else
                m_pFrameKey = L"Minion_Walk_Right";
        }
        break;
    case CMinions::MONSTERMINION_STATE::WALK:
        if (m_iMaxSnowStat == 0)
        {
            if (m_eMinionDirection == OBJECT_DIRECTION::DIR_LEFT)
            {
                m_pFrameKey = L"Minion_Walk_Left";
                m_tInfo.fX -= m_fSpeed;
            }
            else
            {
                m_pFrameKey = L"Minion_Walk_Right";
                m_tInfo.fX += m_fSpeed;
            }
        }
        break;
    case CMinions::MONSTERMINION_STATE::DEAD:
        if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount64())
        {
            ++m_tFrame.iStart;

            if (m_tFrame.iStart >= m_tFrame.iEnd -1)
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

void CMinions::Minion_Move_Frame()
{
    if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount64())
    {
        ++m_tFrame.iStart;

        if (m_tFrame.iStart > m_tFrame.iEnd)
            m_tFrame.iStart = 0;

        m_tFrame.dwTime = GetTickCount64();
    }
}

void CMinions::Set_ReadyToDie(bool _bReadyToDie)
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
