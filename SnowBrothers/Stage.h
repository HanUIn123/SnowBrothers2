#pragma once
#include "Scene.h"
class CStage : public CScene
{
public:
    CStage();
    virtual ~CStage();
public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC _hDC) override;
    virtual void Release() override;
};

