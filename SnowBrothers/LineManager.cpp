#include "pch.h"
#include "LineManager.h"
#include "ObjectManager.h"
#include "KeyManager.h"
#include "ScrollManager.h"

CLineManager* CLineManager::m_pInstance = nullptr;

CLineManager::CLineManager()
{
}


CLineManager::~CLineManager()
{
	Release();
}

void CLineManager::Initialize()
{
}

void CLineManager::Update()
{
}

void CLineManager::Render(HDC hDC)
{
	for (auto& pLine : m_LineList)
		pLine->Render(hDC);
}

void CLineManager::Release()
{
	for_each(m_LineList.begin(), m_LineList.end(), tagDelete());
	m_LineList.clear();
}

bool CLineManager::Collision_Line(float _fX, float _fY, float* pY)
{
	if (m_LineList.empty())
		return false;

	//bool bCheck = true;
	//float fFarestLinefY = 0.f;
	//for (auto& pLine : m_LineList)
	//{
	//	if (pLine->Get_Info().tLeft.fX <= _fX
	//		&& pLine->Get_Info().tRight.fX >= _fX) 
	//	{
	//		float x1 = pLine->Get_Info().tLeft.fX;
	//		float y1 = pLine->Get_Info().tLeft.fY;
	//		float x2 = pLine->Get_Info().tRight.fX;
	//		float y2 = pLine->Get_Info().tRight.fY;
	//		float fCheck_Y = ((y2 - y1) / (x2 - x1)) * (_fX - x1) + y1;
	//		if (((fCheck_Y - _fY >= 0) && ((fFarestLinefY - _fY > fCheck_Y - _fY)) || (bCheck && fCheck_Y - _fY >= 0)))
	//		{
	//			fFarestLinefY = fCheck_Y;
	//			bCheck = false;
	//		}
	//	}
	//	else if (_fX < pLine->Get_Info().tLeft.fX || pLine->Get_Info().tRight.fX < _fX)
	//	{
	//		//m_pPlayerClass = CObjectManager::Get_Instance()->Get_ObjectList(OBJECT_LIST::PLAYER).front();	
	//		//m_pPlayerClass->Set_PosY(fFarestLinefY);
	//	}
	//}
	//if (!bCheck)
	//{
	//	*pY = fFarestLinefY;
	//	return true;
	//}
	//======================================================
	CLine* pTarget = nullptr;

	float minY(WINCY);

	for (auto& pLine : m_LineList)
	{
		float	x1 = pLine->Get_Info().tLeft.fX;
		float	x2 = pLine->Get_Info().tRight.fX;

		float	y1 = pLine->Get_Info().tLeft.fY;
		float	y2 = pLine->Get_Info().tRight.fY;

		float finalLineY(0.0f);

		finalLineY = ((y2 - y1) / (x2 - x1)) * (_fX - x1) + y1;

		if ((_fX >= pLine->Get_Info().tLeft.fX && pLine->Get_Info().tRight.fX > _fX))
		{
			if (finalLineY >= _fY)
			{
				if (finalLineY < minY)
				{
					pTarget = pLine;
					minY = finalLineY;
					*pY = minY;
				}
			}
		}
	}

	if (!pTarget)
		return false;

	return false;
}

void CLineManager::Load_Line(int _iMapNumber)
{
	if (_iMapNumber == 1)
	{
		HANDLE		hFile = CreateFile(L"../Data/Stage1Data/Line.dat",
			GENERIC_READ,
			NULL,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);


		if (INVALID_HANDLE_VALUE == hFile)
		{
			MessageBox(g_hWnd, L"Load File", _T("Fail"), MB_OK);
			return;
		}

		DWORD	dwByte(0);
		LINE	tLine{};

		while (true)
		{
			ReadFile(hFile, &tLine, sizeof(LINE), &dwByte, nullptr);

			if (0 == dwByte)
				break;

			m_LineList.push_back(new CLine(tLine));
		}

		CloseHandle(hFile);

		//MessageBox(g_hWnd, L"Load 완료", _T("성공"), MB_OK);
	}

	if (_iMapNumber == 2)
	{
		HANDLE		hFile = CreateFile(L"../Data/Line.dat",
			GENERIC_READ,
			NULL,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);


		if (INVALID_HANDLE_VALUE == hFile)
		{
			MessageBox(g_hWnd, L"Load File", _T("Fail"), MB_OK);
			return;
		}

		DWORD	dwByte(0);
		LINE	tLine{};

		while (true)
		{
			ReadFile(hFile, &tLine, sizeof(LINE), &dwByte, nullptr);

			if (0 == dwByte)
				break;

			m_LineList.push_back(new CLine(tLine));
		}

		CloseHandle(hFile);

		//MessageBox(g_hWnd, L"Load 완료", _T("성공"), MB_OK);
	}
	

}

void CLineManager::Draw_Line(POINT _ptMouse)
{
	int iScrollY = (int)CScrollManager::Get_Instance()->Get_ScrollY();

	//POINT		ptMouse{};
	GetCursorPos(&_ptMouse);
	ScreenToClient(g_hWnd, &_ptMouse);

	if (CKeyManager::Get_Instance()->Key_Down(VK_LBUTTON))
	{
		if (!(m_tLinePoint[LD_LEFT].fX) && !(m_tLinePoint[LD_LEFT].fY))
		{
			m_tLinePoint[LD_LEFT].fX = (float)_ptMouse.x;
			m_tLinePoint[LD_LEFT].fY = (float)_ptMouse.y - iScrollY;
		}
		else
		{
			// LinePoint[LEFT] 찍고, [RIGHT]도 마우스의 좌표로.
			m_tLinePoint[LD_RIGHT].fX = (float)_ptMouse.x;
			m_tLinePoint[LD_RIGHT].fY = (float)_ptMouse.y - iScrollY;

			// Line클래스 좌, 우 점 좌표 매개변수 생성자를 LineList의 원소로 Push_back
			m_LineList.push_back(new CLine(m_tLinePoint[LD_LEFT], m_tLinePoint[LD_RIGHT]));

			m_tLinePoint->fX = 0;
			m_tLinePoint->fY = 0;

			// =========================================================================
			// 위에서 점 두개 찍고 나면, 이제 그 RIGHT는 LEFT로 또 변경되버림.
			//m_tLinePoint[LD_LEFT].fX = (float)pt.x;
			//m_tLinePoint[LD_LEFT].fY = (float)pt.y;
		}
	}
}

void CLineManager::Save_Line()
{
	// file 개방
	HANDLE  hFile = CreateFile(L"../Data/Line.dat",
		GENERIC_WRITE,
		NULL,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	// INVALID_HANDLE_VALUE : -1 이라서, 파일 저장이 실패했다는 의미.
	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"Save Load File", _T("Fail"), MB_OKCANCEL);
		return;
	}

	DWORD       dwByte(0);

	// 리스트에 담긴 라인 전체를 저장하겠다..
	for (auto& pLine : m_LineList)
	{
		WriteFile(hFile, &(pLine->Get_Info()), sizeof(LINE), &dwByte, nullptr);
	}

	CloseHandle(hFile);

	MessageBox(g_hWnd, L"Save Load 완료", _T("성공"), MB_OK);

}

//bool CLineManager::Collision_Line(float _fX, float* pY)
//{
//	if (m_LineList.empty())
//		return false;
//
//	CLine* pTarget = nullptr;
//
//	for (auto& pLine : m_LineList)
//	{
//		if (_fX >= pLine->Get_Info().tLeft.fX && pLine->Get_Info().tRight.fX > _fX)
//		{
//			pTarget = pLine;
//		}
//	}
//
//	if (!pTarget)
//		return false;
//
//	float	x1 = pTarget->Get_Info().tLeft.fX;
//	float	x2 = pTarget->Get_Info().tRight.fX;
//
//	float	y1 = pTarget->Get_Info().tLeft.fY;
//	float	y2 = pTarget->Get_Info().tRight.fY;
//
//	*pY = ((y2 - y1) / (x2 - x1)) * (_fX - x1) + y1;
//
//	return true;
//}

