#include "pch.h"
#include "SpawnManager.h"

#include "KeyManager.h"

CSpawnManager* CSpawnManager::m_pInstance = nullptr;

CSpawnManager::CSpawnManager() :
    m_iNowSpawn_MonsterType((UINT)MONSTER_SPAWNER::NONE),
    m_iMonsterCount(0)
{
    m_dwCheckDeadMonsterTime = GetTickCount64();
}

CSpawnManager::~CSpawnManager()
{
    Release();
}

void CSpawnManager::Initialize()
{
}

void CSpawnManager::Update()
{


    Set_Spawner();
}

void CSpawnManager::Late_Update()
{
}

void CSpawnManager::Render(HDC _hDC)
{
    for (auto& pSpawner : m_SpawnList)
    {
        pSpawner->Render(_hDC);
    }
}

void CSpawnManager::Release()
{
    for_each(m_SpawnList.begin(), m_SpawnList.end(), Safe_Delete<CSpawn*>);
    m_SpawnList.clear();
}

void CSpawnManager::KeyCommand()
{
    //// 정보 저장
    //if (CKeyManager::Get_Instance()->Key_Down('S'))
    //{
    //	Save_Spawner();
    //	return;
    //}


    if (CKeyManager::Get_Instance()->Key_Down('1'))
    {
        m_iNowSpawn_MonsterType = (UINT)MONSTER_SPAWNER::NONE;
    }
    if (CKeyManager::Get_Instance()->Key_Down('2'))
    {
        m_iNowSpawn_MonsterType = (UINT)MONSTER_SPAWNER::MONSTERONE;
    }
    if (CKeyManager::Get_Instance()->Key_Down('3'))
    {
        m_iNowSpawn_MonsterType = (UINT)MONSTER_SPAWNER::MONSTERTWO;
    }
    if (CKeyManager::Get_Instance()->Key_Down('4'))
    {
        m_iNowSpawn_MonsterType = (UINT)MONSTER_SPAWNER::MONSTERTHREE;
    }
}

void CSpawnManager::Save_Spawner()
{
    HANDLE hFile =
        CreateFile
        (
            L"../Data/Spawner.dat",
            GENERIC_WRITE,
            NULL,
            NULL,
            CREATE_ALWAYS,
            FILE_ATTRIBUTE_NORMAL,
            NULL
        );

    if (INVALID_HANDLE_VALUE == hFile)
    {
        MessageBox(g_hWnd, L"Save File", _T("Fail"), MB_OK);
        return;
    }

    DWORD	dwByte(0);

    for (auto& pSpawn : m_SpawnList)
    {
        WriteFile(hFile, &(pSpawn->Get_SpawnerInfo()), sizeof(tagSpawnerInfo), &dwByte, nullptr);
    }

    CloseHandle(hFile);

    MessageBox(g_hWnd, L"Spawn Save 완료", _T("성공"), MB_OK);


}

void CSpawnManager::Load_Spawner(int _iStageNum)
{
    // 스테이지 1
    if (_iStageNum == 1)
    {
        HANDLE hFile =
            CreateFile
            (
                L"../Data/Stage1Data/Spawner.dat",
                GENERIC_READ,
                NULL,
                NULL,
                OPEN_EXISTING,
                FILE_ATTRIBUTE_NORMAL,
                NULL
            );

        if (INVALID_HANDLE_VALUE == hFile)
        {
            MessageBox(g_hWnd, L"Load File", _T("Fail"), MB_OK);
            return;
        }

        DWORD	dwByte(0);
        tagSpawnerInfo	vSpawner{};

        while (true)
        {
            ReadFile(hFile, &vSpawner, sizeof(tagSpawnerInfo), &dwByte, nullptr);

            if (0 == dwByte)
                break;

            m_SpawnList.push_back(new CSpawn(vSpawner));
        }

        CloseHandle(hFile);

        //MessageBox(g_hWnd, L"Load 완료", _T("성공"), MB_OK);
    }


    // 스테이지 2
    if (_iStageNum == 2)
    {
        HANDLE hFile =
            CreateFile
            (
                L"../Data/Stage2Data/Spawner.dat",
                GENERIC_READ,
                NULL,
                NULL,
                OPEN_EXISTING,
                FILE_ATTRIBUTE_NORMAL,
                NULL
            );

        if (INVALID_HANDLE_VALUE == hFile)
        {
            MessageBox(g_hWnd, L"Load File", _T("Fail"), MB_OK);
            return;
        }

        DWORD	dwByte(0);
        tagSpawnerInfo	vSpawner{};

        while (true)
        {
            ReadFile(hFile, &vSpawner, sizeof(tagSpawnerInfo), &dwByte, nullptr);

            if (0 == dwByte)
                break;

            m_SpawnList.push_back(new CSpawn(vSpawner));
        }

        CloseHandle(hFile);

       // MessageBox(g_hWnd, L"Load 완료", _T("성공"), MB_OK);
    }

}

void CSpawnManager::Set_Spawner()
{
    GetCursorPos(&g_ptMouse);

    ScreenToClient(g_hWnd, &g_ptMouse);

    if (CKeyManager::Get_Instance()->Key_Down(VK_LBUTTON))
    {
        //POINT pt = g_ptMouse;
        //float ptX = (float)pt.x;
        //float ptY = (float)pt.y;

        //if (CLineManager::GetInstance()->GetMinPositionX() > pt.x)
        //	pt.x = CLineManager::GetInstance()->GetMinPositionX();

        m_SpawnList.push_back(new CSpawn(m_iNowSpawn_MonsterType, float(g_ptMouse.x), float(g_ptMouse.y)));
    }
}
