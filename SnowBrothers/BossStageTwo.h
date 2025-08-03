#pragma once
#include "Stage.h"
#include "Object.h"

class CBossStageTwo : public CStage
{
public:
    CBossStageTwo();
    virtual ~CBossStageTwo();

public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC _hDC) override;
    virtual void Release() override;

    void Go_EndScene();


private:
    CObject* m_pPlayerClass;
    CObject* m_pItemClass;

    CObject* pBossTwo;



};

