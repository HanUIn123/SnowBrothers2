#include "pch.h"
#include "BmpManager.h"

CBmpManager* CBmpManager::m_pInstance = nullptr;

CBmpManager::CBmpManager()
{
}

CBmpManager::~CBmpManager()
{
    Release();
}

void CBmpManager::Insert_Bmp(const TCHAR* _pFilePath, const TCHAR* _pImgKey)
{
    auto iter = find_if(m_mapBit.begin(), m_mapBit.end(), CTag_Finder(_pImgKey));
    
    if (iter == m_mapBit.end())
    {
        CUserBmp* pUserBmp = new CUserBmp;
        pUserBmp->Load_Bmp(_pFilePath);

        m_mapBit.insert({ _pImgKey,pUserBmp });
    }
}

HDC CBmpManager::Find_Img(const TCHAR* _pImgKey)
{
    auto iter = find_if(m_mapBit.begin(), m_mapBit.end(), CTag_Finder(_pImgKey));

    if (iter == m_mapBit.end())
    {
        return nullptr;
    }

    return iter->second->Get_MemDC();
}

void CBmpManager::Release()
{
    for_each(m_mapBit.begin(), m_mapBit.end(), tagDeleteMap());
    m_mapBit.clear();
}
