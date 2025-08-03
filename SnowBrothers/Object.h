#pragma once
#include "DefineCollection.h"

class CObject
{
public:
    CObject();
    virtual ~CObject();
public:
    virtual void Initialize()           PURE;
    virtual int Update()                PURE;
    virtual void Late_Update()          PURE;
    virtual void Render(HDC _hDC)       PURE;
    virtual void Release()              PURE;


public:
    const RECT* Get_Rect() { return &m_tRect; }
    tagObjectInfo               Get_ObjectInfo() { return m_tInfo; }

    bool Get_Dead() { return m_bDead; }

    void Set_Dead(bool _bDead) { m_bDead = _bDead; }
    void Set_PosX(float _fX) { m_tInfo.fX += _fX; }
    void Set_PosY(float _fY) { m_tInfo.fY += _fY; }
    void Setting_PosY(float _fY) { m_tInfo.fY = _fY; }
    void Setting_PosX(float _fX) { m_tInfo.fX = _fX; }
    void Setting_SclaeX(float _fCX) { m_tInfo.fCX = _fCX; }
    void Set_Pos(float _fX, float _fY) { m_tInfo.fX = _fX, m_tInfo.fY = _fY; }
    void Set_Direction(OBJECT_DIRECTION _eObjectDir) { m_eDir = _eObjectDir; }

    void Set_TargetPlayer(CObject* _pPlayerClass) { m_pTarget = _pPlayerClass; }


    void Set_CollisionName() { m_pCollisionName = L"ENEMYONESNOW"; }

    const TCHAR* Get_CollisionName() { return m_pCollisionName; }
    const TCHAR* Get_CollisionSnowName() { return m_pCollisionSnowName; }


public:
    float Get_Speed() { return m_fSpeed; }
    void Set_Speed(float _fSpeed) { m_fSpeed = _fSpeed; }


    OBJECT_DIRECTION Get_Direction() { return m_eDir; }
    float Get_JumpSpeed() const { return m_fJumpSpeed; }
    float Get_JumpAccel() const { return m_fJumpAccel; }
    float Get_JumpTime() const { return m_fJumpTime; }

    bool Set_RealPush(bool _bPush) { m_bRealPush = _bPush; return m_bRealPush; }
    bool Get_RealPush() { return m_bRealPush; }


    bool Set_CanKick(bool _bKick) { m_bCanKick = _bKick; return m_bCanKick; }
    bool Get_CanKick() { return m_bCanKick; }


    // ============================ bullet ============================

    bool Get_BulletUpgraded() { return m_bIsBulletUpgraded; }
    void Set_BulletUpgrade(bool _bUpgraded) { m_bIsBulletUpgraded = _bUpgraded; }


    bool Get_BulletRanged() { return m_bIsBulletRanged; }
    void Set_BulletRanged(bool _bRanged) { m_bIsBulletRanged = _bRanged; }




    float           m_fGravityValue;

    bool            m_bCanKick;
    bool            m_bRealPush;



    bool            m_bFalling;

public:
    void        Update_Rect();
    void		Move_Frame();



    float Get_SnowBallSpeed() { return m_fSnowBallSpeed; }
    void Set_SnowBallSpeed(float _fSnowBallSpeed) { m_fSnowBallSpeed = _fSnowBallSpeed; }



    vector<CObject*> Get_VecMonsterSnow() { return m_vecMonsterSnow; }


protected:
    tagObjectInfo               m_tInfo;
    RECT                        m_tRect;
    FRAME                       m_tFrame;
    const TCHAR*                m_pFrameKey;

    FRAME                       m_tSnowFrame;
    const TCHAR*                m_pSnowFrameKey;

    FRAME                       m_tHitedFrame;
    const TCHAR*                m_pHitedFrameKey;


    const TCHAR*                m_pCollisionName;
    const TCHAR*                m_pCollisionSnowName;




    OBJECT_DIRECTION            m_eDir;

    bool                        m_bDead;
    float                       m_fSpeed;
    float                       m_fSnowBallSpeed;
    float                       m_fAngle;
    float                       m_fDistance;
    float                       m_fGravity;



    float                       m_fAccel;
    float                       m_fJumpSpeed;
    float                       m_fJumpAccel;
    float                       m_fJumpTime;
    bool                        m_bLookingRight;



    bool                        m_bIsBulletUpgraded;
    bool                        m_bIsBulletRanged;


    CObject* m_pTarget;





    ULONGLONG                   m_dwFameControllTime;



    vector<CObject*>   m_vecMonsterSnow;


};

