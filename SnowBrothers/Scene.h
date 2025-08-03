#pragma once
#include "DefineCollection.h"
class CScene
{
public:
	CScene();
	virtual ~CScene() {};

public:
	virtual void Initialize()		PURE;
	virtual int	 Update()			PURE;
	virtual void Late_Update()		PURE;
	virtual void Render(HDC _hDC)	PURE;
	virtual void Release()			PURE;

public:
	void		Move_Frame();

protected:
	FRAME                       m_tFrame;
	const TCHAR*				m_pFrameKey;
	void Move_To_Next_Scene();
};

