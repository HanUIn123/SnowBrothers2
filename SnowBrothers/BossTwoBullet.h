#pragma once
#include "Object.h"
class CBossTwoBullet : public CObject
{
public:
	enum class BULLET_STATE {IDLE, END };

public:
    CBossTwoBullet();
    virtual ~CBossTwoBullet();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;


public:
	void BulletAnimation();
	void BulletMoveFrame();

	bool Get_FirstCreate() { return m_bFirstCreate; }
	void Set_FirstCreate(bool _bFirstCreate) { m_bFirstCreate = _bFirstCreate; }



public:
	int m_iDirection;
	ULONGLONG	m_dwBossMissileExistingTime;
	
	BULLET_STATE m_eBulletCurState;
	BULLET_STATE m_eBulletPreState;

	bool		m_bFirstCreate;


	ULONGLONG	m_dwBulletExistingTimeWithNose;




	bool		m_bIsUnder;


	float		m_fPlayerPosY;

};

