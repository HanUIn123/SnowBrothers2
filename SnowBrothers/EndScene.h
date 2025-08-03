#pragma once
#include "Stage.h"
#include "Object.h"
class CEndScene : public CStage
{
public:
    CEndScene();
    virtual ~CEndScene();

public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC _hDC) override;
    virtual void Release() override;

private:

};

