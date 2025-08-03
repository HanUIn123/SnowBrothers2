#pragma once
#include "Stage.h"
#include "Object.h"
class CStageOne : public CStage
{
public:
    CStageOne();
    virtual ~CStageOne();

public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC _hDC) override;
    virtual void Release() override;

    void Go_Next();

private:
    CObject* m_pPlayerClass;

    bool        m_bIsGoNextStage;
};

