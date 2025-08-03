#pragma once
#include "Scene.h"
#include "SceneManager.h"

class CMapManager
{
public:
    enum class MAPSCENE_STATE { IDLE, INTRO_LOOPING, LOADING_SCENE, STAGE01_TO_BOSSTWO,INTRO_STAGE01, CHAPTER_CHANGE, NO_LOADING, INTRO_END };
public:
    CMapManager();
    ~CMapManager();

public:
    void Initialize();
    void Update();
    void Late_Update();
    void Render(HDC _hDC);
    void Release();

public:
    void		Move_Frame();
    void        Menu_BackGround_Frame();
    void        Loading_Scene(CSceneManager::STAGE_ID _eStageName, int _iStageNum);

    void        Check_FrameIndex();
    void        Set_SceneIdle() { m_eCurState = MAPSCENE_STATE::IDLE; }

public:
    static CMapManager* Get_Instance()
    {
        if (!m_pInstance)
            m_pInstance = new CMapManager;

        return m_pInstance;
    }

    static void Destroy_Instance()
    {
        if (m_pInstance)
        {
            delete m_pInstance;
            m_pInstance = nullptr;
        }
    }

private:
    static CMapManager* m_pInstance;

    FRAME                       m_tFrame;
    const TCHAR*                m_pFrameKey;


    MAPSCENE_STATE m_eCurState;
    MAPSCENE_STATE m_ePreState;
    
    CSceneManager::STAGE_ID m_eStageID;


    bool            m_playOnce;


    bool            m_bStageOne;

};

