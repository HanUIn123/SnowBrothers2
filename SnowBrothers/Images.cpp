#include "pch.h"
#include "Images.h"
#include "BmpManager.h"
#include "UiManager.h"

CImages::CImages() : 
    m_eCurUISTATE(UI_STATE::IDLE),
    m_ePreUISTATE(UI_STATE::END)
{

}

CImages::~CImages()
{
    Release();
}

void CImages::Initialize()
{
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/BackGround/WorldClear.bmp", L"WorldClear");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Effect/Great.bmp", L"Great");






    m_tInfo = { WINCX / 2.0f - 260.0f ,50.0f, 500.0f,126.0f };

    m_pFrameKey = L"WorldClear";

    m_tFrame = { 0,2,0,1100,GetTickCount64() };
}

int CImages::Update()
{
    return 0;
}

void CImages::Late_Update()
{
    EndScene_FSM();
    EndScene_Animation();

    if (CUiManager::Get_Instance()->Get_GoNext())
    {
        m_eCurUISTATE = CImages::UI_STATE::GREAT;
    }



    Move_Frame();
}

void CImages::Render(HDC _hDC)
{
    HDC WorldClearDC = CBmpManager::Get_Instance()->Find_Img(L"WorldClear");

    GdiTransparentBlt(_hDC,
        //int(m_tRect.left),
        //int(m_tRect.top),
        int(m_tInfo.fX),
        int(m_tInfo.fY),
        int(500),
        int(126),
        WorldClearDC,
        int(m_tInfo.fCX * m_tFrame.iStart),
        int(m_tInfo.fCY * m_tFrame.iMotion),
        int(m_tInfo.fCX),
        int(m_tInfo.fCY),
        RGB(255, 0, 255));
}

void CImages::Release()
{
}

void CImages::EndScene_FSM()
{
    switch (m_eCurUISTATE)
    {
    case CImages::UI_STATE::IDLE:
        m_pFrameKey = L"WorldClear";
        break;
    case CImages::UI_STATE::GREAT:
        m_pFrameKey = L"Great";
        break;
    }
}

void CImages::EndScene_Animation()
{
    if (m_ePreUISTATE != m_eCurUISTATE)
    {
        switch (m_eCurUISTATE)
        {
        case UI_STATE::IDLE:
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 2;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 100;
            m_tFrame.dwTime = GetTickCount64();
            break;
        case UI_STATE::GREAT:
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 3;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 50;
            m_tFrame.dwTime = GetTickCount64();
            break;
        }
    }
    m_ePreUISTATE = m_eCurUISTATE;
}

void CImages::Move_Frame()
{
    if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount64())
    {
        ++m_tFrame.iStart;

        if (m_tFrame.iStart > m_tFrame.iEnd)
            m_tFrame.iStart = 0;

        m_tFrame.dwTime = GetTickCount64();
    }
}
