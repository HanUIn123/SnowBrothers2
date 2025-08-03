#include "pch.h"
#include "MainGame.h"
#include "BmpManager.h"
#include "KeyManager.h"
#include "AbstractFactory.h"
#include "ObjectManager.h"
#include "SceneManager.h"
#include "TileManager.h"
#include "ScrollManager.h"
#include "LineManager.h"
#include "UiManager.h"
#include "SpawnManager.h"
#include "PlayerManager.h"
#include "MapManager.h"
#include "SoundMgr.h"
#include "EffectManager.h"

CMainGame::CMainGame() :
    m_dwTime(GetTickCount64()),
    m_iFPS(0),
    m_DC(nullptr)
{
    ZeroMemory(m_szFPS, sizeof(m_szFPS));
}

CMainGame::~CMainGame()
{
    Release();
}

void CMainGame::Initialize()
{
    srand(unsigned(time(NULL)));

    m_DC = GetDC(g_hWnd);

    //CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Win_Back.bmp", L"Win_Back");
    CSoundMgr::Get_Instance()->Initialize();

    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/BackGround/WholeBackGround5.bmp", L"Win_Back");
    //CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/BackGround/SnwoBrothersLogo.bmp", L"back");
    CSceneManager::Get_Instance()->Stage_Change(CSceneManager::STAGE_ID::ST_MENU);

    //CSceneManager::Get_Instance()->Initialize();

}

void CMainGame::Update()
{
    // CObjectManager::Get_Instance()->Update();

    //CLineManager::Get_Instance()->Update();

    CSceneManager::Get_Instance()->Update();
}

void CMainGame::Late_Update()
{
    // CObjectManager::Get_Instance()->Late_Update();

    CSceneManager::Get_Instance()->Late_Update();

    CKeyManager::Get_Instance()->Key_Update();

    //CObjectManager::Get_Instance()->Late_Update();
}

void CMainGame::Render()
{
    ++m_iFPS;

    if (m_dwTime + 1000 < GetTickCount64())
    {
        swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);

        SetWindowText(g_hWnd, m_szFPS);

        m_iFPS = 0;
        m_dwTime = GetTickCount64();
    }


    HDC hBackDC = CBmpManager::Get_Instance()->Find_Img(L"Win_Back");
    HDC hGroundDC = CBmpManager::Get_Instance()->Find_Img(L"Win_Back");

    BitBlt(hBackDC, 0, 0, WINCX, WINCY, hGroundDC, 0, 0, SRCCOPY);

    CSceneManager::Get_Instance()->Render(hBackDC);


    BitBlt(m_DC, 0, 0, WINCX, WINCY, hBackDC, 0, 0, SRCCOPY);
    //CObjectManager::Get_Instance()->Render(m_DC);

   /* TCHAR	szCount[32] = L"";
    swprintf_s(szCount, L"X : %d, Y : %d", g_ptMouse.x, g_ptMouse.y);
    TextOut(m_DC, WINCX / 2 - 30, 50, szCount, lstrlen(szCount));*/
}

void CMainGame::Release()
{
    CSoundMgr::Get_Instance()->Destroy_Instance();

    CBmpManager::Get_Instance()->Destroy_Instance();

    CScrollManager::Get_Instance()->Destroy_Instance();

    CKeyManager::Get_Instance()->Destroy_Instance();

    CSceneManager::Get_Instance()->Destroy_Instance();

    CTileManager::Get_Instance()->Destroy_Instance();

    CObjectManager::Get_Instance()->Destroy_Instance();

    CLineManager::Get_Instance()->Destroy_Instance();

    CUiManager::Get_Instance()->Destroy_Instance();

    CSpawnManager::Get_Instance()->Destroy_Instance();

    CPlayerManager::Get_Instance()->Destroy_Instance();

    CMapManager::Get_Instance()->Destroy_Instance();

    CEffectManager::Get_Instance()->Destroy_Instance();

    ReleaseDC(g_hWnd, m_DC);
}
