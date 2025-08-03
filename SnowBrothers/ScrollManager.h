#pragma once
#include "DefineCollection.h"
class CScrollManager
{
private:
    CScrollManager();
    ~CScrollManager();

public:
    float       Get_ScrollX() { return m_fScrollX; }
    float       Get_ScrollY() { return m_fScrollY; }
    void        Set_ScrollX(float _fX) { m_fScrollX += _fX; }
    void        Set_ScrollY(float _fY) { m_fScrollY += _fY; }

    void        Shake_Y(float _fY) { m_fScrollY += _fY; }

public:
    static CScrollManager*  Get_Instance()
    {
        if (!m_pInstacne)
            m_pInstacne = new CScrollManager;

        return m_pInstacne;
    }

    static void             Destroy_Instance()
    {
        if (m_pInstacne)
        {
            delete m_pInstacne;
            m_pInstacne = nullptr;
        }
    }
private:
    static CScrollManager*  m_pInstacne;
    float                   m_fScrollX;
    float                   m_fScrollY;
};

