#include "pch.h"
#include "SceneManager.h"

CSceneManager* CSceneManager::m_pInstance = nullptr;

CSceneManager::CSceneManager() : 
    m_eCurScene(CSCENE_ID::SC_LOGO),
    m_ePreScene(CSCENE_ID::SC_END),
    m_eCurStage(STAGE_ID::ST_END),
    m_ePreStage(STAGE_ID::ST_END),
    m_pScene(nullptr)
{
}

CSceneManager::~CSceneManager()
{
    Release();
}

void CSceneManager::Scene_Change(CSCENE_ID _eSceneID)
{
    m_eCurScene = _eSceneID;

    if (m_ePreScene != m_eCurScene)
    {
        Safe_Delete(m_pScene);

        switch (m_eCurScene)
        {
        case CSceneManager::CSCENE_ID::SC_LOGO:
            break;
        //case CSceneManager::CSCENE_ID::SC_MENU:
        //    m_pScene = new CMyMenu;
        //    break;
        case CSceneManager::CSCENE_ID::SC_EDIT:
            m_pScene = new CEdit;
            break;
        case CSceneManager::CSCENE_ID::SC_TUTO:
            m_pScene = new CTutorial;
            break;
        case CSceneManager::CSCENE_ID::SC_END:
            m_pScene = new CEndScene;
            break;
        }
        m_pScene->Initialize();

        m_ePreScene = m_eCurScene;
    }
}

void CSceneManager::Stage_Change(STAGE_ID _eStageID)
{
    m_eCurStage = _eStageID;

    if (m_ePreStage != m_eCurStage)
    {
        Safe_Delete(m_pScene);

        switch (m_eCurStage)
        {
        case CSceneManager::STAGE_ID::ST_MENU:
            m_pScene = new CMyMenu;
            break;
        case CSceneManager::STAGE_ID::ST_TUTO:
            m_pScene = new CTutorial;
            break;
        case CSceneManager::STAGE_ID::ST_02:
            m_pScene = new CStageOne;
            break;
        case CSceneManager::STAGE_ID::ST_BOSS01:
            m_pScene = new CBossStage;
            break;
        case CSceneManager::STAGE_ID::ST_BOSS02:
            m_pScene = new CBossStageTwo;
            break;
        case CSceneManager::STAGE_ID::ST_END:
            m_pScene = new CEndScene;
            break;
        }
        m_pScene->Initialize();

        m_ePreStage = m_eCurStage;
    }
}

void CSceneManager::Initialize()
{

}

void CSceneManager::Update()
{
    m_pScene->Update();
}

void CSceneManager::Late_Update()
{
    if (m_pScene)
        m_pScene->Late_Update();
}

void CSceneManager::Render(HDC _hDC)
{
    m_pScene->Render(_hDC);
}

void CSceneManager::Release()
{
    Safe_Delete(m_pScene);
}
