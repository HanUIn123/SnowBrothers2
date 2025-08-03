#pragma once
#include "Object.h"
class CEffectManager
{
public:
    enum class EFFECT_STATE { IDLE, SHOOT_EFFECT, BOSS_HITED_EFFECT, EFFECT_END };

public:
    CEffectManager();
    ~CEffectManager();

public:
    void Initialize();
    void Update();
    void Late_Update();
    void Render(HDC _hDC);
    void Release();

public:
    void		Move_Frame();
    void        Effect_Animation();

    void        Get_Effect_Pos(float _fX, float _fY);
    void        Check_Index_Frame();

    bool        Get_beTriggered() { return m_bTriggered; }
    void        Set_BeTriggered(bool _bTriggered) { m_bTriggered = _bTriggered; m_tFrame.dwTime = GetTickCount64(); }

    void        Change_State(int _iStateNum);
    

public:
    static CEffectManager* Get_Instance()
    {
        if (!m_pInstance)
            m_pInstance = new CEffectManager;

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

private:
    static CEffectManager* m_pInstance;
    EFFECT_STATE m_eCurEffectState;
    EFFECT_STATE m_ePreEffectState;

    FRAME                       m_tFrame;
    const TCHAR*                m_pFrameKey;
    RECT                        m_tRect;
    tagObjectInfo               m_tInfo;

    float                       m_fFX;
    float                       m_fFY;

    bool                        m_bTriggered;
    ULONGLONG                   m_dwExistingTime;


};

