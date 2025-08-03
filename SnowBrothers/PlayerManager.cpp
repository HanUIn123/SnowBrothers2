#include "pch.h"
#include "PlayerManager.h"
#include "Player.h"

CPlayerManager* CPlayerManager::m_pInstance = nullptr;

CPlayerManager::CPlayerManager() : 
    m_fX(0.0f),
    m_fY(0.0f),
    m_fSpeed(0.0f),
    m_ePlayerDirection(OBJECT_DIRECTION::DIR_END), 
    m_pPlayerClass(nullptr),
    m_bUpgraded(false)
{
}

CPlayerManager::~CPlayerManager()
{
}

void CPlayerManager::Initialize()
{
   
}

void CPlayerManager::Update()
{
}

void CPlayerManager::Late_Update()
{
}

void CPlayerManager::Render(HDC _hDC)
{
}

void CPlayerManager::Release()
{
}

void CPlayerManager::Set_PlayerInfo(float _fX, float _fY , float _fSpeed/*, OBJECT_DIRECTION _eDirection*/)
{
    m_fX = _fX;
    m_fY = _fY;
    m_fSpeed = _fSpeed;
   //m_ePlayerDirection = _eDirection;
}

void CPlayerManager::Set_PlayerPower(bool _bUpgraded)
{
    m_bUpgraded = _bUpgraded;
}
