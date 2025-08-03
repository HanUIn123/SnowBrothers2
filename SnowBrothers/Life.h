#pragma once
#include "UI.h"
class CLife : public CUI
{
public:
    CLife();
    virtual ~CLife();

public:
    virtual void Initialize()       override;
    virtual int Update()            override;
    virtual void Late_Update()      override;
    virtual void Render(HDC _hDC)   override;
    virtual void Release()          override;

public:
    void Lose_LifeCount();


private:
    vector<HDC> m_vecHDC;
    vector<HDC> m_vecHDC2;

public:
    int m_iHuns_Digit;
    int m_iTens_Digit;
    int m_iOne_Digit;

};

