#include "pch.h"
#include "BossTwo.h"
#include "BmpManager.h"
#include "AbstractFactory.h"
#include "ObjectManager.h"

#include "PlayerManager.h"
#include "KeyManager.h"
#include "ScrollManager.h"

#include "Minions.h"
#include "BossTwoBullet.h"

#include "SoundMgr.h"


CBossTwo::CBossTwo() :
    m_eBossCurState(BOSSTWO_STATE::IDLE),
    m_eBossPreState(BOSSTWO_STATE::END),
    iRandomPosX(0), iRandomPosY(0),
    m_bGoRight(false),
    m_fCurrentBossTwoHp(100.f),
    m_fMaxBossTwoHp(100.f)
{
    m_pCollisionName = L"BOSSTWO";

    m_dwIdleTime = GetTickCount64();

    m_dwShotTime = GetTickCount64();

    m_dwBulletCool = GetTickCount64();

    m_dwMoveHorTime = GetTickCount64();

    m_dwMoveHorTime2 = GetTickCount64();

    m_dwBossHitTime = GetTickCount64();
}

CBossTwo::~CBossTwo()
{
    Release();
}

void CBossTwo::Initialize()
{
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Boss/Boss2_Idle.bmp", L"Boss2_Idle");

    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Boss/Boss2_Spawn2.bmp", L"Boss2_Spawn");

    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Boss/Boss2_MissileReady.bmp", L"Boss2_MissileReady");

    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Boss/Boss2_Hited.bmp", L"Boss2_Hited");

    m_tInfo = { 610, WINCY / 2.0f, 384.0f,384.0f };

    m_pFrameKey = L"Boss2_Idle";

    m_tFrame = { 0,3,0,100,GetTickCount64() };
}

int CBossTwo::Update()
{
    if (m_bDead)
        return (UINT)OBJECT_STATE::OBJ_DEAD;

    if (m_dwMoveHorTime + 3500 <  GetTickCount64())
    {
        m_bGoRight = true;
        m_eBossCurState = BOSSTWO_STATE::MOVE_HORIZON;
        m_dwMoveHorTime = GetTickCount64();
    }

    iRandomPosX = rand() % 3 + 1;

    m_tInfo.fY += 4.0f;

    return 0;
}

void CBossTwo::Late_Update()
{
    __super::Update_Rect();

    BossTwo_Animation();

    BossTwo_FSM();

    BossTwo_MoveFrame();
}

void CBossTwo::Render(HDC _hDC)
{
    //Rectangle(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
    HDC	hBossTwoDC = CBmpManager::Get_Instance()->Find_Img(m_pFrameKey);
    GdiTransparentBlt
    (
        _hDC,
        int(m_tRect.left),
        int(m_tRect.top),
        int(384),
        int(384),
        hBossTwoDC,
        int(m_tInfo.fCX * m_tFrame.iStart),
        int(m_tInfo.fCY * m_tFrame.iMotion),
        int(384),
        int(384),
        RGB(255, 0, 255)
    );
}

void CBossTwo::Release()
{
}


void CBossTwo::BossTwo_Animation()
{
    if (m_eBossPreState != m_eBossCurState)
    {
        switch (m_eBossCurState)
        {
        case BOSSTWO_STATE::IDLE:
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 3;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 200;
            m_tFrame.dwTime = GetTickCount64();
            break;

        case BOSSTWO_STATE::SPAWN_MINION:
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 2;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 150;
            m_tFrame.dwTime = GetTickCount64();
            break;

        case BOSSTWO_STATE::NOSE_SHOT:
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 0;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 200;
            m_tFrame.dwTime = GetTickCount64();
            break;

        case BOSSTWO_STATE::GOT_HIT:
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 0;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 200;
            m_tFrame.dwTime = GetTickCount64();
            break;
        }
        m_eBossPreState = m_eBossCurState;
    }
}

void CBossTwo::BossTwo_FSM()
{
    // IDLE , SPAWN_MINION, NOSE_SHOT
    switch (m_eBossCurState)
    {
    case CBossTwo::BOSSTWO_STATE::IDLE:
        if (m_dwIdleTime + 3500 < GetTickCount64())
        {
            m_eBossCurState = BOSSTWO_STATE::SPAWN_MINION;

            m_pFrameKey = L"Boss2_Spawn";
        }
        break;
    case CBossTwo::BOSSTWO_STATE::SPAWN_MINION:

        if (m_dwIdleTime + 6500 < GetTickCount64())
        {
            Create_Minions();

            if (m_dwShotTime + 2500 < GetTickCount64())
            {
                m_eBossCurState = BOSSTWO_STATE::NOSE_SHOT;

                m_pFrameKey = L"Boss2_MissileReady";
            }
        }
        break;
    case CBossTwo::BOSSTWO_STATE::NOSE_SHOT:


        if (m_dwBulletCool + 3500 < GetTickCount64())
        {
            Create_BossBullet(OBJECT_DIRECTION::DIR_LEFT, m_pTarget);

            m_dwBulletCool = GetTickCount64();
        }

        if (m_dwIdleTime + 7000 < GetTickCount64())
        {
            m_eBossCurState = BOSSTWO_STATE::IDLE;

            m_pFrameKey = L"Boss2_Idle";

            m_dwIdleTime = GetTickCount64();

            m_dwShotTime = GetTickCount64();
        }
        break;

    case CBossTwo::BOSSTWO_STATE::MOVE_HORIZON:

        if (m_bGoRight)
        {
            m_tInfo.fX += 3.0f; 

            if (m_tInfo.fX >= 900)
            {
                m_bGoRight = false;
            }
        }
        else
        {
            if(m_tInfo.fX >= 630)
                m_tInfo.fX -= 3.0f;

            CSoundMgr::Get_Instance()->PlaySound(L"TrainBoss_Hmm.wav", TRAIN_NOISE, 1.0f);
        }


        if (m_dwMoveHorTime2 + 5000 < GetTickCount64())
        {
            m_eBossCurState = BOSSTWO_STATE::SPAWN_MINION;
            m_pFrameKey = L"Boss2_Spawn";

            m_dwMoveHorTime = GetTickCount64();
            m_dwMoveHorTime2 = GetTickCount64();
        }



        break;


    case CBossTwo::BOSSTWO_STATE::GOT_HIT:
        if (m_dwBossHitTime + 700 < GetTickCount64())
        {
            m_eBossCurState = BOSSTWO_STATE::IDLE;

            m_pFrameKey = L"Boss2_Idle";

            m_dwBossHitTime = GetTickCount64();
        }

        break;
    }


}

void CBossTwo::Create_Minions()
{
    for (int i = 0; i < 3; ++i)
        CObjectManager::Get_Instance()->Add_Object(OBJECT_LIST::MINION, CAbstractFactory<CMinions>::Create(float(50.0f + (i * 80 * iRandomPosX)), 20.0f, OBJECT_DIRECTION::DIR_RIGHT));
       
    list<CObject*> MinionList = CObjectManager::Get_Instance()->Get_ObjectList(OBJECT_LIST::MINION);

    for (auto iter = MinionList.begin(); iter != MinionList.end(); ++iter)
    {
        dynamic_cast<CMonster*>(*iter)->Set_TargetPlayer(m_pTarget);
    }
}

CObject* CBossTwo::Create_BossBullet(OBJECT_DIRECTION _eDirection, CObject* _ptarget)
{

    CSoundMgr::Get_Instance()->PlaySound(L"TrainBoss_Hmm.wav", BOSS_NOSE, 1.0f);
    CObject* pBossBullet = new CBossTwoBullet;

    pBossBullet->Initialize();

    if (dynamic_cast<CBossTwoBullet*>(pBossBullet)->Get_FirstCreate())
        pBossBullet->Set_TargetPlayer(_ptarget);

    pBossBullet->Set_Direction(_eDirection);

    if (_eDirection == OBJECT_DIRECTION::DIR_LEFT)
    {
        pBossBullet->Set_Pos(m_tInfo.fX - 50.f, m_tInfo.fY + 10.0f);
    }

    CObjectManager::Get_Instance()->Add_Object(OBJECT_LIST::BOSSBULLET, pBossBullet);

    return pBossBullet;
}


void CBossTwo::BossTwo_MoveFrame()
{
    if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount64())
    {
        ++m_tFrame.iStart;

        if (m_tFrame.iStart > m_tFrame.iEnd)
            m_tFrame.iStart = 0;

        m_tFrame.dwTime = GetTickCount64();
    }
}
