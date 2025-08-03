#pragma once
#include "Item.h"
class CPowerItem : public CItem
{
public:
    enum class POWER_ITEM_STATE { IDLE, END };
public:
    CPowerItem();
    ~CPowerItem();

public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC _hDC) override;
    virtual void Release() override;

    void PowerItemAnimation();

private:
    float                     m_fPowerAbility;
    POWER_ITEM_STATE          m_eItemCurState;
    POWER_ITEM_STATE          m_eItemPreState;
};

