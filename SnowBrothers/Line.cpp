#include "pch.h"
#include "Line.h"
#include "ScrollManager.h"

CLine::CLine()
{
}

CLine::CLine(LINEPOINT& _tLeft, LINEPOINT& _tRight)
	: m_tInfo(_tLeft, _tRight)
{
}

CLine::CLine(LINE& _tLine) :
	m_tInfo(_tLine)
{
}

CLine::~CLine()
{
}

void CLine::Render(HDC hDC)
{

	MoveToEx(hDC, (int)m_tInfo.tLeft.fX, (int)m_tInfo.tLeft.fY, NULL);
	LineTo(hDC, (int)m_tInfo.tRight.fX, (int)m_tInfo.tRight.fY);
}
