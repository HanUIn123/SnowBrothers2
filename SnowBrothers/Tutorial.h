#pragma once
#include "Stage.h"
#include "Object.h"
class CTutorial : public CStage
{
public:
    CTutorial();
    virtual ~CTutorial();

public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC _hDC) override;
    virtual void Release() override;

    void Go_Boss();


private:
    CObject* m_pPlayerClass;
    CObject* m_pItemClass;


    ULONGLONG   m_dwMapMoveCoolTime;

    bool        m_bIsNextStage;
};

