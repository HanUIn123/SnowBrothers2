#pragma once
#include "Scene.h"
class CEdit : public CScene
{
public:
    CEdit();
    virtual ~CEdit();

public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC _hDC) override;
    void Release() override;

private:
    void Key_Input();

private:
    bool m_bTileEditMode;
    bool m_bLineEditMode;
    bool m_bSpawnEditMode;

private:
    POINT   m_ptMouse;
};

