#pragma once
#include "UI.h"
class CImages : public CUI
{
public:
    enum class UI_STATE{IDLE,GREAT, END};
public:
    CImages();
    virtual ~CImages();

public:
    virtual void Initialize()       override;
    virtual int Update()            override;
    virtual void Late_Update()      override;
    virtual void Render(HDC _hDC)   override;
    virtual void Release()          override;


public:
    void EndScene_FSM();

    void EndScene_Animation();

    void Move_Frame();

private:

    UI_STATE    m_eCurUISTATE;
    UI_STATE    m_ePreUISTATE;

};

