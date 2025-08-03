#pragma once
#include "DefineCollection.h"

class CSpawn
{
public:
	CSpawn();
	CSpawn(tagSpawnerInfo& _tSpawn);
	CSpawn(int _iMonsterType, float _fMouseX, float _fMouseY);
	~CSpawn();

public:
	tagSpawnerInfo& Get_SpawnerInfo() { return m_tInfo; }

public:
	void		Render(HDC _hDC);

private:
	tagSpawnerInfo		m_tInfo;
	const int			m_iSpanwerSize;
};

