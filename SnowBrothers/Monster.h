#pragma once
#include "Object.h"

class CMonster : public CObject
{
public:
    enum class MONSTERONE_SNOW_STATE { IDLE, ROLL, END };
    enum class BOSS_HITED_STATE { IDLE, BURN, END};
public:
    CMonster();
    virtual ~CMonster();

public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC _hDC) override;
    virtual void Release() override;


    float Get_Gravity() { return m_fGravityValue; }
    void Set_GrvityValue(float _fGravity) { m_fGravityValue = _fGravity; }

    void Set_fTime() { m_fTime = 0.0f; }



public:
    MONSTER_SNOW_STATE   Get_MonsterState() { return m_eMonsterSnowState; }
    void            Set_MonsterState(MONSTER_SNOW_STATE _eMonsterState) { m_eMonsterSnowState = _eMonsterState; }

    int             Get_SnowStat() { return m_iMaxSnowStat; }
    void            Set_SnowStat(int _iSnowStat)
    {
        m_iMaxSnowStat += _iSnowStat;

        if (m_iMaxSnowStat > (UINT)MONSTER_SNOW_STATE::MS_END)
        {
            m_iMaxSnowStat = (UINT)MONSTER_SNOW_STATE::MS_END;
        }
    }


    bool Get_Hited() { return m_bHited; }
    void Set_Hited(bool _bHited) { m_bHited = _bHited; }


    bool Get_Selected() { return m_bSelected; }
    void Set_Selected(bool _bSelected) { m_bSelected = _bSelected; }


    bool Get_Jump() { return m_bMonsterJump; }
    void Set_JumpFalse() { m_bMonsterJump = false; }


    bool Get_Falling() { return m_bFalling; }
    void Set_FallingFalse() { m_bFalling = false; }
    void Set_FallingTrue() { m_bFalling = true; }

    void Set_TargetPlayer(CObject* _pTarget)
    {
        m_pTarget = _pTarget;
    }


    bool Get_SnowBallMove() { return m_bSnowBallMove; }
    void Set_SnowBallMove(bool _bSnowBallMove) { m_bSnowBallMove = _bSnowBallMove; }

    bool Get_WithPlayer() { return m_bWithPlayer; }
    void Set_WithPlayer(bool _bWithPlayer) { m_bWithPlayer = _bWithPlayer; }


    int Get_CollideCount() { return m_iCollideCount; }
    void Set_CollideCount(int _iCollideCount) { m_iCollideCount = _iCollideCount; }


    bool Get_RevMoving() { return m_bBallRevMoving; }
    void Set_RevMoving(bool _bRevMoving) { m_bBallRevMoving = _bRevMoving; }


    bool Get_ReadyToDie() { return m_bReadyToDie; }
    virtual void Set_ReadyToDie(bool _bReadyToDie) { m_bReadyToDie = _bReadyToDie;  m_dwDieCoolTime = GetTickCount64(); };

    bool Get_Landing() { return m_bAfterLanding; }
    void Set_Landing(bool _bLanding) { m_bAfterLanding = _bLanding; }
    

    void SnowBall_Roll();

    void Set_TobeRoll()
    {
        float fDistanceWithTargetX(0.0f);
        float fDistanceWithTargetY(0.0f);

        fDistanceWithTargetX = abs(m_pTarget->Get_ObjectInfo().fX - this->Get_ObjectInfo().fX);
        fDistanceWithTargetY = abs(m_pTarget->Get_ObjectInfo().fY - this->Get_ObjectInfo().fY);

        if (m_iMaxSnowStat == (UINT)MONSTER_SNOW_STATE::MS_END && (m_pTarget->Get_CanKick() == true)
            && fDistanceWithTargetX < 66.0f && fDistanceWithTargetY < 66.0f)
        {
            m_bSnowBallMove = true;
        }
    }

    void Monster_Snow_Ani();

    void Boss_Hited_Ani();



    void		Snow_Move_Frame();


    void        Hited_Move_Frame();

    bool Get_BossGotHit() { return m_bBossGotHit; }
    void Set_BossGotHit(bool _bBossGotHit) { m_bBossGotHit = _bBossGotHit; }



public:
    MONSTER_SNOW_STATE   m_eMonsterSnowState;
    MONSTER_STATE        m_eMonsterState;


    int             m_iMaxSnowStat;
    bool            m_bSnow;


    bool            m_bHited;

    float           m_fGravityValue;



    float           m_fTime;




    bool            m_bSnowBallMove;


    void            GotHit();

protected:
    bool            m_bMonsterJump;
    bool            m_bMonsterWalk;
    bool            m_bMonsterIdle;


    bool            m_bSelected;




    int             m_iCollideCount;


    bool            m_bFalling;



    bool            m_bWithPlayer;




    bool            m_bBallRevMoving;



    MONSTERONE_SNOW_STATE    m_eCurState;
    MONSTERONE_SNOW_STATE    m_ePreState;
    BOSS_HITED_STATE        m_ePreBossState;
    BOSS_HITED_STATE        m_eCurBossState;




    bool            m_bReadyToDie;

    ULONGLONG       m_dwDieCoolTime;

    bool            m_bAfterLanding;


    bool            m_bBossGotHit;
    bool            m_bBossGotHit2;


    bool            m_bItemCalled;
};

