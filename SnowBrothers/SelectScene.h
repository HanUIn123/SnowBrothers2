#pragma once
#include "Scene.h"
class CSelectScene : public CScene
{
public:
    CSelectScene();
    virtual ~CSelectScene();

public:
    // CScene��(��) ���� ��ӵ�
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC _hDC) override;
    void Release() override;
};

