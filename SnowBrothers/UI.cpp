#include "pch.h"
#include "UI.h"

CUI::CUI() : 
    m_eUIList(UI_LIST::UI_END)
{
    ZeroMemory(&m_tInfo, sizeof(m_tInfo));
    ZeroMemory(&m_tRect, sizeof(RECT));
}
