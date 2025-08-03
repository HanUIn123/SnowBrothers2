#pragma once

#include "Spawn.h"

class CSpawnManager
{
private:
    CSpawnManager();
    ~CSpawnManager();

public:
	void Initialize();
	void Update();
	void Late_Update();
	void Render(HDC _hDC);
	void Release();

public:
    void Set_Spawner();
    void Save_Spawner();
    void Load_Spawner(int _iStageNum);

    list<CSpawn*> Get_SpawnList() { return m_SpawnList; }


    int  Get_MonsterCount() { return m_iMonsterCount; }
    void Set_MonsterCount(int _iMonsterCount) { m_iMonsterCount = _iMonsterCount; }
    void Increase_MonsterCount(int _iMonsterCount) { m_iMonsterCount += _iMonsterCount; }
    void Decrease_MonsterCount(int _iMonsterCount) { m_iMonsterCount -= _iMonsterCount;  m_dwCheckDeadMonsterTime = GetTickCount64(); }

    void Reset_MonsterCount() { m_iMonsterCount = 5; }

    ULONGLONG   Get_CheckDeadMonsterTime() { return m_dwCheckDeadMonsterTime; }
    void Set_CheckDeadMonsterTime(ULONGLONG _uCheckDeadMonsterTime) { m_dwCheckDeadMonsterTime = _uCheckDeadMonsterTime; }


private:
    void KeyCommand();

   



    list<CSpawn*> m_SpawnList;

public:
    static CSpawnManager* Get_Instance()
    {
        if (!m_pInstance)
            m_pInstance = new CSpawnManager;

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
    static CSpawnManager* m_pInstance;

    int m_iNowSpawn_MonsterType;


private:
    int m_iMonsterCount;

    ULONGLONG       m_dwCheckDeadMonsterTime;

};

