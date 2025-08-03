#pragma once
#include "Object.h"
class CBullet : public CObject
{
public:
	CBullet();
	virtual ~CBullet();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;


public:
	int m_iDirection;

	ULONGLONG m_dwStartFallingTime;

	ULONGLONG m_dwExistTime;
};

