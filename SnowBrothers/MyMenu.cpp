#include "pch.h"
#include "MyMenu.h"
#include "BmpManager.h"
#include "AbstractFactory.h"
#include "ObjectManager.h"
#include "KeyManager.h"
#include "TileManager.h"
#include "SceneManager.h"
#include "SoundMgr.h"
#include "MapManager.h"


CMyMenu::CMyMenu() : m_eCurState(INTRO_STATE::LOOPING), m_ePreState(INTRO_STATE::INTRO_END)
{
    ZeroMemory(&rcButton1, sizeof(RECT));
    ZeroMemory(&rcButton2, sizeof(RECT));
    ZeroMemory(&rcButton3, sizeof(RECT));
}

CMyMenu::~CMyMenu()
{
    Release();
}

void CMyMenu::Initialize()
{
    CMapManager::Get_Instance()->Initialize();

    CSoundMgr::Get_Instance()->PlayBGM(L"BGM_MainMenu.wav", 1.0f);
}

int CMyMenu::Update()
{
    return 0;
}

void CMyMenu::Late_Update()
{
    POINT ptMouse{};
    GetCursorPos(&ptMouse);
    ScreenToClient(g_hWnd, &ptMouse);

    if (CKeyManager::Get_Instance()->Key_Down('9'))
        CSceneManager::Get_Instance()->Scene_Change(CSceneManager::CSCENE_ID::SC_EDIT);

    if (CKeyManager::Get_Instance()->Key_Down('5'))
    {
        CMapManager::Get_Instance()->Loading_Scene(CSceneManager::STAGE_ID::ST_TUTO, 3);
         CSoundMgr::Get_Instance()->PlaySound(L"BGM_Stage01.wav", SOUND_BGM, 1.f);
    }

    if (CKeyManager::Get_Instance()->Key_Down('6'))
    {
        CSceneManager::Get_Instance()->Stage_Change(CSceneManager::STAGE_ID::ST_BOSS02);
    }

    CMapManager::Get_Instance()->Late_Update();
}

void CMyMenu::Render(HDC _hDC)
{
    CMapManager::Get_Instance()->Render(_hDC);
}

void CMyMenu::Release()
{
}

void CMyMenu::BackGround_Change()
{
    if (m_ePreState != m_eCurState)
    {
        switch (m_eCurState)
        {
        case INTRO_STATE::IDLE:
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 0;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 200;
            m_tFrame.dwTime = GetTickCount64();
            break;

        case INTRO_STATE::LOOPING:
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 21;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 40;
            m_tFrame.dwTime = GetTickCount64();
            break;
        }
        m_ePreState = m_eCurState;
    }
}

