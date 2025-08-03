#include "pch.h"
#include "EffectManager.h"
#include "BmpManager.h"


CEffectManager* CEffectManager::m_pInstance = nullptr;

CEffectManager::CEffectManager() :
    m_eCurEffectState(EFFECT_STATE::SHOOT_EFFECT),
    m_ePreEffectState(EFFECT_STATE::EFFECT_END),
    m_pFrameKey(nullptr),
    m_bTriggered(false) 
{
    ZeroMemory(&m_tFrame, sizeof(FRAME));
    ZeroMemory(&m_tRect, sizeof(RECT));
    m_dwExistingTime = GetTickCount64();
}

CEffectManager::~CEffectManager()
{
}

void CEffectManager::Initialize()
{
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Effect/ShootEffect.bmp", L"Shoot_Effect");

    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Effect/BossHitedEffect.bmp", L"BossHitedEffect");

    m_tInfo = { 100.f, WINCY / 2.f, 50, 50 };

    m_pFrameKey = L"Shoot_Effect";

    m_tFrame = { 0, 3, 0, 20, GetTickCount64() };
}

void CEffectManager::Update()
{

}

void CEffectManager::Late_Update()
{
    Effect_Animation();

    if(m_eCurEffectState == EFFECT_STATE::BOSS_HITED_EFFECT)
        Move_Frame();

    Check_Index_Frame();
}

void CEffectManager::Render(HDC _hDC)
{
    HDC hPlayerShootDC = CBmpManager::Get_Instance()->Find_Img(L"Shoot_Effect");
    HDC hBossHitedDC = CBmpManager::Get_Instance()->Find_Img(L"BossHitedEffect");

    if (m_bTriggered)
    {
        if (m_eCurEffectState == EFFECT_STATE::SHOOT_EFFECT)
        {
            GdiTransparentBlt(_hDC,
                int(m_fFX),
                int(m_fFY),
                int(50),
                int(50),
                hPlayerShootDC,
                int(m_tInfo.fCX * m_tFrame.iStart),
                int(m_tInfo.fCY * m_tFrame.iMotion),
                int(50),
                int(50),
                RGB(255, 0, 255));
        }
    }

    if (m_eCurEffectState == EFFECT_STATE::BOSS_HITED_EFFECT)
    {
        GdiTransparentBlt(_hDC,
            int(m_fFX),
            int(m_fFY),
            int(44),
            int(55),
            hBossHitedDC,
            int(44 * m_tFrame.iStart),
            int(55 * m_tFrame.iMotion),
            int(44),
            int(55),
            RGB(255, 0, 255));
    }
}

void CEffectManager::Release()
{
}

void CEffectManager::Move_Frame()
{
    if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount64())
    {
        ++m_tFrame.iStart;

        if (m_tFrame.iStart > m_tFrame.iEnd)
        {
            m_tFrame.iStart = 0;
        }

        m_tFrame.dwTime = GetTickCount64();
    }
}

void CEffectManager::Effect_Animation()
{
    if (m_ePreEffectState != m_eCurEffectState)
    {
        switch (m_eCurEffectState)
        {
        case EFFECT_STATE::SHOOT_EFFECT:
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 3;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 40;
            m_tFrame.dwTime = GetTickCount64();
            break;
        case EFFECT_STATE::BOSS_HITED_EFFECT:
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 1;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 80;
            m_tFrame.dwTime = GetTickCount64();
            break;
        }
        m_ePreEffectState = m_eCurEffectState;
    }
}

void CEffectManager::Get_Effect_Pos(float _fX, float _fY)
{
    m_fFX = _fX;
    m_fFY = _fY;
}

void CEffectManager::Check_Index_Frame()
{
    if (m_bTriggered)
    {
        if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount64())
        {
            ++m_tFrame.iStart;

            if (m_tFrame.iStart >= m_tFrame.iEnd)
            {
                m_tFrame.iStart = m_tFrame.iEnd;
                m_tFrame.iStart = 0;
                m_bTriggered = false;
            }
            m_tFrame.dwTime = GetTickCount64();
        }
    }
}

void CEffectManager::Change_State(int _iStateNum)
{
    if (_iStateNum == 1)
    {
        m_eCurEffectState = EFFECT_STATE::SHOOT_EFFECT;
    }
    if (_iStateNum == 2)
    {
        m_eCurEffectState = EFFECT_STATE::BOSS_HITED_EFFECT;
    }
    
}
