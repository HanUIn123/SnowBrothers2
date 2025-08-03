#pragma once

#include "DefineCollection.h"

class CLine
{
public:
	CLine();
	CLine(LINEPOINT& _tLeft, LINEPOINT& _tRight);
	CLine(LINE& _tLine);
	~CLine();

public:
	const LINE& Get_Info() const { return m_tInfo; }

public:
	void		Render(HDC hDC);

private:
	LINE		m_tInfo;
};

