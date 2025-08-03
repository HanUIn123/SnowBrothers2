#pragma once
#include "Monster.h"

class CMonsterOne : public CMonster
{
public:
    enum class MONSTERONE_STATE { IDLE, WALK, JUMP, DEAD, END };

public:
    CMonsterOne();
    virtual ~CMonsterOne();

public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC _hDC) override;
    virtual void Release() override;


public:

    void MonsterOne_Animation();

    void MonsterOne_FSM();

    void Walk();

    void Jump();

    void DropItem();
   
    virtual void Set_ReadyToDie(bool _bReadyToDie);


private:
    vector<HDC> m_vecHDC;


private:


    ULONGLONG       m_dwIdleTime;
    ULONGLONG       m_dwWalkingTime;
    ULONGLONG       m_dwJumpingTime;

    MONSTER_STATE        m_eMonsterCurState;
    MONSTER_STATE        m_eMonsterPreState;


    OBJECT_DIRECTION    m_eMonsterDirection;

private:
    float           m_fPower;
    float           m_fTime;


    UINT            m_iRandNum;


    bool            m_bItemCalled;
   
};

