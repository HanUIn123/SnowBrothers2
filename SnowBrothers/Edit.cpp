#include "pch.h"
#include "Edit.h"
#include "BmpManager.h"
#include "KeyManager.h"
#include "ScrollManager.h"
#include "TileManager.h"
#include "LineManager.h"
#include "SceneManager.h"
#include "SpawnManager.h"
#include "ObjectManager.h"

CEdit::CEdit() :
    m_bTileEditMode(false),
    m_bLineEditMode(false),
    m_bSpawnEditMode(false)

{
    ZeroMemory(&m_ptMouse, sizeof(POINT));
}

CEdit::~CEdit()
{
    Release();
}

void CEdit::Initialize()
{
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Tile/Tile04.bmp", L"Tile");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/BackGround/stage102.bmp", L"Ground");

    CTileManager::Get_Instance()->Initialize();
}

int CEdit::Update()
{
    CTileManager::Get_Instance()->Update();
    return 0;
}

void CEdit::Late_Update()
{
    CTileManager::Get_Instance()->Late_Update();

    Key_Input();
}

void CEdit::Render(HDC _hDC)
{
    HDC	hGroundDC = CBmpManager::Get_Instance()->Find_Img(L"Ground");

    BitBlt(_hDC, 0, 0, WINCX, WINCY * 2, hGroundDC, 0, 0, SRCCOPY);

    CSpawnManager::Get_Instance()->Render(_hDC);
    CTileManager::Get_Instance()->Render(_hDC);
    CLineManager::Get_Instance()->Render(_hDC);

    TCHAR	szCount10[32] = L"";
    swprintf_s(szCount10, L"TileMode : %d", m_bTileEditMode);
    TextOut(_hDC, 20, 20, szCount10, lstrlen(szCount10));

    TCHAR	szCount11[32] = L"";
    swprintf_s(szCount11, L"LineMode : %d", m_bLineEditMode);
    TextOut(_hDC, 20, 40, szCount11, lstrlen(szCount11));

    TCHAR	szCount15[32] = L"";
    swprintf_s(szCount15, L"SpawnMode : %d", m_bSpawnEditMode);
    TextOut(_hDC, 20, 60, szCount15, lstrlen(szCount15));

    TCHAR	szCount[32] = L"";
    swprintf_s(szCount, L"X : %d, Y : %d", m_ptMouse.x, m_ptMouse.y);
    TextOut(_hDC, WINCX / 2 - 30, 50, szCount, lstrlen(szCount));
}

void CEdit::Release()
{
}

void CEdit::Key_Input()
{
    if (CKeyManager::Get_Instance()->Key_Down(VK_RETURN))
    {
    }

    if (m_bTileEditMode)
    {
        if (CKeyManager::Get_Instance()->Key_Pressing(VK_LBUTTON))
        {
            GetCursorPos(&m_ptMouse);
            ScreenToClient(g_hWnd, &m_ptMouse);

            m_ptMouse.x -= (int)CScrollManager::Get_Instance()->Get_ScrollX();
            m_ptMouse.y -= (int)CScrollManager::Get_Instance()->Get_ScrollY();

            CTileManager::Get_Instance()->Picking_Tile(m_ptMouse, 0, 0);
        }

        if (CKeyManager::Get_Instance()->Key_Pressing(VK_LBUTTON) && CKeyManager::Get_Instance()->Key_Pressing('Q'))
        {
            GetCursorPos(&m_ptMouse);
            ScreenToClient(g_hWnd, &m_ptMouse);

            m_ptMouse.x -= (int)CScrollManager::Get_Instance()->Get_ScrollX();
            m_ptMouse.y -= (int)CScrollManager::Get_Instance()->Get_ScrollY();

            CTileManager::Get_Instance()->Picking_Tile(m_ptMouse, 3, 0);
        }

        if (CKeyManager::Get_Instance()->Key_Pressing(VK_RBUTTON))
        {
            GetCursorPos(&m_ptMouse);
            ScreenToClient(g_hWnd, &m_ptMouse);

            m_ptMouse.x -= (int)CScrollManager::Get_Instance()->Get_ScrollX();
            m_ptMouse.y -= (int)CScrollManager::Get_Instance()->Get_ScrollY();

            CTileManager::Get_Instance()->Picking_Tile(m_ptMouse, 6, 0);
        }
    }

    if (m_bLineEditMode)
    {
        GetCursorPos(&m_ptMouse);
        ScreenToClient(g_hWnd, &m_ptMouse);

        m_ptMouse.x -= (int)CScrollManager::Get_Instance()->Get_ScrollX();
        m_ptMouse.y -= (int)CScrollManager::Get_Instance()->Get_ScrollY();
        CLineManager::Get_Instance()->Draw_Line(m_ptMouse);
    }

    if (m_bSpawnEditMode)
    {
        CSpawnManager::Get_Instance()->Set_Spawner();
    }

    if (CKeyManager::Get_Instance()->Key_Down('T'))
    {
        m_bTileEditMode = true;
        m_bLineEditMode = false;
        m_bSpawnEditMode = false;
    }

    if (CKeyManager::Get_Instance()->Key_Down('L'))
    {
        m_bLineEditMode = true;
        m_bTileEditMode = false;
        m_bSpawnEditMode = false;
    }

    if (CKeyManager::Get_Instance()->Key_Down('M'))
    {
        m_bSpawnEditMode = true;
        m_bTileEditMode = false;
        m_bLineEditMode = false;
    }

    if (CKeyManager::Get_Instance()->Key_Down('S'))
    {
        CLineManager::Get_Instance()->Save_Line();
        CTileManager::Get_Instance()->Save_Tile();
        CSpawnManager::Get_Instance()->Save_Spawner();
    }

}
