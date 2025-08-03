#pragma once
#include "Monster.h"

class CMinions : public CMonster
{
public:
    enum class MONSTERMINION_STATE { IDLE,LANDING, WALK, DEAD, END};

public:
    CMinions();

    virtual ~CMinions();

public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC _hDC) override;
    virtual void Release() override;

    void Minion_Animation();
    void Minion_FSM();
    void Minion_Move_Frame();

    virtual void Set_ReadyToDie(bool _bReadyToDie);

private:
    MONSTERMINION_STATE m_eMinionCurState;
    MONSTERMINION_STATE m_eMinionPreState;

    OBJECT_DIRECTION    m_eMinionDirection;

private:
    vector<HDC>         m_vecHDC;
    UINT                m_iRandDirection;


    ULONGLONG           m_dwIdleTime;


    bool            m_bItemCalled;
};

