#pragma once
#include "DefineCollection.h"

class CMainGame
{
public:
    CMainGame();
    ~CMainGame();

public:
	void		Initialize();
	void		Update();
	void		Late_Update();
	void		Render();
	void		Release();

private:
	HDC			m_DC;
	ULONGLONG	m_dwTime;
	TCHAR		m_szFPS[16];
	int			m_iFPS;

};

