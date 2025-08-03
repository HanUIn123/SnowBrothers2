#pragma once
#include "UserBmp.h"

class CBmpManager
{
private:
    CBmpManager();
    ~CBmpManager();

public:
    void    Insert_Bmp(const TCHAR* _pFilePath, const TCHAR* _pImgKey);
    HDC     Find_Img(const TCHAR* _pImgKey);
    void    Release();

public:
    static CBmpManager* Get_Instance()
    {
        if (!m_pInstance)
            m_pInstance = new CBmpManager;

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
    map<const TCHAR*, CUserBmp*>    m_mapBit;
private:
    static CBmpManager* m_pInstance;

};

