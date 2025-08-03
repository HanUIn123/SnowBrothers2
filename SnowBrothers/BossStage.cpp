#include "pch.h"
#include "BossStage.h"
#include "ObjectManager.h"
#include "KeyManager.h"
#include "BmpManager.h"
#include "AbstractFactory.h"

#include "Player.h"
#include "Bullet.h"
#include "Item.h"
#include "Life.h"
#include "BossOne.h"
#include "Minions.h"


#include "CollisionManager.h"
#include "LineManager.h"
#include "TileManager.h"
#include "UiManager.h"
#include "SpawnManager.h"
#include "PlayerManager.h"

#include "MapManager.h"
#include "BossOneHp.h"

#include "EffectManager.h"



CBossStage::CBossStage() :
    m_pPlayerClass(nullptr),
    m_pItemClass(nullptr),
    pBossOne(nullptr)
{
}

CBossStage::~CBossStage()
{
    Release();
}

void CBossStage::Initialize()
{
    CMapManager::Get_Instance()->Set_SceneIdle();

    CLineManager::Get_Instance()->Initialize();

    CEffectManager::Get_Instance()->Initialize();

    CObjectManager::Get_Instance()->Add_Object(OBJECT_LIST::PLAYER, CAbstractFactory<CPlayer>::Create());

    m_pPlayerClass = CObjectManager::Get_Instance()->Get_ObjectList(OBJECT_LIST::PLAYER).front();

    CSoundMgr::Get_Instance()->PlaySound(L"BossOneBGM.wav", SOUND_BGM, 1.f);

    CPlayerManager::Get_Instance()->Set_PlayerInfo(CPlayerManager::Get_Instance()->Get_PlayerPosX(),
        CPlayerManager::Get_Instance()->Get_PlayerPosY(), CPlayerManager::Get_Instance()->Get_PlayerSpeed());

    m_pPlayerClass->Set_Pos(80.0f, 500.0f);
    m_pPlayerClass->Set_Speed(5.5f);

    dynamic_cast<CPlayer*>(m_pPlayerClass)->Set_UpgradeBullet(CPlayerManager::Get_Instance()->Get_PlayerPower());

    dynamic_cast<CPlayer*>(m_pPlayerClass)->Set_Life(CUiManager::Get_Instance()->Get_PlayerLifeCount());

    pBossOne = new CBossOne;
    pBossOne->Initialize();

    CObjectManager::Get_Instance()->Add_Object(OBJECT_LIST::BOSS, pBossOne);

    dynamic_cast<CBossOne*>(pBossOne)->Set_TargetPlayer(m_pPlayerClass);

    MinionList = CObjectManager::Get_Instance()->Get_ObjectList(OBJECT_LIST::MINION);

    for (auto iter = MinionList.begin(); iter != MinionList.end(); ++iter)
    {
        dynamic_cast<CMonster*>(*iter)->Set_TargetPlayer(m_pPlayerClass);

        dynamic_cast<CPlayer*>(m_pPlayerClass)->Set_TargeetMonster(*iter);
    }

    CUiManager::Get_Instance()->Add_UI(UI_LIST::UI_LIFE, CAbstractFactory<CLife>::Create_UI());

    CLineManager::Get_Instance()->Load_Line(2);
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/BackGround/back.bmp", L"Map01Back");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/BackGround/bossStage.bmp", L"BossStage");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Tile/Tile04.bmp", L"Tile");

    CUiManager::Get_Instance()->Add_UI(UI_LIST::UI_HPBAR, CAbstractFactory<CBossOneHp>::Create_UI());

    CTileManager::Get_Instance()->Load_Tile(2);
}

int CBossStage::Update()
{
    CObjectManager::Get_Instance()->Update();

    CTileManager::Get_Instance()->Update();

    CUiManager::Get_Instance()->Update();

    Go_Next();

    return 0;
}

void CBossStage::Late_Update()
{
    CObjectManager::Get_Instance()->Late_Update();

    CTileManager::Get_Instance()->Late_Update();

    CUiManager::Get_Instance()->Late_Update();

    CMapManager::Get_Instance()->Late_Update();

    CEffectManager::Get_Instance()->Late_Update();
}

void CBossStage::Render(HDC _hDC)
{
    HDC	hGroundDC = CBmpManager::Get_Instance()->Find_Img(L"BossStage");

    BitBlt(_hDC, 0, 0, WINCX, WINCY, hGroundDC, 0, 0, SRCCOPY);

    CTileManager::Get_Instance()->Render(_hDC);

    CUiManager::Get_Instance()->Render(_hDC);

    CObjectManager::Get_Instance()->Render(_hDC);

    CEffectManager::Get_Instance()->Render(_hDC);

    CMapManager::Get_Instance()->Render(_hDC);
}

void CBossStage::Release()
{
    CTileManager::Get_Instance()->Destroy_Instance();

    CPlayerManager::Get_Instance()->Set_PlayerInfo(m_pPlayerClass->Get_ObjectInfo().fX, m_pPlayerClass->Get_ObjectInfo().fY, m_pPlayerClass->Get_Speed()/*, m_pPlayerClass->Get_Direction()*/);
    CPlayerManager::Get_Instance()->Set_PlayerPower(dynamic_cast<CPlayer*>(m_pPlayerClass)->Get_UpgradeBullet());

    CPlayerManager::Get_Instance()->Set_PlayerLifeCount(dynamic_cast<CPlayer*>(m_pPlayerClass)->Get_Life());

    CObjectManager::Get_Instance()->Destroy_Instance();

    CLineManager::Get_Instance()->Destroy_Instance();

    CUiManager::Get_Instance()->Get_PlayerLifeCount();

    CUiManager::Get_Instance()->Destroy_Instance();
}

void CBossStage::Go_Next()
{
    if (dynamic_cast<CBossOne*>(pBossOne)->Get_CurrentBossOneHp() <= 0)
    {
       // CMapManager::Get_Instance()->Loading_Scene(CSceneManager::STAGE_ID::ST_02, 3);
      /*  CMapManager::Get_Instance()->Loading_Scene(CSceneManager::STAGE_ID::ST_02, 4);*/


    }
}
