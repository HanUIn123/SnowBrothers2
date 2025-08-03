#pragma once
#include "Object.h"
class CPlayerManager
{
public:
    CPlayerManager();
    ~CPlayerManager();

public:
    void Initialize();
    void Update();
    void Late_Update();
    void Render(HDC _hDC);
    void Release();

public:
    void Set_PlayerInfo(float _fX, float _fY, float _fSpeed/*, OBJECT_DIRECTION _eDirection*/);
    void Set_PlayerPower(bool _bUpgraded);

    void Set_PlayerLifeCount(int _iLifeCount) { m_iLifeCount = _iLifeCount; }

public:
    static CPlayerManager* Get_Instance()
    {
        if (!m_pInstance)
            m_pInstance = new CPlayerManager;

        return m_pInstance;
    }

    static void Destroy_Instance()
    {
        if (m_pInstance)
        {
            delete m_pInstance;
            m_pInstance = nullptr;
        }
    }

public:
    float Get_PlayerPosX() { return m_fX; }
    float Get_PlayerPosY() { return m_fY; }
    float Get_PlayerSpeed() {return m_fSpeed;}
    bool Get_PlayerPower() { return m_bUpgraded; }
    int Get_PlayerLifeCount() { return m_iLifeCount; }
    OBJECT_DIRECTION Get_PlayerDirection() {return m_ePlayerDirection;}

private:
    static CPlayerManager* m_pInstance;

private:
    float   m_fX;
    float   m_fY;
    float   m_fSpeed;
    bool    m_bUpgraded;
    int     m_iLifeCount;
    OBJECT_DIRECTION m_ePlayerDirection;


    CObject* m_pPlayerClass;












};

