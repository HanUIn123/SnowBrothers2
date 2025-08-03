#pragma once
#include "DefineCollection.h"
class CKeyManager
{
private:
    CKeyManager();
    ~CKeyManager();

public:
    bool    Key_Pressing(int _iKey);
    bool    Key_Down(int _iKey);
    bool    Key_Up(int _iKey);
    void    Key_Update();

public:
    static CKeyManager* Get_Instance()
    {
        if (!m_pInstance)
            m_pInstance = new CKeyManager;

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
    static CKeyManager* m_pInstance;
    bool                m_bKeyState[VK_MAX];
};

