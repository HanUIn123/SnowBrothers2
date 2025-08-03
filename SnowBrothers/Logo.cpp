#include "pch.h"
#include "Logo.h"
#include "BmpManager.h"
#include "KeyManager.h"
#include "SceneManager.h"

CLogo::CLogo()
{
}

CLogo::~CLogo()
{
    Release();
}

void CLogo::Initialize()
{

}

int CLogo::Update()
{
    return 0;
}

void CLogo::Late_Update()
{
    if (CKeyManager::Get_Instance()->Key_Down(VK_RETURN))
    {
        //CSceneManager::Get_Instance()->Scene_Change(CSceneManager::CSCENE_ID::SC_MENU);
        return;
    }
}

void CLogo::Render(HDC _hDC)
{
    //HDC hMemDC = CBmpManager::Get_Instance()->Find_Img

    //BitBlt(_hDC, 0,0,WINCX,WINCY,)
}

void CLogo::Release()
{
}
