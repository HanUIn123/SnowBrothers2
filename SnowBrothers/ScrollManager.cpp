#include "pch.h"
#include "ScrollManager.h"

CScrollManager* CScrollManager::m_pInstacne = nullptr;


CScrollManager::CScrollManager() :
    m_fScrollX(0.0f),
    m_fScrollY(0.0f)
{
}

CScrollManager::~CScrollManager()
{
}
