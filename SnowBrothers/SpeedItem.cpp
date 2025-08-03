#include "pch.h"
#include "SpeedItem.h"
#include "BmpManager.h"
#include "ObjectManager.h"

CSpeedItem::CSpeedItem() : 
    m_fSpeedAbility(0.0f),
    m_eItemCurState(SPEED_ITEM_STATE::IDLE),
    m_eItemPreState(SPEED_ITEM_STATE::END)
{
    
}

CSpeedItem::~CSpeedItem()
{
    Release();
}

void CSpeedItem::Initialize()
{
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Item/SpeedItem_Idle.bmp", L"SpeedItem_Idle");

    m_tInfo = { WINCX / 2.0f, 250.0f, 64.0f,64.0f };

    m_pCollisionName = L"SPEED";

    m_pFrameKey = L"SpeedItem_Idle";

    m_tFrame = { 0,2,0,50,GetTickCount64() };
}

int CSpeedItem::Update()
{
    if (m_bDead)
        return (UINT)OBJECT_STATE::OBJ_DEAD;

    return (UINT)OBJECT_STATE::OBJ_NOEVENT;
}

void CSpeedItem::Late_Update()
{
    __super::Update_Rect();

    SpeedItemAnimation();

    CObject::Move_Frame();
}

void CSpeedItem::Render(HDC _hDC)
{
    // Rectangle(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

    HDC	hSpeedItemDC = CBmpManager::Get_Instance()->Find_Img(m_pFrameKey);

    GdiTransparentBlt
    (
        _hDC,
        int(m_tRect.left),
        int(m_tRect.top),
        int(64),
        int(64),
        hSpeedItemDC,
        int(m_tInfo.fCX * m_tFrame.iStart),
        int(m_tInfo.fCY * m_tFrame.iMotion),
        int(64),
        int(64),
        RGB(255, 0, 255)
    );
}

void CSpeedItem::Release()
{
}

void CSpeedItem::SpeedItemAnimation()
{
    if (m_eItemPreState != m_eItemCurState)
    {
        switch (m_eItemCurState)
        {
        case SPEED_ITEM_STATE::IDLE:
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 2;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 50;
            m_tFrame.dwTime = GetTickCount64();
            break;
        case SPEED_ITEM_STATE ::END:
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
