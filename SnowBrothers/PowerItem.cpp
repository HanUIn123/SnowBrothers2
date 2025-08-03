#include "pch.h"
#include "PowerItem.h"
#include "BmpManager.h"
#include "ObjectManager.h"

CPowerItem::CPowerItem() : 
    m_fPowerAbility(0.0f),
    m_eItemCurState(POWER_ITEM_STATE::IDLE),
    m_eItemPreState(POWER_ITEM_STATE::END)
{
}

CPowerItem::~CPowerItem()
{
    Release();
}

void CPowerItem::Initialize()
{
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Item/PowerItem_Idle.bmp", L"PowerItem_Idle");

    m_tInfo = { WINCX / 3.0f, 250.0f , 64.0f ,64.0f };

    m_pCollisionName = L"POWER";

    m_pFrameKey = L"PowerItem_Idle";

    m_tFrame = { 0,2,0,50,GetTickCount64() };
}

int CPowerItem::Update()
{
    if (m_bDead)
    {
        return (UINT)OBJECT_STATE::OBJ_DEAD;
    }
    return (UINT)OBJECT_STATE::OBJ_NOEVENT;
}

void CPowerItem::Late_Update()
{
    __super::Update_Rect();
    
    PowerItemAnimation();

    CObject::Move_Frame();
}

void CPowerItem::Render(HDC _hDC)
{
    HDC hPowerItemDC = CBmpManager::Get_Instance()->Find_Img(m_pFrameKey);

    GdiTransparentBlt
    (
        _hDC,
        int(m_tRect.left),
        int(m_tRect.top),
        int(64),
        int(64),
        hPowerItemDC,
        int(m_tInfo.fCX * m_tFrame.iStart),
        int(m_tInfo.fCY * m_tFrame.iMotion),
        int(64),
        int(64),
        RGB(255, 0, 255)
    );
}

void CPowerItem::Release()
{
}

void CPowerItem::PowerItemAnimation()
{
    if (m_eItemPreState != m_eItemCurState)
    {
        switch (m_eItemCurState)
        {
        case POWER_ITEM_STATE::IDLE:
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 2;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 50;
            m_tFrame.dwTime = GetTickCount64();
            break;
        case POWER_ITEM_STATE::END:
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

