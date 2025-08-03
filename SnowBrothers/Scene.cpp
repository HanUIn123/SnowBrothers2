#include "pch.h"
#include "Scene.h"
#include "SceneManager.h"

CScene::CScene() : 
	m_pFrameKey(nullptr)
{
	ZeroMemory(&m_tFrame, sizeof(FRAME));
}

void CScene::Initialize()
{
}

int CScene::Update()
{
    return 0;
}

void CScene::Late_Update()
{
}

void CScene::Render(HDC _hDC)
{
}

void CScene::Release()
{
}

void CScene::Move_Frame()
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount64())
	{
		++m_tFrame.iStart;

		if (m_tFrame.iStart > m_tFrame.iEnd)
			m_tFrame.iStart = 0;

		m_tFrame.dwTime = GetTickCount64();
	}
}

void CScene::Move_To_Next_Scene()
{
}
