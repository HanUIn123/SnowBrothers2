#pragma once
#include "Item.h"
class CRangeItem : public CItem
{
public:
    enum class RANGE_ITEM_STATE { IDLE, END };
public:
    CRangeItem();
    ~CRangeItem();

public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC _hDC) override;
    virtual void Release() override;

    void RangeItemAnimation();

private:
    float                     m_fRangeAbility;
    RANGE_ITEM_STATE          m_eItemCurState;
    RANGE_ITEM_STATE          m_eItemPreState;
};

