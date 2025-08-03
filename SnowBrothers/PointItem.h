#pragma once
#include "Item.h"
class CPointItem : public CItem
{
public:
    enum class POiNT_ITEM_STATE{IDLE,END};
public:
    CPointItem();
    ~CPointItem();

public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC _hDC) override;
    virtual void Release() override;

    void PointItemAnimation();

private:
    int                       m_iPointNumber;
    POiNT_ITEM_STATE          m_eItemCurState;
    POiNT_ITEM_STATE          m_eItemPreState;

};

