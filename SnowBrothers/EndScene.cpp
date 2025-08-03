#include "pch.h"
#include "EndScene.h"
#include "UiManager.h"
#include "AbstractFactory.h"
#include "Images.h"
#include "BmpManager.h"
#include "ObjectManager.h"
#include "TileManager.h"
#include "SoundMgr.h"



#include "BossOne.h"
#include "BossTwo.h"
#include "Player.h"



CEndScene::CEndScene()
{
}

CEndScene::~CEndScene()
{
    Release();
}

void CEndScene::Initialize()
{
    CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);

    CSoundMgr::Get_Instance()->PlayBGM(L"ending.wav", 1.0f);

    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/BackGround/back.bmp", L"Map01Back");

    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/BackGround/EndScene.bmp", L"EndScene");

    CUiManager::Get_Instance()->Add_UI(UI_LIST::UI_WORLDCLEAR, CAbstractFactory<CImages>::Create_UI());

    CObjectManager::Get_Instance()->Add_Object(OBJECT_LIST::PLAYER,
        CAbstractFactory<CPlayer>::Create());

    CObject* m_pPlayerClass = CObjectManager::Get_Instance()->Get_ObjectList(OBJECT_LIST::PLAYER).front();

    CMonster* pBossTwo = new CBossTwo;
    pBossTwo->Initialize();

    CObjectManager::Get_Instance()->Add_Object(OBJECT_LIST::BOSS, pBossTwo);

    CMonster* pBossOne = new CBossOne;
    pBossOne->Initialize();

    CObjectManager::Get_Instance()->Add_Object(OBJECT_LIST::BOSS, pBossOne);

    dynamic_cast<CBossTwo*>(pBossTwo)->Set_TargetPlayer(m_pPlayerClass);
    dynamic_cast<CBossOne*>(pBossOne)->Set_TargetPlayer(m_pPlayerClass);
    
    CTileManager::Get_Instance()->Load_Tile(5);

    dynamic_cast<CPlayer*>(m_pPlayerClass)->Set_UnlimitedSuperMode(true);
}

int CEndScene::Update()
{
    CUiManager::Get_Instance()->Update();

    CObjectManager::Get_Instance()->Update();

    return 0;
}

void CEndScene::Late_Update()
{
    CUiManager::Get_Instance()->Late_Update();

    CObjectManager::Get_Instance()->Late_Update();
}

void CEndScene::Render(HDC _hDC)
{
    HDC	hGroundDC = CBmpManager::Get_Instance()->Find_Img(L"EndScene");

    BitBlt(_hDC, 0, 0, WINCX, WINCY, hGroundDC, 0, 0, SRCCOPY);

    CUiManager::Get_Instance()->Render(_hDC);

    CObjectManager::Get_Instance()->Render(_hDC);
}

void CEndScene::Release()
{
}
