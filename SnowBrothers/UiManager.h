#pragma once
#include "UI.h"

class CUiManager
{
private:
    CUiManager();
    ~CUiManager();

public:
    void Initialize();
    int Update();
    void Late_Update();
    void Render(HDC _hDC);
    void Release();

public:
    void Add_UI(UI_LIST _eUIList, CUI* pUI);

    


private:
    list<CUI*>  m_ListUI[(UINT)UI_LIST::UI_END];

public:
    static CUiManager* Get_Instance()
    {
        if (!m_pInstance)
            m_pInstance = new CUiManager;

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
    int Get_PlayerLifeCount() {return m_iPlayerLifeCount;}
    void Set_PlayerLifeCount(int _iPlayerLifeCount) { m_iPlayerLifeCount = _iPlayerLifeCount;}


    void Set_GoNext(bool _bGoNext) { m_bGoNext = _bGoNext; }
    bool Get_GoNext() { return m_bGoNext; }

private:
    static CUiManager* m_pInstance;

    int         m_iPlayerLifeCount;


    bool        m_bGoNext;

};

