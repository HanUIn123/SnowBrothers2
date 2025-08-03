#include "pch.h"
#include "Player.h"
#include "Bullet.h"
#include "BmpManager.h"
#include "KeyManager.h"
#include "ObjectManager.h"
#include "LineManager.h"
#include "SoundMgr.h"
#include "EffectManager.h"
#include "UiManager.h"

CPlayer::CPlayer() :
    m_bJump(false),
    m_bDownJump(false),
    m_bRunning(false),
    m_bWalking(false),
    m_isLookingDown(false),
    m_bFalling(false),
    m_bShoot(false),
    m_bCanPush(false),
    m_bSpeedUp(false),
    m_bBulletUpgraded(false),
    m_bRealPush(false),
    m_bCanRollwithSnow(false),
    m_bSuperMode(false),
    m_bIsOnSnow(false),
    m_bRanged(false),
    m_bBeforeDie(false),
    m_bUnlimitedSuperMode(false),
    //m_bCanKick(false),
    m_dwShootingTime(GetTickCount64()),
    m_fPower(0.0f),
    m_fTime(0.0f),
    m_iTickCount(0),
    m_iExampleCount(0),
    m_fJumpPower(16.5f),
    m_iLife(5),
    m_eCurState(PLAYER_STATE::IDLE),
    m_ePreState(PLAYER_STATE::END)
    //m_ePlayerDirection(OBJECT_DIRECTION::DIR_RIGHT)
{
    m_pCollisionName = L"TOM";

    m_dwDownJumpTime = GetTickCount64();

    m_eDir = OBJECT_DIRECTION::DIR_RIGHT;

    m_dwSuperTime = GetTickCount64();

    m_dwPlayerDieCoolTime = GetTickCount64();
}

CPlayer::~CPlayer()
{
    Release();
}

void CPlayer::Initialize()
{
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_Idle_left.bmp", L"Player_Idle_Left");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_Idle_right.bmp", L"Player_Idle_Right");

    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_Walk_left.bmp", L"Player_Walk_Left");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_Walk_right.bmp", L"Player_Walk_Right");

    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_Run_Left.bmp", L"Player_Run_Left");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_Run_Right.bmp", L"Player_Run_Right");

    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_Jump_Left.bmp", L"Player_Jump_Left");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_Jump_Right.bmp", L"Player_Jump_Right");

    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_Shoot_Right.bmp", L"Player_Shoot_Right");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_Shoot_Left.bmp", L"Player_Shoot_Left");

    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_push_Left.bmp", L"Player_Push_Left");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_push_Right.bmp", L"Player_Push_Right");

    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_Kick_Left2.bmp", L"Player_Kick_Left");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_Kick_Right2.bmp", L"Player_Kick_Right");


    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_Falling_Right.bmp", L"Player_Falling_Right");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_Falling_Left.bmp", L"Player_Falling_Left");

    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_Super_right.bmp", L"Player_Super_right");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_Super_left.bmp", L"Player_Super_left");

    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_SuperWalk_right.bmp", L"Player_SuperWalk_right");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_SuperWalk_left.bmp", L"Player_SuperWalk_left");

    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_dead.bmp", L"Player_Dead");

    //m_eDir = m_ePlayerDirection;

    m_tInfo = { 100.f, WINCY / 2.f, 64, 64 };

    m_fSpeed = 2.5f;

    m_fDistance = 100.f;

    m_fPower = 20.f;

    m_pFrameKey = L"Player_Idle_Left";

    m_tFrame = { 0,0,0,100,GetTickCount64() };

    m_fAccel = 10.f;
    m_fJumpAccel = 20.f;

    m_bLookingRight = true;
}

int CPlayer::Update()
{
    if (m_bDead)
        return (UINT)OBJECT_STATE::OBJ_DEAD;

    m_tInfo.fY += 7.0f;

    //if ((m_tInfo.fX < WINCX - 10 && m_tInfo.fX > 10) &&
    //    (m_tInfo.fY < WINCY - 10 && m_tInfo.fY > 10))
    //{
    //    Player_FSM();
    //    Shoot();


    //    Kick();
    //}
    //else
    //{
    //    if (m_tInfo.fX > 10)
    //        m_tInfo.fX = WINCX - 20;
    //    else if (m_tInfo.fX < WINCX - 10)
    //        m_tInfo.fX = 20;
    //}

    if (CKeyManager::Get_Instance()->Key_Down('V'))
    {
        //m_bUnlimitedSuperMode = true;
    }

    if (!m_bBeforeDie)
    {
        Player_FSM();
        Shoot();
        Kick();
    }
    else
    {   
       /* m_pFrameKey = L"Player_Dead";
        m_eCurState = PLAYER_STATE::DEAD;*/


        if (m_eCurState != PLAYER_STATE::DEAD)  //  DEAD 상태로 바뀌는 '순간'만 실행
        {
            m_dwPlayerDieCoolTime = GetTickCount64();  //  타이머 갱신은 딱 한 번만
            m_pFrameKey = L"Player_Dead";
            m_eCurState = PLAYER_STATE::DEAD;

            m_tFrame.iStart = 0; //  애니메이션 재생 초기화
            m_tFrame.iEnd = 6;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 70;
            m_tFrame.dwTime = GetTickCount64();
        }
    }

  /*  if (m_eCurState == PLAYER_STATE::DEAD)
    {
        if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount64())
        {
            ++m_tFrame.iStart;

            if (m_tFrame.iStart >= m_tFrame.iEnd)
            {
                m_tFrame.iStart = m_tFrame.iEnd;
            }
            m_tFrame.dwTime = GetTickCount64();;
        }
        if (m_dwPlayerDieCoolTime + 500 < GetTickCount64())
        {
            m_bSuperMode = true;
            m_bBeforeDie = false;

            m_iLife -= 1;



            m_fSpeed = 2.5f;
            m_bBulletUpgraded = false;
            m_bRanged = false;


            m_tInfo.fX = 100.0f;
            m_tInfo.fY = 550.0f;


            m_eCurState = PLAYER_STATE::SUPER;
            m_pFrameKey = L"Player_Super_right";
        }
    }*/


    if (m_eCurState == PLAYER_STATE::DEAD)
    {
        // 죽는 애니메이션 재생
        if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount64())
        {
            ++m_tFrame.iStart;

            if (m_tFrame.iStart >= m_tFrame.iEnd)
                m_tFrame.iStart = m_tFrame.iEnd;

            m_tFrame.dwTime = GetTickCount64();
        }

        //  부활까지의 시간 늘려줌: 1500ms
        if (m_dwPlayerDieCoolTime + 1000 < GetTickCount64())
        {
            m_bSuperMode = true;
            m_bBeforeDie = false;
            m_iLife -= 1;

            m_fSpeed = 2.5f;
            m_bBulletUpgraded = false;
            m_bRanged = false;

            m_tInfo.fX = 100.0f;
            m_tInfo.fY = 550.0f;

            m_eCurState = PLAYER_STATE::SUPER;
            m_pFrameKey = L"Player_Super_right";
            m_dwSuperTime = GetTickCount64(); // ← SUPER 상태 타이머 갱신
            m_dwInvincibleStartTime = GetTickCount64(); // ← 무적 타이머 갱신
            //  죽을 때마다 타이머 갱신되게끔 막음
            //m_dwPlayerDieCoolTime = GetTickCount64();  // <- 이건 여기 말고 "죽는 순간"에 설정해야 함
        }
    }

    CUiManager::Get_Instance()->Set_PlayerLifeCount(m_iLife);

    __super::Update_Rect();

    return (UINT)OBJECT_STATE::OBJ_NOEVENT;
}

void CPlayer::Late_Update()
{
    if (m_fSpeed >= 4.5f)
        m_bSpeedUp = true;
    else
        m_bSpeedUp = false;

    if (m_bCanRollwithSnow)
    {
        dynamic_cast<CMonster*>(m_pTarget)->Set_WithPlayer(true);
        m_tInfo.fX = m_pTarget->Get_ObjectInfo().fX;
        m_tInfo.fY = m_pTarget->Get_ObjectInfo().fY;
    }

    if (CKeyManager::Get_Instance()->Key_Down('F'))
    {
        m_bSuperMode = true;
        m_bCanRollwithSnow = false;

        if (m_pTarget != nullptr)
        {
            dynamic_cast<CMonster*>(m_pTarget)->Set_WithPlayer(false);
            m_tInfo.fX = m_pTarget->Get_ObjectInfo().fX;
            m_tInfo.fY = m_pTarget->Get_ObjectInfo().fY - 80.0f;
        }
    }

    if (m_bSuperMode)
    {
        if (CKeyManager::Get_Instance()->Key_Pressing(VK_RIGHT))
        {
            m_bWalking = true;
            m_eCurState = PLAYER_STATE::WALK;
            m_eDir = OBJECT_DIRECTION::DIR_RIGHT;
            m_pFrameKey = L"Player_SuperWalk_right";
        }
        else if (CKeyManager::Get_Instance()->Key_Up(VK_RIGHT))
        {
            m_pFrameKey = L"Player_Super_right";
        }

        if (CKeyManager::Get_Instance()->Key_Pressing(VK_LEFT))
        {
            m_bWalking = true;
            m_eCurState = PLAYER_STATE::WALK;
            m_eDir = OBJECT_DIRECTION::DIR_LEFT;
            m_pFrameKey = L"Player_SuperWalk_left";
        }
        else if (CKeyManager::Get_Instance()->Key_Up(VK_RIGHT))
        {
            m_pFrameKey = L"Player_Super_left";
        }
    }

    if (m_dwSuperTime + 4500 < GetTickCount64())
    {
        m_bSuperMode = false;
        m_dwSuperTime = GetTickCount64();
    }

    Player_Animation();
    Jump2();
    Push_Snow();

    CObject::Move_Frame();
}

void CPlayer::Render(HDC _hDC)
{
    HDC	hMemDC = CBmpManager::Get_Instance()->Find_Img(m_pFrameKey);

    //Rectangle(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

    if (!m_bCanRollwithSnow)
    {
        GdiTransparentBlt(_hDC,
            int(m_tRect.left),
            int(m_tRect.top),
            int(64),
            int(64),
            hMemDC,
            int(m_tInfo.fCX * m_tFrame.iStart),
            int(m_tInfo.fCY * m_tFrame.iMotion),
            int(m_tInfo.fCX),
            int(m_tInfo.fCY),
            RGB(255, 0, 255));
    }

    //      0        1           2       3       4       5       6
    //  DIR_LEFT, DIR_RIGHT, DIR_UP, DIR_DOWN, DIR_LU, DIR_RU, DIR_END
    //Text_Render(_hDC);
}

void CPlayer::Release()
{
}

void CPlayer::Offset()
{
}

void CPlayer::Player_FSM()
{
    m_isLookingDown = CKeyManager::Get_Instance()->Key_Pressing(VK_DOWN) ? true : false;

    if (!m_bSpeedUp || m_bSpeedUp)
    {
        switch (m_eCurState)
        {
        case CPlayer::PLAYER_STATE::IDLE:
        {
            m_bCanPush = false;
            m_bJump = false;
            m_bCanKick = false;
            //m_bDownJump = false;

            if (!m_bSpeedUp)
            {
                if (CKeyManager::Get_Instance()->Key_Pressing(VK_RIGHT))
                {
                    m_bWalking = true;
                    m_eCurState = PLAYER_STATE::WALK;
                    m_eDir = OBJECT_DIRECTION::DIR_RIGHT;
                    m_pFrameKey = L"Player_Walk_Right";
                }
                else if (CKeyManager::Get_Instance()->Key_Pressing(VK_LEFT))
                {
                    m_bWalking = true;
                    m_eCurState = PLAYER_STATE::WALK;
                    m_eDir = OBJECT_DIRECTION::DIR_LEFT;
                    m_pFrameKey = L"Player_Walk_Left";
                }
            }
            else
            {
                if (CKeyManager::Get_Instance()->Key_Pressing(VK_RIGHT))
                {
                    m_bWalking = true;
                    m_eCurState = PLAYER_STATE::WALK;
                    m_eDir = OBJECT_DIRECTION::DIR_RIGHT;
                    m_pFrameKey = L"Player_Run_Right";
                }
                else if (CKeyManager::Get_Instance()->Key_Pressing(VK_LEFT))
                {
                    m_bWalking = true;
                    m_eCurState = PLAYER_STATE::WALK;
                    m_eDir = OBJECT_DIRECTION::DIR_LEFT;
                    m_pFrameKey = L"Player_Run_Left";
                }
            }

            if (CKeyManager::Get_Instance()->Key_Pressing('A'))
            {
                m_bWalking = false;
                m_bShoot = true;
                if ((UINT)m_eDir == (UINT)OBJECT_DIRECTION::DIR_RIGHT)
                {
                    m_eCurState = PLAYER_STATE::SHOOT;
                    m_pFrameKey = L"Player_Shoot_Right";
                }
                else if ((UINT)m_eDir == (UINT)OBJECT_DIRECTION::DIR_LEFT)
                {
                    m_eCurState = PLAYER_STATE::SHOOT;
                    m_pFrameKey = L"Player_Shoot_Left";
                }
            }

            /*if (CKeyManager::Get_Instance()->Key_Down('D'))
            {
               CSoundMgr::Get_Instance()->PlaySound(L"Player_Jump.wav", SOUND_EFFECT, 1.0f);

                if (!m_isLookingDown)
                {
                    m_bJump = true;

                    m_eCurState = PLAYER_STATE::JUMP;
                    if ((UINT)m_eDir == (UINT)OBJECT_DIRECTION::DIR_RIGHT)
                    {
                        m_pFrameKey = L"Player_Jump_Right";
                    }
                    else if ((UINT)m_eDir == (UINT)OBJECT_DIRECTION::DIR_LEFT)
                    {
                        m_pFrameKey = L"Player_Jump_Left";
                    }
                }
                else
                {
                    m_bDownJump = true;

                    m_eCurState = PLAYER_STATE::JUMP;
                    if ((UINT)m_eDir == (UINT)OBJECT_DIRECTION::DIR_RIGHT)
                        m_pFrameKey = L"Player_Jump_Right";
                    else
                        m_pFrameKey = L"Player_Jump_Left";
                }
            }*/

            // 아래키 + D키 동시 입력이면 DownJump 먼저 처리
            if (CKeyManager::Get_Instance()->Key_Pressing(VK_DOWN) && CKeyManager::Get_Instance()->Key_Down('D'))
            {
                CSoundMgr::Get_Instance()->PlaySound(L"Player_Jump.wav", SOUND_EFFECT, 1.0f);

                m_bDownJump = true;
                m_eCurState = PLAYER_STATE::JUMP;

                if (m_eDir == OBJECT_DIRECTION::DIR_RIGHT)
                    m_pFrameKey = L"Player_Jump_Right";
                else
                    m_pFrameKey = L"Player_Jump_Left";
            }
            else if (CKeyManager::Get_Instance()->Key_Down('D'))
            {
                CSoundMgr::Get_Instance()->PlaySound(L"Player_Jump.wav", SOUND_EFFECT, 1.0f);

                m_bJump = true;
                m_eCurState = PLAYER_STATE::JUMP;

                if (m_eDir == OBJECT_DIRECTION::DIR_RIGHT)
                    m_pFrameKey = L"Player_Jump_Right";
                else
                    m_pFrameKey = L"Player_Jump_Left";
            }


            if (m_dwDownJumpTime + 500 < GetTickCount64())
            {
                m_bDownJump = false;
                m_dwDownJumpTime = GetTickCount64();
            }
        }
        break;



        case CPlayer::PLAYER_STATE::WALK:
        {
            m_bJump = false;

            if (m_eDir == OBJECT_DIRECTION::DIR_RIGHT)
                m_tInfo.fX += m_fSpeed;
            else if (m_eDir == OBJECT_DIRECTION::DIR_LEFT)
                m_tInfo.fX -= m_fSpeed;

            if ((m_eCurState == PLAYER_STATE::WALK && CKeyManager::Get_Instance()->Key_Down('A')) || CKeyManager::Get_Instance()->Key_Down('A'))
            {
                m_bShoot = true;

                if ((UINT)m_eDir == (UINT)OBJECT_DIRECTION::DIR_RIGHT)
                {
                    m_eCurState = PLAYER_STATE::SHOOT;
                    m_pFrameKey = L"Player_Shoot_Right";
                }

                else if ((UINT)m_eDir == (UINT)OBJECT_DIRECTION::DIR_LEFT)
                {
                    m_eCurState = PLAYER_STATE::SHOOT;
                    m_pFrameKey = L"Player_Shoot_Left";
                }
            }

            if (CKeyManager::Get_Instance()->Key_Up(VK_RIGHT))
            {
                m_bWalking = false;
                m_eCurState = PLAYER_STATE::IDLE;
                m_pFrameKey = L"Player_Idle_Right";
            }
            else if (CKeyManager::Get_Instance()->Key_Up(VK_LEFT))
            {
                m_bWalking = false;
                m_eCurState = PLAYER_STATE::IDLE;
                m_pFrameKey = L"Player_Idle_Left";
            }


            if (CKeyManager::Get_Instance()->Key_Down('D'))
            {
                CSoundMgr::Get_Instance()->PlaySound(L"Player_Jump.wav", SOUND_EFFECT, 1.0f);
                if (!m_isLookingDown)
                {
                    m_bJump = true;

                    m_eCurState = PLAYER_STATE::JUMP;

                    if ((UINT)m_eDir == (UINT)OBJECT_DIRECTION::DIR_RIGHT)
                    {
                        m_pFrameKey = L"Player_Jump_Right";

                    }
                    else if ((UINT)m_eDir == (UINT)OBJECT_DIRECTION::DIR_LEFT)
                    {

                        m_pFrameKey = L"Player_Jump_Left";
                    }
                }
                else
                {
                    m_bDownJump = true;

                    m_eCurState = PLAYER_STATE::JUMP;

                    if ((UINT)m_eDir == (UINT)OBJECT_DIRECTION::DIR_RIGHT)
                        m_pFrameKey = L"Player_Jump_Right";
                    else
                        m_pFrameKey = L"Player_Jump_Left";
                }
            }

        }
        break;

        case CPlayer::PLAYER_STATE::SHOOT:
        {
            if (CKeyManager::Get_Instance()->Key_Up('A'))
            {
                m_bShoot = false;

                if ((UINT)m_eDir == (UINT)OBJECT_DIRECTION::DIR_RIGHT)
                {
                    m_eCurState = PLAYER_STATE::IDLE;
                    m_pFrameKey = L"Player_Idle_Right";
                }
                else if ((UINT)m_eDir == (UINT)OBJECT_DIRECTION::DIR_LEFT)
                {
                    m_eCurState = PLAYER_STATE::IDLE;
                    m_pFrameKey = L"Player_Idle_Left";
                }
            }
        }
        break;
        case CPlayer::PLAYER_STATE::JUMP:
        {
            if (m_bJump == false)
            {
                if ((UINT)m_eDir == (UINT)OBJECT_DIRECTION::DIR_RIGHT)
                {
                    m_eCurState = PLAYER_STATE::IDLE;
                    m_pFrameKey = L"Player_Idle_Right";
                }
                else if ((UINT)m_eDir == (UINT)OBJECT_DIRECTION::DIR_LEFT)
                {
                    m_eCurState = PLAYER_STATE::IDLE;
                    m_pFrameKey = L"Player_Idle_Left";
                }
            }
            else
            {
                if (CKeyManager::Get_Instance()->Key_Pressing(VK_RIGHT))
                {
                    m_tInfo.fX += m_fSpeed;
                }
                else if (CKeyManager::Get_Instance()->Key_Pressing(VK_LEFT))
                {
                    m_tInfo.fX -= m_fSpeed;
                }
            }
        }
        break;
        case CPlayer::PLAYER_STATE::PUSH:
        {
            if ((UINT)m_eDir == (UINT)OBJECT_DIRECTION::DIR_RIGHT)
            {

                if (CKeyManager::Get_Instance()->Key_Pressing(VK_RIGHT))
                {
                    m_pFrameKey = L"Player_Push_Right";
                    m_tInfo.fX += 1.5f;

                }
                else
                {
                    m_tInfo.fX -= 0.5f;

                    m_eCurState = PLAYER_STATE::IDLE;
                    m_pFrameKey = L"Player_Idle_Right";
                    m_bCanPush = false;
                }

            }
            else if ((UINT)m_eDir == (UINT)OBJECT_DIRECTION::DIR_LEFT)
            {
                if (CKeyManager::Get_Instance()->Key_Pressing(VK_LEFT))
                {
                    m_pFrameKey = L"Player_Push_Left";
                    m_tInfo.fX -= 1.5f;
                }
                else
                {
                    m_tInfo.fX += 0.5f;

                    m_eCurState = PLAYER_STATE::IDLE;
                    m_pFrameKey = L"Player_Idle_Left";
                    m_bCanPush = false;
                }
            }
        }
        break;
        case CPlayer::PLAYER_STATE::KICK:
        {
            if ((UINT)m_eDir == (UINT)OBJECT_DIRECTION::DIR_RIGHT)
            {
                m_eCurState = PLAYER_STATE::IDLE;
                m_pFrameKey = L"Player_Idle_Right";
            }
            else if ((UINT)m_eDir == (UINT)OBJECT_DIRECTION::DIR_LEFT)
            {
                m_eCurState = PLAYER_STATE::IDLE;
                m_pFrameKey = L"Player_Idle_Left";
            }
        }
        break;
        case CPlayer::PLAYER_STATE::FALLING:
        {
            if (!m_bFalling)
            {
                if ((UINT)m_eDir == (UINT)OBJECT_DIRECTION::DIR_RIGHT)
                {
                    m_eCurState = PLAYER_STATE::IDLE;
                    m_pFrameKey = L"Player_Idle_Right";
                }
                else if ((UINT)m_eDir == (UINT)OBJECT_DIRECTION::DIR_LEFT)
                {
                    m_eCurState = PLAYER_STATE::IDLE;
                    m_pFrameKey = L"Player_Idle_Left";
                }
            }
        }
        break;
        case CPlayer::PLAYER_STATE::SUPER:
        {
        }
        break;
        }


    }
}

void CPlayer::Jump()
{
    float fY(0.0f);
    float fX(0.0f);
    bool bLineCollide = CLineManager::Get_Instance()->Collision_Line(m_tInfo.fX, m_tInfo.fY, &fY);

    if (m_bDownJump)
    {
        bLineCollide = false;
        m_tInfo.fY -= -(3.0f);
        m_fTime += 0.15f;

        if (fY < m_tInfo.fY + 10.0f && m_fTime > 5.0f)
        {
            bLineCollide = true;
            m_bDownJump = false;
        }
    }
    else
        bLineCollide = true;

    if (m_bJump)
    {
        m_bSpeedUp = false;
        m_tInfo.fY -= (m_fPower - (9.8f * m_fTime));
        m_fTime += 0.15f;

        if (bLineCollide && (fY < m_tInfo.fY))
        {
            m_bJump = false;
            m_bFalling = false;
            m_fTime = 0.0f;

            m_tInfo.fY = fY - (m_tInfo.fCY * 0.5f);
            m_pFrameKey = L"Player_Idle_Left";
            m_eCurState = PLAYER_STATE::IDLE;
        }
    }
    else if (bLineCollide)
    {
        m_tInfo.fY = fY - (m_tInfo.fCY * 0.5f);
    }
}

void CPlayer::Jump2()
{
    if (m_bDownJump)
    {
        m_tInfo.fY -= 3.0f;
    }


    if (m_bJump)
    {
        if (m_fJumpPower < 7.0f)
        {
            m_bFalling = true;

            m_bJump = false;
        }

        m_tInfo.fY -= m_fJumpPower;

        m_fJumpPower -= 0.45f;


        if (CKeyManager::Get_Instance()->Key_Down('A'))
        {
            m_bShoot = true;

            if ((UINT)m_eDir == (UINT)OBJECT_DIRECTION::DIR_RIGHT)
            {
                m_eCurState = PLAYER_STATE::SHOOT;
                m_pFrameKey = L"Player_Shoot_Right";
            }
            else if ((UINT)m_eDir == (UINT)OBJECT_DIRECTION::DIR_LEFT)
            {
                m_eCurState = PLAYER_STATE::SHOOT;
                m_pFrameKey = L"Player_Shoot_Left";
            }
        }

    }
}

void CPlayer::Player_Animation()
{
    if (m_ePreState != m_eCurState)
    {
        switch (m_eCurState)
        {
        case PLAYER_STATE::IDLE:
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 0;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 200;
            m_tFrame.dwTime = GetTickCount64();
            break;

        case PLAYER_STATE::WALK:
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 2;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 50;
            m_tFrame.dwTime = GetTickCount64();
            break;

        case PLAYER_STATE::JUMP:
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 6;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 35;
            m_tFrame.dwTime = GetTickCount64();
            break;

        case PLAYER_STATE::SHOOT:
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 2;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 20;
            m_tFrame.dwTime = GetTickCount64();
            break;

        case PLAYER_STATE::DEAD:
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 6;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 70;
            m_tFrame.dwTime = GetTickCount64();
            break;

        case PLAYER_STATE::PUSH:
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 2;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 30;
            m_tFrame.dwTime = GetTickCount64();
            break;
        case PLAYER_STATE::FALLING:
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 0;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 30;
            m_tFrame.dwTime = GetTickCount64();
            break;
        case PLAYER_STATE::KICK:
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 2;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 60;
            m_tFrame.dwTime = GetTickCount64();
            break;
        case PLAYER_STATE::SUPER:
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 2;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 40;
            m_tFrame.dwTime = GetTickCount64();
            break;
        }
    }
    m_ePreState = m_eCurState;
}

void CPlayer::Shoot()
{
    if (m_bShoot && ((UINT)m_eDir == (UINT)OBJECT_DIRECTION::DIR_RIGHT))
    {
        if (m_dwShootingTime + 250 < GetTickCount64())
        {
            Create_Bullet(OBJECT_DIRECTION::DIR_RIGHT, m_bBulletUpgraded);

            m_dwShootingTime = GetTickCount64();
        }
    }
    if (m_bShoot && ((UINT)m_eDir == (UINT)OBJECT_DIRECTION::DIR_LEFT))
    {
        if (m_dwShootingTime + 250 < GetTickCount64())
        {
            Create_Bullet(OBJECT_DIRECTION::DIR_LEFT, m_bBulletUpgraded);

            m_dwShootingTime = GetTickCount64();
        }
    }
}

void CPlayer::Kick()
{
    if (CKeyManager::Get_Instance()->Key_Down('S') && m_bCanPush)
    {
        CSoundMgr::Get_Instance()->PlaySound(L"SnowKick.wav", SOUND_EFFECT, 1.0f);
        m_bCanKick = true;

        m_eCurState = PLAYER_STATE::KICK;

        m_pTarget->Set_Direction(m_eDir);
    }
}

void CPlayer::Push_Snow()
{
    if (m_bCanPush)
    {
        m_bShoot = false;

        m_eCurState = PLAYER_STATE::PUSH;
    }
}

void CPlayer::Text_Render(HDC _hDC)
{
    TCHAR	szCount[32] = L"";
    swprintf_s(szCount, L"m_bBeforeDie : %d", (UINT)m_bBeforeDie);
    TextOut(_hDC, 20, 20, szCount, lstrlen(szCount));

    // IDLE, WALK, RUN, JUMP, PUSH, SHOOT, KICK, DEAD, END
    TCHAR	szCount2[32] = L"";
    swprintf_s(szCount2, L"PLAYER_DOWNJUMP : %d", (UINT)m_bDownJump);
    TextOut(_hDC, 20, 220, szCount2, lstrlen(szCount2));

    TCHAR	szCount3[32] = L"";
    swprintf_s(szCount3, L"PLAYER_FALLING : %d", (UINT)m_bFalling);
    TextOut(_hDC, 20, 60, szCount3, lstrlen(szCount3));

    TCHAR	szCount4[32] = L"";
    swprintf_s(szCount4, L"IS_SUPERMODE : %d", (UINT)m_bSuperMode);
    TextOut(_hDC, 20, 80, szCount4, lstrlen(szCount4));

    TCHAR	szCount5[32] = L"";
    swprintf_s(szCount5, L"IS_ROLLING : %d", m_bCanRollwithSnow);
    TextOut(_hDC, 20, 120, szCount5, lstrlen(szCount5));

    TCHAR	szCount6[32] = L"";
    swprintf_s(szCount6, L"IS_PUSHING : %d", m_bCanPush);
    TextOut(_hDC, 20, 140, szCount6, lstrlen(szCount6));

    TCHAR	szCount7[32] = L"";
    swprintf_s(szCount7, L"PLAYER X : %d", (int)m_tInfo.fX);
    TextOut(_hDC, 20, 160, szCount7, lstrlen(szCount7));

    TCHAR	szCount9[32] = L"";
    swprintf_s(szCount9, L"IS_ONTOP : %d", m_bSuperMode);
    TextOut(_hDC, 20, 200, szCount9, lstrlen(szCount9));
}

CObject* CPlayer::Create_Bullet(OBJECT_DIRECTION _eDirection, bool _bUpgraded)
{
    CObject* pBullet = new CBullet;

    pBullet->Initialize();

    CSoundMgr::Get_Instance()->PlaySound(L"Player_Shoot3.wav", SOUND_EFFECT, 1.0f);

    pBullet->Set_Direction(_eDirection);

    pBullet->Set_BulletUpgrade(_bUpgraded);

    if (_eDirection == OBJECT_DIRECTION::DIR_LEFT)
    {
        if (_bUpgraded == false)
        {
            pBullet->Set_Pos(m_tInfo.fX - m_tInfo.fCX * 0.5f, m_tInfo.fY - 15.0f);
        }
        else
        {
            pBullet->Set_Pos(m_tInfo.fX - m_tInfo.fCX * 0.5f, m_tInfo.fY - 15.0f);
        }
    }

    if (_eDirection == OBJECT_DIRECTION::DIR_RIGHT)
    {
        if (_bUpgraded == false)
        {
            pBullet->Set_Pos(m_tInfo.fX + m_tInfo.fCX * 0.5f, m_tInfo.fY - 15.0f);
        }
        else
        {
            pBullet->Set_Pos(m_tInfo.fX + m_tInfo.fCX * 0.5f, m_tInfo.fY - 15.0f);
        }
    }

    CObjectManager::Get_Instance()->Add_Object(OBJECT_LIST::BULLET, pBullet);

    m_iExampleCount += 1;

    return pBullet;
}

