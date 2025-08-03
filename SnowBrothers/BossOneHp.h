#pragma once
#include "UI.h"
class CBossOneHp : public CUI
{
public:
    CBossOneHp();
    virtual ~CBossOneHp();

public:
    virtual void Initialize()       override;
    virtual int Update()            override;
    virtual void Late_Update()      override;
    virtual void Render(HDC _hDC)   override;
    virtual void Release()          override;

public:
    void Decrease_Hp();
private:
    vector<HDC> m_vecHDC;
};

