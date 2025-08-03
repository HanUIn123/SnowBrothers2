#pragma once
#include "Monster.h"
class CBossOne : public CMonster
{
public:
    enum class BOSSONE_STATE { IDLE, FACE_CHANGE, ARM_SHAKING, ARM_SHAKE_LEFT, SEE_LEFT, LONG, JUMP, GO_BACK, DEAD, END };

public:
    CBossOne();
    virtual ~CBossOne();

public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC _hDC) override;
    virtual void Release() override;

public:
    void BossOne_Animation();
    void BossOne_FSM();
    void Create_Minions(OBJECT_DIRECTION _eDir);

    void BossOne_MoveFrame();

    void BossOne_LeftJump();
    void BossOne_RightJump();


    void Set_CurrentBossOneHp(float _fCurrentHp);
    float Get_CurrentBossOneHp() { return m_fCurrentBossOneHp; }
    float Get_MaxBossOneHp() { return m_fMaxBossOneHp; }

    bool Get_LeftJump(){return m_bBossJumpLeft;}
    void Set_LeftJump(bool _bLeftJump) { m_bBossJumpLeft = _bLeftJump; }

    void Burn_OnFire();

    void While_Long_State();



private:
    BOSSONE_STATE           m_eBossCurState;
    BOSSONE_STATE           m_eBossPreState;


    ULONGLONG               m_dwIdleTime;
    ULONGLONG               m_dwFaceChnagingTime;
    ULONGLONG               m_dwShakingArmTime;

    ULONGLONG               m_dwTurnLeftTime;

    ULONGLONG               m_dwSpawnMinionTime;

    ULONGLONG               m_dwReStartTime;

    ULONGLONG               m_dwBossJumpTime;

    OBJECT_DIRECTION        m_eBossOneDirection;

    bool                 m_bStartPattern1;
    bool                 m_bStartPattern2;
    bool                 m_bShakingArms;
    bool                 m_bFaceChanging;
    bool                 m_bIsDeadOneTime;


    bool                m_bMoving;
    bool                m_bLonging;
    bool                m_bGoBack;


    bool                m_bRestart;



    bool                m_bBossJumpLeft;
    bool                m_bBossJumpRight;
    bool                m_bBossJumpLeftSide;
    bool                m_bBossJumpRightSide;


    float               m_fCurrentBossOneHp;
    float               m_fMaxBossOneHp;

    bool                m_bJumpOver;

    ULONGLONG           m_dwCheckPlayerDirectionTime;

    list<CObject*>      MinionList;

    int                 m_iRandomFirePos;

};

