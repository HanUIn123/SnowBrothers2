#pragma once
#include "Item.h"
class CSpeedItem : public CItem
{
public:
    enum class SPEED_ITEM_STATE { IDLE , END };
public:
    CSpeedItem();
    ~CSpeedItem();

public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC _hDC) override;
    virtual void Release() override;

    void SpeedItemAnimation();

private:
    float               m_fSpeedAbility;
    SPEED_ITEM_STATE           m_eItemCurState;
    SPEED_ITEM_STATE           m_eItemPreState;
};

