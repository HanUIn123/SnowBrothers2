#include "pch.h"
#include "Item.h"
#include "BmpManager.h"


CItem::CItem()
{
}

CItem::CItem(float _fX, float _fY, float _fCX, float _fCY, const TCHAR* _pName)
{

}

CItem::~CItem()
{
}

void CItem::Initialize()
{

}

int CItem::Update()
{
    if (m_bDead)
        return (UINT)OBJECT_STATE::OBJ_DEAD;

    __super::Update_Rect();

    return (UINT)OBJECT_STATE::OBJ_NOEVENT;
}

void CItem::Late_Update()
{
    __super::Update_Rect();
}

void CItem::Render(HDC _hDC)
{
   
}

void CItem::Release()
{
}
