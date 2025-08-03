#pragma once
#include "DefineCollection.h"
#include "MyMenu.h"
#include "Edit.h"



#include "Tutorial.h"
#include "StageOne.h"
#include "BossStage.h"
#include "BossStageTwo.h"

#include "EndScene.h"

#include "SoundMgr.h"

class CSceneManager
{
public:
    enum class CSCENE_ID {SC_TUTO,SC_LOGO,  SC_EDIT, SC_SELECT_SCENE, SC_STAGE, SC_END};
    enum class STAGE_ID { ST_TUTO, ST_MENU, ST_BOSS01, ST_BOSS02, ST_01, ST_02, ST_03, ST_04, ST_END};
private:
    CSceneManager();
    ~CSceneManager();

public:
    void Scene_Change(CSCENE_ID _eSceneID);
    void Stage_Change(STAGE_ID _eStageID);
    void Initialize();
    void Update();
    void Late_Update();
    void Render(HDC _hDC);
    void Release();

public:
    static CSceneManager* Get_Instance()
    {
        if (!m_pInstance)
            m_pInstance = new CSceneManager;

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
    static CSceneManager*   m_pInstance;
    CScene*                 m_pScene;

    CSCENE_ID               m_eCurScene;
    CSCENE_ID               m_ePreScene;

    STAGE_ID                m_eCurStage;
    STAGE_ID                m_ePreStage;
};