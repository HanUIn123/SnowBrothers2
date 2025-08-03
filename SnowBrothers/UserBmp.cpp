#include "pch.h"
#include "UserBmp.h"

CUserBmp::CUserBmp() : 
    m_hMemDC(nullptr),
    m_hBitmap(nullptr),
    m_hOldbmp(nullptr)
{
}

CUserBmp::~CUserBmp()
{
}

void CUserBmp::Load_Bmp(const TCHAR* _pFilePath)
{
    HDC         hDC = GetDC(g_hWnd);

    m_hMemDC = CreateCompatibleDC(hDC);

    ReleaseDC(g_hWnd, hDC);

    m_hBitmap = (HBITMAP)LoadImage(NULL, _pFilePath,
        IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

    m_hOldbmp = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);
}

void CUserBmp::Release()
{
    SelectObject(m_hMemDC, m_hOldbmp);
    DeleteObject(m_hBitmap);
    DeleteDC(m_hMemDC);
}
