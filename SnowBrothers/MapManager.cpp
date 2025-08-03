#include "pch.h"
#include "MapManager.h"
#include "BmpManager.h"


CMapManager* CMapManager::m_pInstance = nullptr;

CMapManager::CMapManager() :
    m_eCurState(MAPSCENE_STATE::INTRO_LOOPING),
    m_ePreState(MAPSCENE_STATE::INTRO_END),
    m_pFrameKey(nullptr),
    m_eStageID(CSceneManager::STAGE_ID::ST_END),
    m_playOnce(false),
    m_bStageOne(false)
{
    ZeroMemory(&m_tFrame, sizeof(FRAME));
}

CMapManager::~CMapManager()
{
}

void CMapManager::Initialize()
{
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/BackGround/Intro.bmp", L"Intro");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/BackGround/BackGroundFameImage/BackGroundFrame2.bmp", L"BackGroundFrame2");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/BackGround/BackGroundFameImage/BackGroundFrame3.bmp", L"BackGroundFrame3");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/BackGround/bossToStageOne.bmp", L"bossToStageOne");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/BackGround/MenuToStage1.bmp", L"MenuToStage1");

    m_pFrameKey = L"Intro";

    m_tFrame = { 0, 21, 0, 200, GetTickCount64() };
}

void CMapManager::Update()
{

}

void CMapManager::Late_Update()
{
    Menu_BackGround_Frame();
    Move_Frame();
    Check_FrameIndex();
}

void CMapManager::Render(HDC _hDC)
{
    HDC hMemDC = CBmpManager::Get_Instance()->Find_Img(m_pFrameKey);

    if (m_eCurState == MAPSCENE_STATE::INTRO_LOOPING || m_eCurState == MAPSCENE_STATE::LOADING_SCENE || m_eCurState == MAPSCENE_STATE::INTRO_STAGE01 
        || m_eCurState == MAPSCENE_STATE::CHAPTER_CHANGE)
    {
        GdiTransparentBlt(_hDC,
            int(0),
            int(0),
            int(800),
            int(600),
            hMemDC,
            int(800 * m_tFrame.iStart),
            int(600 * m_tFrame.iMotion),
            int(800),
            int(600),
            RGB(255, 0, 255));
    }
}

void CMapManager::Release()
{
}

void CMapManager::Move_Frame()
{
    if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount64())
    {
        ++m_tFrame.iStart;

        if (m_tFrame.iStart > m_tFrame.iEnd)
            m_tFrame.iStart = 0;

        m_tFrame.dwTime = GetTickCount64();
    }
}

void CMapManager::Menu_BackGround_Frame()
{
    if (m_ePreState != m_eCurState)
    {
        switch (m_eCurState)
        {
        case MAPSCENE_STATE::IDLE:
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 0;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 200;
            m_tFrame.dwTime = GetTickCount64();
            break;

        case MAPSCENE_STATE::INTRO_LOOPING:
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 21;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 40;
            m_tFrame.dwTime = GetTickCount64();
            break;

        case MAPSCENE_STATE::LOADING_SCENE:
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 20;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 40;
            m_tFrame.dwTime = GetTickCount64();
            if (m_bStageOne)
            {
                m_tFrame.iEnd = 18;
            }
            break;

        case MAPSCENE_STATE::INTRO_STAGE01:
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 15;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 40;
            m_tFrame.dwTime = GetTickCount64();
            break;

        case MAPSCENE_STATE::CHAPTER_CHANGE:
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 10;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 40;
            m_tFrame.dwTime = GetTickCount64();
            break;
        case MAPSCENE_STATE::NO_LOADING:
            break;
        }
        m_ePreState = m_eCurState;
    }
}

void CMapManager::Loading_Scene(CSceneManager::STAGE_ID _eStageName, int _iStageNum)
{
    m_playOnce = true;
    /*m_tFrame.iStart = 0;*/

    if (m_tFrame.iStart == 0)
    {
        CSoundMgr::Get_Instance()->PlaySound(L"StageMove.wav", SOUND_SCENE, 1.0f);
    }

 

    if (_iStageNum == 1)
    {
        m_eCurState = MAPSCENE_STATE::LOADING_SCENE;
        m_tFrame.iStart = 0;
        m_pFrameKey = L"BackGroundFrame2";
    }
    else if (_iStageNum == 2)
    {
        m_eCurState = MAPSCENE_STATE::LOADING_SCENE;
        m_bStageOne = true;
        m_tFrame.iStart = 0;
        m_pFrameKey = L"BackGroundFrame3";
    }
    else if (_iStageNum == 3)
    {
         m_eCurState = MAPSCENE_STATE::INTRO_STAGE01;
         m_tFrame.iStart = 0;
        m_pFrameKey = L"MenuToStage1";
    }
    else if (_iStageNum == 4)
    {
        m_eCurState = MAPSCENE_STATE::CHAPTER_CHANGE;
        m_tFrame.iStart = 0;
        m_pFrameKey = L"bossToStageOne";

    }

    m_eStageID = _eStageName;
}

void CMapManager::Check_FrameIndex()
{
    if (m_eCurState != MAPSCENE_STATE::NO_LOADING && m_playOnce)
    {
        if (m_tFrame.iStart >= m_tFrame.iEnd)
        {
            m_playOnce = false;
            m_tFrame.iStart = 0;
            //CSceneManager::Get_Instance()->Scene_Change(CSceneManager::CSCENE_ID::SC_TUTO);
            CSceneManager::Get_Instance()->Stage_Change(m_eStageID);

            m_eCurState = MAPSCENE_STATE::NO_LOADING;

        }
    }
}
