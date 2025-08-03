#include "pch.h"
#include "Tutorial.h"
#include "ObjectManager.h"
#include "KeyManager.h"
#include "BmpManager.h"
#include "AbstractFactory.h"

#include "Player.h"
#include "Bullet.h"
#include "Item.h"
#include "MonsterOne.h"

#include "SpeedItem.h"
#include "PowerItem.h"
#include "RangeItem.h"



#include "Life.h"


#include "CollisionManager.h"
#include "LineManager.h"
#include "TileManager.h"
#include "UiManager.h"
#include "SpawnManager.h"
#include "PlayerManager.h"

#include "MapManager.h"

#include "EffectManager.h"

#include "SoundMgr.h"

#include "Images.h"

CTutorial::CTutorial() :
    m_pPlayerClass(nullptr),
    m_pItemClass(nullptr),
    m_bIsNextStage(false)
{
    m_dwMapMoveCoolTime = GetTickCount64();
}

CTutorial::~CTutorial()
{
    Release();
}

void CTutorial::Initialize()
{
    CMapManager::Get_Instance()->Set_SceneIdle();

    CLineManager::Get_Instance()->Initialize();

    CEffectManager::Get_Instance()->Initialize();

    CObjectManager::Get_Instance()->Add_Object(OBJECT_LIST::PLAYER,
        CAbstractFactory<CPlayer>::Create());

    CObjectManager::Get_Instance()->Add_Object(OBJECT_LIST::ITEM, CAbstractFactory<CSpeedItem>::Create());
    CObjectManager::Get_Instance()->Add_Object(OBJECT_LIST::ITEM, CAbstractFactory<CPowerItem>::Create());
    CObjectManager::Get_Instance()->Add_Object(OBJECT_LIST::ITEM, CAbstractFactory<CRangeItem>::Create());

    m_pPlayerClass = CObjectManager::Get_Instance()->Get_ObjectList(OBJECT_LIST::PLAYER).front();

    CUiManager::Get_Instance()->Add_UI(UI_LIST::UI_LIFE, CAbstractFactory<CLife>::Create_UI());

    CLineManager::Get_Instance()->Load_Line(1);
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/BackGround/back.bmp", L"Map01Back");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/BackGround/Stage101.bmp", L"Stage101");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Tile/Tile04.bmp", L"Tile");

    CTileManager::Get_Instance()->Load_Tile(1);

    CSpawnManager::Get_Instance()->Load_Spawner(1);

    list<CSpawn*> SpawnList = CSpawnManager::Get_Instance()->Get_SpawnList();

    for (auto iter : SpawnList)
    {
        CObjectManager::Get_Instance()->Add_Object(OBJECT_LIST::MONSTER, CAbstractFactory<CMonsterOne>::Create(
            (*iter).Get_SpawnerInfo().fX, (*iter).Get_SpawnerInfo().fY, OBJECT_DIRECTION::DIR_END));

        CSpawnManager::Get_Instance()->Increase_MonsterCount(1);
    }

    list<CObject*> MonsterList = CObjectManager::Get_Instance()->Get_ObjectList(OBJECT_LIST::MONSTER);

    for (auto iter = MonsterList.begin(); iter != MonsterList.end(); ++iter)
    {
        dynamic_cast<CMonster*>(*iter)->Set_TargetPlayer(m_pPlayerClass);

        dynamic_cast<CPlayer*>(m_pPlayerClass)->Set_TargeetMonster(*iter);
    }
}

int CTutorial::Update()
{
    CObjectManager::Get_Instance()->Update();

    CTileManager::Get_Instance()->Update();

    CUiManager::Get_Instance()->Update();

    return 0;
}

void CTutorial::Late_Update()
{
    Go_Boss();

    CObjectManager::Get_Instance()->Late_Update();

    CTileManager::Get_Instance()->Late_Update();

    CUiManager::Get_Instance()->Late_Update();

    CMapManager::Get_Instance()->Late_Update();

    CEffectManager::Get_Instance()->Late_Update();

    
}

void CTutorial::Render(HDC _hDC)
{
    HDC	hGroundDC = CBmpManager::Get_Instance()->Find_Img(L"Stage101");

    BitBlt(_hDC, 0, 0, WINCX, WINCY, hGroundDC, 0, 0, SRCCOPY);

    CTileManager::Get_Instance()->Render(_hDC);

    CUiManager::Get_Instance()->Render(_hDC);

    CObjectManager::Get_Instance()->Render(_hDC);

    CMapManager::Get_Instance()->Render(_hDC);

    CEffectManager::Get_Instance()->Render(_hDC);
}

void CTutorial::Release()
{
    CTileManager::Get_Instance()->Destroy_Instance();

    CPlayerManager::Get_Instance()->Set_PlayerInfo(m_pPlayerClass->Get_ObjectInfo().fX, m_pPlayerClass->Get_ObjectInfo().fY, m_pPlayerClass->Get_Speed()/*,m_pPlayerClass->Get_Direction()*/);
    CPlayerManager::Get_Instance()->Set_PlayerPower(dynamic_cast<CPlayer*>(m_pPlayerClass)->Get_UpgradeBullet());

    CUiManager::Get_Instance()->Get_PlayerLifeCount();

    CObjectManager::Get_Instance()->Destroy_Instance();

    CLineManager::Get_Instance()->Destroy_Instance();

    CSpawnManager::Get_Instance()->Destroy_Instance();
}

void CTutorial::Go_Boss()
{
    if (CSpawnManager::Get_Instance()->Get_MonsterCount() <= 0 && !m_bIsNextStage)
    {
        if (CSpawnManager::Get_Instance()->Get_CheckDeadMonsterTime() + 2000 < GetTickCount64())
        {
            CMapManager::Get_Instance()->Loading_Scene(CSceneManager::STAGE_ID::ST_BOSS01 , 1);
            CSoundMgr::Get_Instance()->PlaySound(L"StageMove.wav", SOUND_SCENE, 1.0f);
            m_bIsNextStage = true;
        }
    }
}

