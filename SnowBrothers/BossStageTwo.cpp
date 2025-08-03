#include "pch.h"
#include "BossStageTwo.h"
#include "ObjectManager.h"
#include "KeyManager.h"
#include "BmpManager.h"
#include "AbstractFactory.h"

#include "Player.h"
#include "Bullet.h"
#include "Item.h"
#include "Life.h"
#include "BossTwo.h"

#include "CollisionManager.h"
#include "LineManager.h"
#include "TileManager.h"
#include "UiManager.h"
#include "SpawnManager.h"
#include "PlayerManager.h"

#include "MapManager.h"

#include "SoundMgr.h"

#include "BossTwoHp.h"


CBossStageTwo::CBossStageTwo() :
    m_pPlayerClass(nullptr),
    m_pItemClass(nullptr),
    pBossTwo(nullptr)
{
}

CBossStageTwo::~CBossStageTwo()
{
    Release();
}

void CBossStageTwo::Initialize()
{
    CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
    CSoundMgr::Get_Instance()->PlayBGM(L"BossOneBGM.wav", 1.0f);

    CObjectManager::Get_Instance()->Add_Object(OBJECT_LIST::PLAYER,
        CAbstractFactory<CPlayer>::Create());

    m_pPlayerClass = CObjectManager::Get_Instance()->Get_ObjectList(OBJECT_LIST::PLAYER).front();

    CPlayerManager::Get_Instance()->Set_PlayerInfo(CPlayerManager::Get_Instance()->Get_PlayerPosX(),
        CPlayerManager::Get_Instance()->Get_PlayerPosY(), CPlayerManager::Get_Instance()->Get_PlayerSpeed());

    m_pPlayerClass->Set_Pos(80.0f, 00.0f);
    m_pPlayerClass->Set_Speed(5.5f);
    dynamic_cast<CPlayer*>(m_pPlayerClass)->Set_UpgradeBullet(true);

    dynamic_cast<CPlayer*>(m_pPlayerClass)->Set_Life(CUiManager::Get_Instance()->Get_PlayerLifeCount());

    pBossTwo = new CBossTwo;
    pBossTwo->Initialize();

    CObjectManager::Get_Instance()->Add_Object(OBJECT_LIST::BOSS, pBossTwo);

    dynamic_cast<CBossTwo*>(pBossTwo)->Set_TargetPlayer(m_pPlayerClass);

    list<CObject*> MinionList = CObjectManager::Get_Instance()->Get_ObjectList(OBJECT_LIST::MINION);

    for (auto iter = MinionList.begin(); iter != MinionList.end(); ++iter)
    {
        dynamic_cast<CMonster*>(*iter)->Set_TargetPlayer(m_pPlayerClass);

        dynamic_cast<CPlayer*>(m_pPlayerClass)->Set_TargeetMonster(*iter);
    }

    CUiManager::Get_Instance()->Add_UI(UI_LIST::UI_LIFE, CAbstractFactory<CLife>::Create_UI());
    
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/BackGround/back.bmp", L"Map01Back");

    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/BackGround/BossStage2.bmp", L"BossStage2");

    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Tile/Tile04.bmp", L"Tile");

    CUiManager::Get_Instance()->Add_UI(UI_LIST::UI_HPBAR, CAbstractFactory<CBossTwoHp>::Create_UI());

    CTileManager::Get_Instance()->Load_Tile(3);
}

int CBossStageTwo::Update()
{
    CObjectManager::Get_Instance()->Update();

    CTileManager::Get_Instance()->Update();

    CUiManager::Get_Instance()->Update();

    return 0;
}

void CBossStageTwo::Late_Update()
{
    CObjectManager::Get_Instance()->Late_Update();

    CTileManager::Get_Instance()->Late_Update();

    CUiManager::Get_Instance()->Late_Update();

    CMapManager::Get_Instance()->Late_Update();


    Go_EndScene();
}

void CBossStageTwo::Render(HDC _hDC)
{
    HDC	hGroundDC = CBmpManager::Get_Instance()->Find_Img(L"BossStage2");

    BitBlt(_hDC, 0, 0, WINCX, WINCY, hGroundDC, 0, 0, SRCCOPY);

    CTileManager::Get_Instance()->Render(_hDC);

    CUiManager::Get_Instance()->Render(_hDC);

    CObjectManager::Get_Instance()->Render(_hDC);

    CMapManager::Get_Instance()->Render(_hDC);
}

void CBossStageTwo::Release()
{
    CTileManager::Get_Instance()->Destroy_Instance();

    CObjectManager::Get_Instance()->Destroy_Instance();

    CLineManager::Get_Instance()->Destroy_Instance();

    CUiManager::Get_Instance()->Destroy_Instance();
}

void CBossStageTwo::Go_EndScene()
{
    if (dynamic_cast<CBossTwo*>(pBossTwo)->Get_CurrentBossTwoHp() <= 0)
    {
        CSceneManager::Get_Instance()->Stage_Change(CSceneManager::STAGE_ID::ST_END);
    }
}
