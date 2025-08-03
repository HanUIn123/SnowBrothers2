#pragma once
#include "Object.h"
class CMonsterTwoBullet : public CObject
{
public:
	enum class BULLET_STATE { IDLE, END };

public:
	CMonsterTwoBullet();
	virtual ~CMonsterTwoBullet();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;


public:
	void Monster_BulletAnimation();
	void Monster_BulletMoveFrame();

	bool Get_FirstCreate() { return m_bFirstCreate; }
	void Set_FirstCreate(bool _bFirstCreate) { m_bFirstCreate = _bFirstCreate; }



public:
	int m_iDirection;
	ULONGLONG	m_dwMonsterMissileExistingTime;

	BULLET_STATE m_eMonsterBulletCurState;
	BULLET_STATE m_eMonsterBulletPreState;

	bool		m_bFirstCreate;

	float		m_fPlayerPosY;
};

