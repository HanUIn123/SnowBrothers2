#pragma once
#include "Scene.h"
class CSelectScene : public CScene
{
public:
    CSelectScene();
    virtual ~CSelectScene();

public:
    // CScene을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC _hDC) override;
    void Release() override;
};

