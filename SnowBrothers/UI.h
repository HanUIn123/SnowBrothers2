#pragma once
#include "DefineCollection.h"

class CUI
{
public:
    CUI();
    virtual ~CUI() {};

public:
    virtual void Initialize()       PURE;
    virtual int Update()            PURE;
    virtual void Late_Update()      PURE;
    virtual void Render(HDC _hDC)   PURE;
    virtual void Release()          PURE;

    void Set_UiList(UI_LIST _eUIlist) { m_eUIList = _eUIlist; }

protected:
    tagUiInfo                   m_tInfo;
    RECT                        m_tRect;

    UI_LIST                     m_eUIList;


    FRAME                       m_tFrame;
    const TCHAR*                m_pFrameKey;
};