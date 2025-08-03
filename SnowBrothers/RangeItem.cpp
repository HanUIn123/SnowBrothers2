#include "pch.h"
#include "RangeItem.h"
#include "BmpManager.h"
#include "ObjectManager.h"


CRangeItem::CRangeItem() :
    m_fRangeAbility(0.0f),
    m_eItemCurState(RANGE_ITEM_STATE::IDLE),
    m_eItemPreState(RANGE_ITEM_STATE::END)
{
}

CRangeItem::~CRangeItem()
{
    Release();
}

void CRangeItem::Initialize()
{
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Item/RangeItem_Idle.bmp", L"RangeItem_Idle");

    m_tInfo = { WINCX / 2.0f + 100.0f, 250.0f , 64.0f ,64.0f };

    m_pCollisionName = L"RANGE";

    m_pFrameKey = L"RangeItem_Idle";

    m_tFrame = { 0,2,0,50,GetTickCount64() };
}

int CRangeItem::Update()
{
    if (m_bDead)
    {
        return (UINT)OBJECT_STATE::OBJ_DEAD;
    }
    return (UINT)OBJECT_STATE::OBJ_NOEVENT;
}

void CRangeItem::Late_Update()
{
    __super::Update_Rect();

    RangeItemAnimation();

    CObject::Move_Frame();
}

void CRangeItem::Render(HDC _hDC)
{
    HDC hRangeItemDC = CBmpManager::Get_Instance()->Find_Img(m_pFrameKey);

    GdiTransparentBlt
    (
        _hDC,
        int(m_tRect.left),
        int(m_tRect.top),
        int(64),
        int(64),
        hRangeItemDC,
        int(m_tInfo.fCX * m_tFrame.iStart),
        int(m_tInfo.fCY * m_tFrame.iMotion),
        int(64),
        int(64),
        RGB(255, 0, 255)
    );
}

void CRangeItem::Release()
{
}

void CRangeItem::RangeItemAnimation()
{
    if (m_eItemPreState != m_eItemCurState)
    {
        switch (m_eItemCurState)
        {
        case RANGE_ITEM_STATE::IDLE:
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 2;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 50;
            m_tFrame.dwTime = GetTickCount64();
            break;
        case RANGE_ITEM_STATE::END:
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 0;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 200;
            m_tFrame.dwTime = GetTickCount64();
            break;
        }
    }
    m_eItemPreState = m_eItemCurState;
}
