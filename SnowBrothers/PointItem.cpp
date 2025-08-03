#include "pch.h"
#include "PointItem.h"
#include "BmpManager.h"
#include "ObjectManager.h"


CPointItem::CPointItem() : 
    m_iPointNumber(0),
    m_eItemCurState(POiNT_ITEM_STATE::IDLE),
    m_eItemPreState(POiNT_ITEM_STATE::END)
{
}

CPointItem::~CPointItem()
{
    Release();
}

void CPointItem::Initialize()
{
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Item/fishBread.bmp", L"fishBread");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Item/ramen.bmp", L"ramen");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Item/rice.bmp", L"rice");

    m_tInfo = { WINCX / 3.0f, 250.0f , 77.0f ,64.0f };

    m_pCollisionName = L"POINT_ITEM";

    m_pFrameKey = L"fishBread";


    switch (GetTickCount64() % 3)
    {
    case 0:
        m_pFrameKey = L"fishBread";
        break;

    case 1:
        m_pFrameKey = L"ramen";
        break;

    case 2:
        m_pFrameKey = L"rice";
        break;
    }

    m_tFrame = { 0,0,0,50,GetTickCount64() };
}

int CPointItem::Update()
{
    if (m_bDead)
    {
        return (UINT)OBJECT_STATE::OBJ_DEAD;
    }

    return (UINT)OBJECT_STATE::OBJ_NOEVENT;
}

void CPointItem::Late_Update()
{
    __super::Update_Rect();

    PointItemAnimation();

    CObject::Move_Frame();
}

void CPointItem::Render(HDC _hDC)
{
    HDC hPointItemDC = CBmpManager::Get_Instance()->Find_Img(m_pFrameKey);

    GdiTransparentBlt
    (
        _hDC,
        int(m_tRect.left),
        int(m_tRect.top),
        int(77),
        int(64),
        hPointItemDC,
        int(m_tInfo.fCX * m_tFrame.iStart),
        int(m_tInfo.fCY * m_tFrame.iMotion),
        int(77),
        int(64),
        RGB(255, 0, 255)
    );
}

void CPointItem::Release()
{
}

void CPointItem::PointItemAnimation()
{
    if (m_eItemPreState != m_eItemCurState)
    {
        switch (m_eItemCurState)
        {
        case POiNT_ITEM_STATE::IDLE:
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 0;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 50;
            m_tFrame.dwTime = GetTickCount64();
            break;
        case POiNT_ITEM_STATE::END:
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
