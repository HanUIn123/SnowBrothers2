#pragma once
#include "Object.h"
#include "Monster.h"


class CMonster;
class CPlayer : public CObject
{
public:
    enum class PLAYER_STATE { IDLE, WALK, RUN, JUMP, PUSH, SHOOT, KICK, ROLLING, FALLING ,DEAD, SUPER, END };

public:
    CPlayer();
    virtual ~CPlayer();

public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC _hDC) override;
    virtual void Release() override;

    PLAYER_STATE Get_PlayerState() { return m_eCurState; }
    void Set_PlayerState(PLAYER_STATE _eState) { m_eCurState = _eState; }
    

    //OBJECT_DIRECTION Get_PlayerDirection() { return m_ePlayerDirection; }
    //OBJECT_DIRECTION Get_PlayerDirection() { return m_eDir; }

public:
    void Set_TargeetMonster(CObject* _pObject)
    {
        m_pTarget = _pObject;
    }

public:

    bool Set_CanPush(bool _bPush) {   m_bCanPush = _bPush; return m_bCanPush; }
    bool Get_CanPush() { return m_bCanPush; }

    bool Set_RealPush(bool _bPush) { m_bRealPush = _bPush; return m_bRealPush; }
    bool Get_RealPush() { return m_bRealPush; }


    bool Get_DownJump() { return m_bDownJump; }
    void Set_DownJump(bool _bDownJump) { m_bDownJump = _bDownJump; }


    bool Get_CanRolling() { return m_bCanRollwithSnow; }
    void Set_CanRolling(bool _bCanRolling) { m_bCanRollwithSnow = _bCanRolling; }


   // bool Set_CanKick(bool _bKick) { m_bCanKick = _bKick; return m_bCanKick; }
    //bool Get_CanKick() { return m_bCanKick; }

    void Plus_Life(int _Plus) { if (m_iLife < 3)m_iLife += _Plus; }
    void Lose_Life(int _Lose) { m_iLife -= _Lose; }

    void Set_Life(int _iLife) { m_iLife = _iLife; }
    int Get_Life() { return m_iLife; }
    int Get_Count() { return m_iExampleCount; }
    void Set_Count(int _iCount) { m_iExampleCount = _iCount; }

    void   Set_UpgradeBullet(bool _bUpgraded) { m_bBulletUpgraded = _bUpgraded; }
    bool   Get_UpgradeBullet() { return m_bBulletUpgraded; }



    float Get_JumpPower() { return m_fJumpPower; }
    void Set_PlayerJumpPower(float _fJumpPower) { m_fJumpPower = _fJumpPower; }

    bool Get_PlayerJump() { return m_bJump; }
    void Set_PlayerJumpFalse() { m_bJump = false; }


    bool Get_PlayerFalling() { return m_bFalling; }
    void Set_PlayerFallingFalse() { m_bFalling = false; }


    //float Get_Gravity() { return m_fGravityValue; }
    //void Set_GrvityValue(float _fGravity) { m_fGravityValue = _fGravity; }

    bool Get_SuperMode() { return m_bSuperMode; }
    void Set_SuperMode(bool _bSuperMode) { m_bSuperMode = _bSuperMode; }
    
    bool Get_UnlimitedSuperMode() { return m_bUnlimitedSuperMode; }
    void Set_UnlimitedSuperMode(bool _bSuperMode) { m_bUnlimitedSuperMode = _bSuperMode; }

    bool Get_IsOnSnow() { return m_bIsOnSnow; }
    void Set_IsOnSnow(bool _bIsOnSnow) { m_bIsOnSnow = _bIsOnSnow; }


    bool Get_Ranged() {return m_bRanged;}
    void Set_Ranged(bool _bRanged) { m_bRanged = _bRanged; }

    bool Get_BeforeDie() { return m_bBeforeDie; }
    void Set_BeforeDie(bool _bBeforeDie) { m_bBeforeDie = _bBeforeDie; m_dwPlayerDieCoolTime = GetTickCount64(); }


private:
    void Jump();

    void Jump2();

    void Offset();

    void Player_FSM();

    void Player_Animation();

    void Shoot();

    void Kick();

public:

    void Push_Snow();

private:

    void Text_Render(HDC _hDC);

    CObject* Create_Bullet(OBJECT_DIRECTION _eDirection, bool _bUpgraded);


private:
    bool            m_bJump;
    bool            m_bDownJump;

    float           m_fPower;
    float           m_fTime;

    PLAYER_STATE    m_eCurState;
    PLAYER_STATE    m_ePreState;
    //OBJECT_DIRECTION m_ePlayerDirection;


private:
    bool            m_bWalking;
    bool            m_bRunning;
    float			m_iTickCount;
    bool            m_isLookingDown;
    bool            m_bFalling;



    bool            m_bShoot;
    ULONGLONG       m_dwShootingTime;


    ULONGLONG       m_dwDownJumpTime;


    bool            m_bCanPush;

    bool            m_bRealPush;


    bool            m_bBulletUpgraded;


private:
    int             m_iLife;

    int             m_iExampleCount;





    bool            m_bSpeedUp;
    bool            m_bRanged;


    float           m_fJumpPower;



    bool            m_bCanRollwithSnow;


    ULONGLONG       m_dwSuperTime;

    bool            m_bSuperMode;


    bool            m_bUnlimitedSuperMode;

    bool            m_bIsOnSnow;

    bool            m_bBeforeDie;
    ULONGLONG       m_dwPlayerDieCoolTime;

    ULONGLONG m_dwInvincibleStartTime; // SUPER 상태 시 무적 시작 시간

public:
    ULONGLONG Get_InvincibleStartTime() const { return m_dwInvincibleStartTime; }
};

