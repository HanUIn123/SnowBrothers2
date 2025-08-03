#include "pch.h"
#include "Tile.h"
#include "BmpManager.h"
#include "ScrollManager.h"
#include "ObjectManager.h"

CTile::CTile() : 
    m_iDrawID(6),
    m_iOption(0)
{
}

CTile::~CTile()
{
    Release();
}

void CTile::Initialize()
{
    m_tInfo.fCX = TILECX;
    m_tInfo.fCY = TILECY;

   
}

int CTile::Update()
{
    if(m_bDead)
        return (UINT)OBJECT_STATE::OBJ_DEAD;

    __super::Update_Rect();



    return (UINT)OBJECT_STATE::OBJ_DEAD;
}

void CTile::Late_Update()
{
}

void CTile::Render(HDC _hDC)
{
    // Rectangle(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

    HDC hMemDC = CBmpManager::Get_Instance()->Find_Img(L"Tile");

    int iScrollX = (int)CScrollManager::Get_Instance()->Get_ScrollX();
    int iScrollY = (int)CScrollManager::Get_Instance()->Get_ScrollY();

    BitBlt(_hDC,
        m_tRect.left  /*iScrollX*/,
        m_tRect.top + iScrollY,
        TILECX,
        TILECY,
        hMemDC,
        TILECX * m_iDrawID,
        0,
        SRCCOPY);
}

void CTile::Release()
{
}
