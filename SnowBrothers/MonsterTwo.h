#pragma once
#include "Monster.h"
class CMonsterTwo : public CMonster
{
public:
    enum class MONSTERTWO_STATE { IDLE, WALK, SHOOT, JUMP, CHANGE, DEAD, END};
public:
    CMonsterTwo();
    virtual ~CMonsterTwo();

public:
    virtual void    Initialize() override;
    virtual int     Update() override;
    virtual void    Late_Update() override;
    virtual void    Render(HDC _hDC) override;
    virtual void    Release() override;

    void            MT_Animation();
    void            MT_FSM();

    CObject* Create_MonsterBullet(OBJECT_DIRECTION _eDirection);


public:
    void MT_Move_Frame();

    void Jump();

    virtual void Set_ReadyToDie(bool _bReadyToDie);

private:
    MONSTERTWO_STATE    m_eMTCurState;
    MONSTERTWO_STATE    m_eMTPreState;
    OBJECT_DIRECTION    m_eMonsterDirection;

private:
    vector<HDC>         m_vecHDC;
    ULONGLONG           m_dwIdleTime;


    ULONGLONG           m_dwShootTime;
    ULONGLONG           m_dwBulletCoolTime;
    ULONGLONG           m_dwJumpTime;

    bool                m_bShoot;

    int                 m_iRanAttackDecade;

    bool m_bItemCalled;
};

