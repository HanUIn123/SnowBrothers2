#include "pch.h"
#include "Monster.h"
#include "SpawnManager.h"
#include "SoundMgr.h"

#include "ObjectManager.h"
#include "AbstractFactory.h"
#include "SpeedItem.h"
#include "PowerItem.h"
#include "RangeItem.h"
#include "PointItem.h"

CMonster::CMonster() : 
    m_eMonsterSnowState(MONSTER_SNOW_STATE::MS_END),
    m_iMaxSnowStat(0),
    m_iCollideCount(0),
    m_fGravityValue(16.0f),
    m_fTime(0),
    m_bSnow(false),
    m_bHited(false),
    m_bSnowBallMove(false),
    m_bMonsterJump(false),
    m_bMonsterWalk(false),
    m_bMonsterIdle(true),
    m_bSelected(false),
    m_bFalling(false),
    m_bWithPlayer(false),
    m_bBallRevMoving(false),
    m_bReadyToDie(false),
    m_bAfterLanding(false),
    m_bBossGotHit(false),
    m_bBossGotHit2(false),
    m_bItemCalled(false),
    m_eMonsterState(MONSTER_STATE::MS_END),
    m_eCurState(MONSTERONE_SNOW_STATE::IDLE),
    m_ePreState(MONSTERONE_SNOW_STATE::END),
    m_ePreBossState(BOSS_HITED_STATE::IDLE),
    m_eCurBossState(BOSS_HITED_STATE::END)
{
    m_fSnowBallSpeed = 10.0f;
    m_dwDieCoolTime = GetTickCount64();
}

CMonster::~CMonster()
{
}

void CMonster::Initialize()
{
}

int CMonster::Update()
{
    return 0;
}

void CMonster::Late_Update()
{
}

void CMonster::Render(HDC _hDC)
{
    TCHAR	szCount8[32] = L"";
    swprintf_s(szCount8, L"Collide_Count : %d", m_iCollideCount);
    TextOut(_hDC, 20, 300, szCount8, lstrlen(szCount8));
}

void CMonster::Release()
{
}


void CMonster::SnowBall_Roll()
{
    if (m_bSnowBallMove)
    {
        m_eCurState = MONSTERONE_SNOW_STATE::ROLL;

        if (0 > m_tRect.left || WINCX < m_tRect.right)
        {
            /* m_fSnowBallSpeed *= -1.0f;

             m_iCollideCount++;
             if (m_iCollideCount == 5)
             {
                 m_iMaxSnowStat = 0;
                 m_iCollideCount = 0;
                 m_bDead = true;
                 CSpawnManager::Get_Instance()->Decrease_MonsterCount(1);
                 m_bSnowBallMove = false;
             }*/

            m_iCollideCount++;
            CSoundMgr::Get_Instance()->PlaySound(L"SnowTurn.wav", SOUND_EFFECT, 1.0f);

            if (m_iCollideCount++)
            {
                m_fSnowBallSpeed *= -1.05f;

                if (m_iCollideCount >= 12)
                {
                    m_iMaxSnowStat = 0;
                    m_iCollideCount = 0;
                    m_bDead = true;
                    CSpawnManager::Get_Instance()->Decrease_MonsterCount(1);
                    m_bSnowBallMove = false;
                }
            }
        }
    }
}

void CMonster::Monster_Snow_Ani()
{
    if (m_ePreState != m_eCurState)
    {
        switch (m_eCurState)
        {
        case MONSTERONE_SNOW_STATE::ROLL:
            m_tSnowFrame.iStart = 0;
            m_tSnowFrame.iEnd = 2;
            m_tSnowFrame.iMotion = 0;
            m_tSnowFrame.dwSpeed = 50;
            m_tSnowFrame.dwTime = GetTickCount64();
            break;
        }
    }
    m_ePreState = m_eCurState;
}

void CMonster::Boss_Hited_Ani()
{
    if (m_ePreBossState != m_eCurBossState)
    {
        switch (m_eCurBossState)
        {
        case BOSS_HITED_STATE::BURN:
            m_tHitedFrame.iStart = 0;
            m_tHitedFrame.iEnd = 1;
            m_tHitedFrame.iMotion = 0;
            m_tHitedFrame.dwSpeed = 50;
            m_tHitedFrame.dwTime = GetTickCount64();
            break;
        }
    }
    m_ePreBossState = m_eCurBossState;
}

void CMonster::Snow_Move_Frame()
{
    if (m_tSnowFrame.dwTime + m_tSnowFrame.dwSpeed < GetTickCount64())
    {
        ++m_tSnowFrame.iStart;

        if (m_tSnowFrame.iStart > m_tSnowFrame.iEnd)
            m_tSnowFrame.iStart = 0;

        m_tSnowFrame.dwTime = GetTickCount64();
    }
}

void CMonster::Hited_Move_Frame()
{
    if (m_tHitedFrame.dwTime + m_tHitedFrame.dwSpeed < GetTickCount64())
    {
        ++m_tHitedFrame.iStart;

        if (m_tHitedFrame.iStart > m_tHitedFrame.iEnd)
            m_tHitedFrame.iStart = 0;

        m_tHitedFrame.dwTime = GetTickCount64();
    }
}

void CMonster::GotHit()
{
    if (m_bBossGotHit || m_bBossGotHit2)
    {
        m_eCurBossState = BOSS_HITED_STATE::BURN;
    }
}



