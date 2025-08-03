#include "pch.h"
#include "UiManager.h"

CUiManager* CUiManager::m_pInstance = nullptr;

CUiManager::CUiManager()
{
    m_ListUI->clear();
}

CUiManager::~CUiManager()
{
    Release();
}

void CUiManager::Initialize()
{
}

int CUiManager::Update()
{
    int iResult(0);

    for (unsigned int i = 0; i < (UINT)UI_LIST::UI_END; ++i)
    {
        for (auto iter = m_ListUI[i].begin(); iter != m_ListUI[i].end();)
        {
            iResult = (*iter)->Update();

            if ((UINT)UI_STATE::UI_OFF == iResult)
            {
                Safe_Delete<CUI*>(*iter);
                iter = m_ListUI[i].erase(iter);
            }
            else
                ++iter;
        }
    }

    return iResult;
}

void CUiManager::Late_Update()
{
    for (unsigned int i = 0; i < (UINT)UI_LIST::UI_END; ++i)
        for (auto& pUi : m_ListUI[i])
            pUi->Late_Update();
}

void CUiManager::Render(HDC _hDC)
{
    for (unsigned int i = 0; i < (UINT)UI_LIST::UI_END; ++i)
        for (auto& pUi : m_ListUI[i])
            pUi->Render(_hDC);
}

void CUiManager::Release()
{
    for (unsigned int i = 0; i < (UINT)UI_LIST::UI_END; ++i)
    {
        for (auto& pUi : m_ListUI[i])
            Safe_Delete<CUI*>(pUi);
        m_ListUI->clear();
    }
}

void CUiManager::Add_UI(UI_LIST _eUIList, CUI* pUI)
{
    if ((UINT)_eUIList >= (UINT)UI_LIST::UI_END || pUI == nullptr)
        return;

    m_ListUI[(UINT)_eUIList].push_back(pUI);
}
