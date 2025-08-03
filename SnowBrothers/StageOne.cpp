#include "pch.h"
#include "StageOne.h"
#include "ObjectManager.h"
#include "BmpManager.h"
#include "TileManager.h"
#include "AbstractFactory.h"
#include "LineManager.h"
#include "UiManager.h"
#include "SpawnManager.h"
#include "KeyManager.h"


#include "MapManager.h"
#include "Minions.h"
#include "Player.h"
#include "Life.h"

#include "MonsterTwo.h"

#include "PlayerManager.h"
#include "SoundMgr.h"



CStageOne::CStageOne() :
    m_pPlayerClass(nullptr),
    m_bIsGoNextStage(false)
{
}

CStageOne::~CStageOne()
{
    Release();
}

void CStageOne::Initialize()
{
    CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
    CSoundMgr::Get_Instance()->PlayBGM(L"BGM_Stage01.wav", 1.0f);
    CMapManager::Get_Instance()->Set_SceneIdle();

    CLineManager::Get_Instance()->Initialize();

    CObjectManager::Get_Instance()->Add_Object(OBJECT_LIST::PLAYER,
        CAbstractFactory<CPlayer>::Create());

    m_pPlayerClass = CObjectManager::Get_Instance()->Get_ObjectList(OBJECT_LIST::PLAYER).front();

    m_pPlayerClass->Set_Pos(80.0f, 520.0f);
    m_pPlayerClass->Set_Speed(4.5f);

    dynamic_cast<CPlayer*>(m_pPlayerClass)->Set_UpgradeBullet(CPlayerManager::Get_Instance()->Get_PlayerPower());

    CUiManager::Get_Instance()->Add_UI(UI_LIST::UI_LIFE, CAbstractFactory<CLife>::Create_UI());
    dynamic_cast<CPlayer*>(m_pPlayerClass)->Set_Life(CPlayerManager::Get_Instance()->Get_PlayerLifeCount());

    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/BackGround/back.bmp", L"Map01Back");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/BackGround/Stage102.bmp", L"Stage102");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Tile/Tile04.bmp", L"Tile");

    CTileManager::Get_Instance()->Load_Tile(4);

    CSpawnManager::Get_Instance()->Reset_MonsterCount();

    CSpawnManager::Get_Instance()->Load_Spawner(2);

    list<CSpawn*> SpawnList = CSpawnManager::Get_Instance()->Get_SpawnList();

    for (auto iter : SpawnList)
    {
        CObjectManager::Get_Instance()->Add_Object(OBJECT_LIST::MONSTER, CAbstractFactory<CMonsterTwo>::Create(
            (*iter).Get_SpawnerInfo().fX, (*iter).Get_SpawnerInfo().fY, OBJECT_DIRECTION::DIR_END));
    }


    list<CObject*> MonsterList = CObjectManager::Get_Instance()->Get_ObjectList(OBJECT_LIST::MONSTER);

    for (auto iter = MonsterList.begin(); iter != MonsterList.end(); ++iter)
    {
        dynamic_cast<CMonsterTwo*>(*iter)->Set_TargetPlayer(m_pPlayerClass);

        dynamic_cast<CPlayer*>(m_pPlayerClass)->Set_TargeetMonster(*iter);
    }
}

int CStageOne::Update()
{
    CObjectManager::Get_Instance()->Update();

    CTileManager::Get_Instance()->Update();

    CUiManager::Get_Instance()->Update();

    return 0;
}

void CStageOne::Late_Update()
{
    CObjectManager::Get_Instance()->Late_Update();

    CTileManager::Get_Instance()->Late_Update();

    CMapManager::Get_Instance()->Late_Update();

    CUiManager::Get_Instance()->Late_Update();

    Go_Next();
}

void CStageOne::Render(HDC _hDC)
{
    HDC	hGroundDC = CBmpManager::Get_Instance()->Find_Img(L"Stage102");

    BitBlt(_hDC, 0, 0, WINCX, WINCY, hGroundDC, 0, 0, SRCCOPY);

    CTileManager::Get_Instance()->Render(_hDC);

    CObjectManager::Get_Instance()->Render(_hDC);

    CUiManager::Get_Instance()->Render(_hDC);

    CMapManager::Get_Instance()->Render(_hDC);
}

void CStageOne::Release()
{
    CTileManager::Get_Instance()->Destroy_Instance();

    CPlayerManager::Get_Instance()->Set_PlayerInfo(m_pPlayerClass->Get_ObjectInfo().fX, m_pPlayerClass->Get_ObjectInfo().fY, m_pPlayerClass->Get_Speed()/*, dynamic_cast<CPlayer*>(m_pPlayerClass)->Get_Direction()*/);
    CPlayerManager::Get_Instance()->Set_PlayerPower(dynamic_cast<CPlayer*>(m_pPlayerClass)->Get_UpgradeBullet());

    CObjectManager::Get_Instance()->Destroy_Instance();

    CUiManager::Get_Instance()->Get_PlayerLifeCount();
}

void CStageOne::Go_Next()
{
    if (CSpawnManager::Get_Instance()->Get_MonsterCount() <= 3 && !m_bIsGoNextStage)
    {
        CMapManager::Get_Instance()->Loading_Scene(CSceneManager::STAGE_ID::ST_BOSS02, 2);
        m_bIsGoNextStage = true;
    }
}
