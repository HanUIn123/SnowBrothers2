#include "pch.h"
#include "BossOne.h"
#include "BmpManager.h"
#include "AbstractFactory.h"
#include "ObjectManager.h"

#include "PlayerManager.h"
#include "KeyManager.h"
#include "ScrollManager.h"


#include "Minions.h"
#include "EffectManager.h"
#include "MapManager.h"


CBossOne::CBossOne() :
    m_eBossCurState(BOSSONE_STATE::IDLE),
    m_eBossPreState(BOSSONE_STATE::END),
    m_fCurrentBossOneHp(100.f),
    m_fMaxBossOneHp(100.f),
    m_bStartPattern1(false),
    m_bStartPattern2(false),
    m_bIsDeadOneTime(false),
    m_bShakingArms(false),
    m_bFaceChanging(false),
    m_bMoving(false),
    m_bLonging(false),
    m_bGoBack(false),
    m_bRestart(false),
    m_bBossJumpLeft(false),
    m_bBossJumpRight(false),
    m_bBossJumpLeftSide(true),
    m_bBossJumpRightSide(false),
    m_bJumpOver(false),
    m_eBossOneDirection(OBJECT_DIRECTION::DIR_END),
    m_iRandomFirePos(0)
{
    m_pCollisionName = L"BOSSONE";

    m_dwIdleTime = GetTickCount64();

    m_dwFaceChnagingTime = GetTickCount64();

    m_dwShakingArmTime = GetTickCount64();

    m_dwSpawnMinionTime = GetTickCount64();

    m_dwTurnLeftTime = GetTickCount64();

    m_dwReStartTime = GetTickCount64();

    m_dwCheckPlayerDirectionTime = GetTickCount64();

    m_dwBossJumpTime = GetTickCount64();
}

CBossOne::~CBossOne()
{
    Release();
}

void CBossOne::Initialize()
{
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Boss/Boss1_Idle.bmp", L"Boss1_Idle");

    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Boss/Boss1_FaceChange2.bmp", L"Boss1_FaceChange");

    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Boss/Boss1_Shake_Front.bmp", L"Boss1_Shake_Front");

    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Boss/Boss1_See_Left.bmp", L"Boss1_See_Left");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Boss/Boss1_See_Right.bmp", L"Boss1_See_Right");

    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Boss/Boss1_Shaking_Left.bmp", L"Boss1_Shaking_Left");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Boss/Boss1_Shaking_Right.bmp", L"Boss1_Shaking_Right");

    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Boss/Boss1_Long_Left.bmp", L"Boss1_Long_Left");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Boss/Boss1_Long_Right.bmp", L"Boss1_Long_Right");


    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Effect/BossHitedEffect2.bmp", L"BossHitedEffect2");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Effect/BossHitedEffect3.bmp", L"BossHitedEffect3");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Effect/BossHitedEffect4.bmp", L"BossHitedEffect4");

    m_tInfo = { WINCX / 2.0f, WINCY / 2.0f, 384.0f,384.0f };

    m_iRandomFirePos = rand() % 4 + 1;

    m_pFrameKey = L"Boss1_Idle";

    m_pHitedFrameKey = L"BossHitedEffect";

    m_tFrame = { 0,2,0,100,GetTickCount64() };

    m_tHitedFrame = { 0,1,0,100,GetTickCount64() };
}

int CBossOne::Update()
{
    if (m_bDead)
        return (UINT)OBJECT_STATE::OBJ_DEAD;

    m_tInfo.fY += 4.0f;

    if (m_tInfo.fX == WINCX / 2.0f)
    {
        if (m_pTarget->Get_ObjectInfo().fX < WINCX / 2.0f)
        {
            m_eBossOneDirection = OBJECT_DIRECTION::DIR_LEFT;
        }
        else
        {
            m_eBossOneDirection = OBJECT_DIRECTION::DIR_RIGHT;
        }
    }

    //if (m_fCurrentBossOneHp >= 75.0f && m_fCurrentBossOneHp <= 90.0f && m_eBossCurState == BOSSONE_STATE::IDLE)
    {
    //    m_eBossCurState = BOSSONE_STATE::JUMP;

   //    if (m_eBossOneDirection == OBJECT_DIRECTION::DIR_LEFT)
   //    {
   //        m_bBossJumpLeft = true;
   //    }
   //    else
   //    {
   //        m_bBossJumpRight = true;
   //    }
    }
    if (CKeyManager::Get_Instance()->Key_Down('Q'))
    {
        m_bBossJumpRight = true;
        m_bBossJumpRightSide = true;
    }




    return 0;
}

void CBossOne::Late_Update()
{
    __super::Update_Rect();

    BossOne_Animation();

    BossOne_FSM();

    BossOne_MoveFrame();

   
    BossOne_LeftJump();

    Boss_Hited_Ani();

    CMonster::Hited_Move_Frame();
}

void CBossOne::Render(HDC _hDC)
{
    HDC	hBossOneDC = CBmpManager::Get_Instance()->Find_Img(m_pFrameKey);

    HDC hBossLongDC = CBmpManager::Get_Instance()->Find_Img(L"Boss1_Long_Left");
    HDC hBossLong2DC = CBmpManager::Get_Instance()->Find_Img(L"Boss1_Long_Right");


    HDC hBossHitedDC = CBmpManager::Get_Instance()->Find_Img(m_pHitedFrameKey);


    //Rectangle(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

    if (m_pFrameKey == L"Boss1_Long_Left")
    {
         GdiTransparentBlt
         (
             _hDC,
             int(m_tRect.left),
             int(m_tRect.top - 192),
             int(384),
             int(576),
             hBossLongDC,
             int(m_tInfo.fCX * m_tFrame.iStart),
             int(m_tInfo.fCY * m_tFrame.iMotion),
             int(384),
             int(576),
             RGB(255, 0, 255)
         );

        //Rectangle(_hDC, m_tRect.left, m_tRect.top - (m_tFrame.iStart * 38.4f), m_tRect.right, m_tRect.bottom - (m_tFrame.iStart * 38.4f));
    }
    else if (m_pFrameKey == L"Boss1_Long_Right")
    {
          GdiTransparentBlt
          (
              _hDC,
              int(m_tRect.left),
              int(m_tRect.top - 192),
              int(384),
              int(576),
              hBossLong2DC,
              int(m_tInfo.fCX * m_tFrame.iStart),
              int(m_tInfo.fCY * m_tFrame.iMotion),
              int(384),
              int(576),
              RGB(255, 0, 255)
          );


        //GdiTransparentBlt
        //(
        //    _hDC,
        //    int(m_tRect.left),
        //    int(m_tRect.top - 192),
        //    int(m_tInfo.fCX),
        //    int(576),
        //    hBossOneDC,
        //    int(384 * m_tFrame.iStart),
        //    int(384 * m_tFrame.iMotion),
        //    int(m_tInfo.fCX),
        //    int(576),
        //    RGB(255, 0, 255)
        //);

        //Rectangle(_hDC, m_tRect.left, m_tRect.top - (m_tFrame.iStart * 38.4f), m_tRect.right, m_tRect.bottom - (m_tFrame.iStart * 38.4f));
    }

    else
    {
        GdiTransparentBlt
        (
            _hDC,
            int(m_tRect.left),
            int(m_tRect.top),
            int(384),
            int(384),
            hBossOneDC,
            int(m_tInfo.fCX * m_tFrame.iStart),
            int(m_tInfo.fCY * m_tFrame.iMotion),
            int(384),
            int(384),
            RGB(255, 0, 255)
        );
    }

    if (m_bBossGotHit == true)
    {
        GdiTransparentBlt
        (
            _hDC,
            int(m_tRect.left + 120.0f),
            int(m_tRect.top + 100.0f),
            int(132),
            int(165),
            hBossHitedDC,
            int(132 * m_tHitedFrame.iStart),
            int(165 * m_tHitedFrame.iMotion),
            int(132),
            int(165),
            RGB(255, 0, 255)
        );
    }

    //TCHAR	szCount[32] = L"";
    //swprintf_s(szCount, L"BOSS_STATE : %d", (UINT)m_eBossCurState);
    //TextOut(_hDC, 20, 20, szCount, lstrlen(szCount));

    //TCHAR	szCount2[32] = L"";
    //swprintf_s(szCount2, L"BOSS_FX : %d", (UINT)m_tInfo.fX);
    //TextOut(_hDC, 20, 40, szCount2, lstrlen(szCount2));

    //TCHAR	szCount3[32] = L"";
    //swprintf_s(szCount3, L"BOSS_DIRECTION : %d", (UINT)m_eBossOneDirection);
    //TextOut(_hDC, 20, 60, szCount3, lstrlen(szCount3));
}

void CBossOne::Release()
{
}

void CBossOne::BossOne_Animation()
{
    if (m_eBossPreState != m_eBossCurState)
    {
        switch (m_eBossCurState)
        {
        case BOSSONE_STATE::IDLE:
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 2;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 200;
            m_tFrame.dwTime = GetTickCount64();
            break;

        case BOSSONE_STATE::FACE_CHANGE:
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 2;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 80;
            m_tFrame.dwTime = GetTickCount64();
            break;

        case BOSSONE_STATE::ARM_SHAKING:
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 2;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 200;
            m_tFrame.dwTime = GetTickCount64();
            break;

        case BOSSONE_STATE::ARM_SHAKE_LEFT:
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 2;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 200;
            m_tFrame.dwTime = GetTickCount64();
            break;

        case BOSSONE_STATE::SEE_LEFT:
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 1;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 200;
            m_tFrame.dwTime = GetTickCount64();
            break;

        case BOSSONE_STATE::JUMP:
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 2;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 200;
            m_tFrame.dwTime = GetTickCount64();
            break;

        case BOSSONE_STATE::LONG:
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 17;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 120;
            m_tFrame.dwTime = GetTickCount64();
            break;

        case BOSSONE_STATE::DEAD:
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 2;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 200;
            m_tFrame.dwTime = GetTickCount64();
            break;
        }
        m_eBossPreState = m_eBossCurState;
    }
}

void CBossOne::BossOne_FSM()
{
    switch (m_eBossCurState)
    {
    case CBossOne::BOSSONE_STATE::IDLE:

        if (m_bStartPattern2)
        {
            if (m_dwTurnLeftTime + 6000 < GetTickCount64())
            {
                m_pFrameKey = L"Boss1_Idle";

                m_eBossCurState = BOSSONE_STATE::SEE_LEFT;

                m_bMoving = true;

                m_dwTurnLeftTime = GetTickCount64();
            }
        }
        else if (!m_bStartPattern2 && m_tInfo.fX >= WINCX / 2.0f)
        {
            if (m_dwIdleTime + 3000 < GetTickCount64())
            {
                m_eBossCurState = BOSSONE_STATE::ARM_SHAKING;

                m_pFrameKey = L"Boss1_Shake_Front";
            }
        }

        break;
    case CBossOne::BOSSONE_STATE::FACE_CHANGE:
        if (m_dwIdleTime + 6000 < GetTickCount64())
        {
            m_tFrame.iStart = m_tFrame.iEnd;

            m_tFrame.dwSpeed = 0;

            if (m_dwSpawnMinionTime + 1000 < GetTickCount64())
            {
                Create_Minions(m_eBossOneDirection);

                m_dwSpawnMinionTime = GetTickCount64();
            }

            if (m_dwIdleTime + 7000 < GetTickCount64())
            {
                m_eBossCurState = BOSSONE_STATE::IDLE;

                m_pFrameKey = L"Boss1_Idle";

                m_bStartPattern2 = true;

            }
        }
        break;
    case CBossOne::BOSSONE_STATE::ARM_SHAKING:

        if (m_dwIdleTime + 4000 < GetTickCount64())
        {
            m_eBossCurState = BOSSONE_STATE::FACE_CHANGE;

            m_pFrameKey = L"Boss1_FaceChange";

            CSoundMgr::Get_Instance()->PlaySound(L"BossOneSpining.wav", BOSS_FC, 1.0f);
        }
        break;
    case CBossOne::BOSSONE_STATE::ARM_SHAKE_LEFT:

        if (m_bGoBack)
        {
            if ((UINT)m_eBossOneDirection == (UINT)OBJECT_DIRECTION::DIR_LEFT)
            {
                m_tInfo.fX += 2.0f;
                if (m_tInfo.fX >= WINCX / 2.0f)
                {
                    m_tInfo.fX = WINCX / 2.0f;

                    m_bStartPattern2 = false;

                    m_bGoBack = false;

                    m_bMoving = false;

                    m_eBossCurState = BOSSONE_STATE::IDLE;

                    m_pFrameKey = L"Boss1_Idle";

                    m_dwIdleTime = GetTickCount64();
                }

            }
            else if ((UINT)m_eBossOneDirection == (UINT)OBJECT_DIRECTION::DIR_RIGHT)
            {
                m_tInfo.fX -= 2.0f;
                if (m_tInfo.fX <= WINCX / 2.0f)
                {
                    m_tInfo.fX = WINCX / 2.0f;

                    m_bStartPattern2 = false;

                    m_bGoBack = false;

                    m_bMoving = false;

                    m_eBossCurState = BOSSONE_STATE::IDLE;

                    m_pFrameKey = L"Boss1_Idle";

                    m_dwIdleTime = GetTickCount64();
                }


                if (m_tInfo.fX >= 480.0f && !m_bGoBack)
                {
                    m_tInfo.fX = 480.0f;

                    m_eBossCurState = BOSSONE_STATE::LONG;

                    m_pFrameKey = L"Boss1_Long_Right";
                }
            }
        }
        else if (m_bMoving && m_bStartPattern2)
        {
            if (m_eBossOneDirection == OBJECT_DIRECTION::DIR_LEFT)
                m_tInfo.fX -= 2.0f;
            else
                m_tInfo.fX += 2.0f;
        }

        if (m_tInfo.fX <= 120.0f && !m_bGoBack)
        {
            m_tInfo.fX = 120.0f;

            m_eBossCurState = BOSSONE_STATE::LONG;

            m_pFrameKey = L"Boss1_Long_Left";
        }
        if (m_tInfo.fX >= 680.0f && !m_bGoBack)
        {
            m_tInfo.fX = 680.0f;

            m_eBossCurState = BOSSONE_STATE::LONG;

            m_pFrameKey = L"Boss1_Long_Right";
        }
        break;
    case CBossOne::BOSSONE_STATE::SEE_LEFT:
        if (m_bMoving)
        {
            if (m_eBossOneDirection == OBJECT_DIRECTION::DIR_LEFT)
            {
                if (m_dwTurnLeftTime + 1500 < GetTickCount64())
                {
                    m_eBossCurState = BOSSONE_STATE::ARM_SHAKE_LEFT;

                    m_pFrameKey = L"Boss1_Shaking_Left";
                }
            }
            else
            {
                if (m_dwTurnLeftTime + 1500 < GetTickCount64())
                {
                    m_eBossCurState = BOSSONE_STATE::ARM_SHAKE_LEFT;

                    m_pFrameKey = L"Boss1_Shaking_Right";
                }
            }
        }
        break;
    case CBossOne::BOSSONE_STATE::LONG:

        if (m_tFrame.iStart >= m_tFrame.iEnd - 1)
        {
            m_tFrame.iStart = m_tFrame.iEnd - 1;

            if (m_eBossOneDirection == OBJECT_DIRECTION::DIR_LEFT)
            {
                m_bGoBack = true;
            }
            else
            {
                m_bGoBack = true;
            }

            m_tFrame.iStart = 0;

            m_eBossCurState = BOSSONE_STATE::ARM_SHAKE_LEFT;

            if (m_eBossOneDirection == OBJECT_DIRECTION::DIR_LEFT)
                m_pFrameKey = L"Boss1_Shaking_Left";
            else
                m_pFrameKey = L"Boss1_Shaking_Right";

        }
        break;
    case CBossOne::BOSSONE_STATE::JUMP:
    {
       // BossOne_LeftJump();
    }
    break;
    case CBossOne::BOSSONE_STATE::GO_BACK:
        if (m_tInfo.fX <= 120.0f)
            m_tInfo.fX += 2.5f;
        else if (m_tInfo.fX >= 680.0f)
            m_tInfo.fX -= 2.5f;
        break;
    case CBossOne::BOSSONE_STATE::DEAD:
        break;
    case CBossOne::BOSSONE_STATE::END:
        break;
    default:
        break;
    }
}

void CBossOne::Create_Minions(OBJECT_DIRECTION _eDir)
{
    if (_eDir == OBJECT_DIRECTION::DIR_LEFT)
    {
        for (int i = 0; i < 2; ++i)
        {
            CObject* pTempMinionClass = new CMinions;

            pTempMinionClass->Initialize();

            pTempMinionClass->Set_Pos(50.0f + (i * 64), 20.0f);

            pTempMinionClass->Set_Direction(OBJECT_DIRECTION::DIR_LEFT);

            dynamic_cast<CMonster*>(pTempMinionClass)->Set_TargetPlayer(m_pTarget);

            CObjectManager::Get_Instance()->Add_Object(OBJECT_LIST::MINION, pTempMinionClass);
        }
    }
    else
    {
        for (int i = 0; i < 2; ++i)
        {
            CObject* pTempMinionClass = new CMinions;

            pTempMinionClass->Initialize();

            pTempMinionClass->Set_Pos(550.0f + (i * 64), 20.0f);

            pTempMinionClass->Set_Direction(OBJECT_DIRECTION::DIR_RIGHT);

            dynamic_cast<CMonster*>(pTempMinionClass)->Set_TargetPlayer(m_pTarget);

            CObjectManager::Get_Instance()->Add_Object(OBJECT_LIST::MINION, pTempMinionClass);
        }
    }

    /*list<CObject*>*/ /*MinionList = CObjectManager::Get_Instance()->Get_ObjectList(OBJECT_LIST::MINION);

    for (auto iter = MinionList.begin(); iter != MinionList.end(); ++iter)
    {
        dynamic_cast<CMonster*>(*iter)->Set_TargetPlayer(m_pTarget);
    }*/
}

void CBossOne::BossOne_MoveFrame()
{
    if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount64())
    {
        ++m_tFrame.iStart;

        if (m_tFrame.iStart > m_tFrame.iEnd)
            m_tFrame.iStart = 0;

        //While_Long_State();

        m_tFrame.dwTime = GetTickCount64();
    }

}

void CBossOne::BossOne_LeftJump()
{
    if (m_bBossJumpLeft)
    {
        // if (m_dwBossJumpTime + 5500 > GetTickCount64())

        if (m_bBossJumpLeftSide)
        {
            if (m_fGravityValue < 4.0f)
            {
                m_bFalling = true;
            }

            m_tInfo.fY -= m_fGravityValue;

            m_tInfo.fX -= 2.5f;

            m_fGravityValue -= 0.35f;

            if (m_tInfo.fX <= 120.0f)
            {
                //m_bBossJumpRightSide = true;
                 //m_bBossJumpLeftSide = false;

                m_eBossCurState = BOSSONE_STATE::GO_BACK;
            }

            //m_eBossCurState = BOSSONE_STATE::JUMP;

            if (m_eBossOneDirection == OBJECT_DIRECTION::DIR_LEFT)
                m_pFrameKey = L"Boss1_Shaking_Left";
        }
        if (m_bBossJumpRightSide)
        {
            if (m_fGravityValue < 4.0f)
            {
                m_bFalling = true;
            }

            m_tInfo.fY -= m_fGravityValue;

            m_tInfo.fX += 2.5f;

            m_fGravityValue -= 0.35f;

            if (m_tInfo.fX >= WINCX / 2.0f)
            {
                m_bBossJumpRightSide = false;

                m_bBossJumpLeft = false;

                m_eBossCurState = BOSSONE_STATE::IDLE;

                m_pFrameKey = L"Boss1_Idle";

                m_dwIdleTime = GetTickCount64();
            }
        }
    }
}

void CBossOne::BossOne_RightJump()
{
    if (m_bBossJumpRight)
    {
        if (m_dwBossJumpTime + 5500 > GetTickCount64())
        {
            if (m_bBossJumpRightSide)
            {
                if (m_fGravityValue < 4.0f)
                {
                    m_bFalling = true;
                }

                m_tInfo.fY -= m_fGravityValue;

                m_tInfo.fX += 2.5f;

                m_fGravityValue -= 0.35f;

                if (m_tInfo.fX >= 680.0f)
                {
                    m_bBossJumpLeftSide = true;
                    m_bBossJumpRightSide = false;
                }

                m_eBossCurState = BOSSONE_STATE::JUMP;

                if (m_eBossOneDirection == OBJECT_DIRECTION::DIR_RIGHT)
                    m_pFrameKey = L"Boss1_Shaking_Right";
            }
            else if (m_bBossJumpLeftSide)
            {
                if (m_fGravityValue < 4.0f)
                {
                    m_bFalling = true;
                }

                m_tInfo.fY -= m_fGravityValue;

                m_tInfo.fX -= 2.5f;

                m_fGravityValue -= 0.35f;

                if (m_tInfo.fX <= WINCX / 2.0f)
                {
                    m_bBossJumpLeftSide = false;

                    m_bBossJumpRight = false;

                    m_eBossCurState = BOSSONE_STATE::IDLE;

                    m_pFrameKey = L"Boss1_Idle";

                    m_dwIdleTime = GetTickCount64();
                }
            }
        }
    }
}

void CBossOne::Set_CurrentBossOneHp(float _fCurrentHp)
{
    m_fCurrentBossOneHp -= _fCurrentHp;

    if (m_fCurrentBossOneHp <= 0 && !m_bIsDeadOneTime)
    {
        CMapManager::Get_Instance()->Loading_Scene(CSceneManager::STAGE_ID::ST_02, 4);
        m_bIsDeadOneTime = true;
    }

    if (m_fCurrentBossOneHp <= 10.0f)
    {
        m_pHitedFrameKey = L"BossHitedEffect4";
    }

    else if (m_fCurrentBossOneHp <= 40.0f)
    {
        m_pHitedFrameKey = L"BossHitedEffect3";
    }
    else if (m_fCurrentBossOneHp <= 70.0f)
    {
        m_bBossGotHit = true;
        m_pHitedFrameKey = L"BossHitedEffect2";
    }

    

}

void CBossOne::Burn_OnFire()
{
    if (m_fCurrentBossOneHp <= 70.0f)
    {
        CEffectManager::Get_Instance()->Change_State(2);

        CEffectManager::Get_Instance()->Get_Effect_Pos(m_tInfo.fX + (m_iRandomFirePos * 10.0f), m_tInfo.fY);
    }
    if (m_fCurrentBossOneHp <= 40.0f)
    {
        CEffectManager::Get_Instance()->Get_Effect_Pos(m_tInfo.fX + (m_iRandomFirePos * 10.0f), m_tInfo.fY);
        CEffectManager::Get_Instance()->Get_Effect_Pos(m_tInfo.fX - (m_iRandomFirePos * 10.0f), m_tInfo.fY);
    }
}

void CBossOne::While_Long_State()
{
    if (m_eBossCurState == BOSSONE_STATE::LONG)
    {
        if (m_tFrame.iStart <= 8)
        {
            m_tInfo.fY -= 12.0f * m_tFrame.iStart;
        }
        else
        {
            m_tInfo.fY += 12.0f * (m_tFrame.iStart - 8);
        }
    }
}

