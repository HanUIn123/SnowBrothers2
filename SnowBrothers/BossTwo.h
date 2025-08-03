#pragma once
#include "Monster.h"
class CBossTwo : public CMonster
{
public:
    enum class BOSSTWO_STATE { IDLE, SPAWN_MINION, NOSE_SHOT, GOT_HIT,MOVE_HORIZON,END };
public:
    CBossTwo();
    virtual ~CBossTwo();

public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC _hDC) override;
    virtual void Release() override;

    CObject* Create_BossBullet(OBJECT_DIRECTION _eDirection, CObject* _ptarget);

public:
    void                BossTwo_Animation();

    void                BossTwo_FSM();

    void                Create_Minions();

    void                BossTwo_MoveFrame();

    BOSSTWO_STATE        m_eBossCurState;
    BOSSTWO_STATE        m_eBossPreState;

    ULONGLONG           m_dwIdleTime;
    ULONGLONG           m_dwShotTime;


    ULONGLONG           m_dwMoveHorTime;
    ULONGLONG           m_dwMoveHorTime2;

    ULONGLONG           m_dwBulletCool;


    ULONGLONG           m_dwBossHitTime;


    void    Set_CurrentBossTwoHp(float _fCurrentHp) 
    { 
        m_fCurrentBossTwoHp -= _fCurrentHp; 

        m_pFrameKey = L"Boss2_Hited";

        m_eBossCurState = BOSSTWO_STATE::GOT_HIT;
    }

    float   Get_CurrentBossTwoHp() { return m_fCurrentBossTwoHp; }
    float   Get_MaxBossTwoHp() { return m_fMaxBossTwoHp; }

private:

    int     iRandomPosX;
    int     iRandomPosY;


    bool    m_bGoRight;

    float   m_fCurrentBossTwoHp;
    float   m_fMaxBossTwoHp;

};

