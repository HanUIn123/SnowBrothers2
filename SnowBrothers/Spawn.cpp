#include "pch.h"
#include "Spawn.h"

CSpawn::CSpawn() : m_iSpanwerSize(10)
{
}

CSpawn::CSpawn(tagSpawnerInfo& _tSpawn)
    : m_iSpanwerSize(10), m_tInfo(_tSpawn)
{

}

CSpawn::CSpawn(int _iMonsterType, float _fMouseX, float _fMouseY) :
    m_iSpanwerSize(10)
{
    m_tInfo.fX = (float)g_ptMouse.x;
    m_tInfo.fY = (float)g_ptMouse.y;
}

CSpawn::~CSpawn()
{
}

void CSpawn::Render(HDC _hDC)
{
    const TCHAR* spawnName = L"";

    switch (m_tInfo.iMonsterType)
    {
    case (UINT)MONSTER_SPAWNER::MONSTERONE:
        spawnName = L"ENEMYONE";
        break;

    case (UINT)MONSTER_SPAWNER::MONSTERTWO:
        spawnName = L"ENEMYTWO";
        break;
    }

  

    Rectangle(_hDC,
        (LONG)m_tInfo.fX - m_iSpanwerSize,
        (LONG)m_tInfo.fY - m_iSpanwerSize,
        (LONG)m_tInfo.fX + m_iSpanwerSize,
        (LONG)m_tInfo.fY + m_iSpanwerSize


        //(LONG)g_ptMouse.x - m_iSpanwerSize,
        //(LONG)g_ptMouse.y - m_iSpanwerSize,
        //(LONG)g_ptMouse.x + m_iSpanwerSize,
        //(LONG)g_ptMouse.y + m_iSpanwerSize
    );

    TextOut(_hDC, (LONG)m_tInfo.fX, (LONG)m_tInfo.fY, spawnName, lstrlen(spawnName));
    //TextOut(_hDC, (LONG)g_ptMouse.x, (LONG)g_ptMouse.y, spawnName, lstrlen(spawnName));
}
