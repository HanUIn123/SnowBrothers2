#pragma once
#include "Scene.h"
class CMyMenu : public CScene
{
public: 
	enum class INTRO_STATE { IDLE, LOOPING , INTRO_END };

public:
	CMyMenu();
	virtual ~CMyMenu();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

private:
	void	BackGround_Change();

private:
	RECT rcButton1;
	RECT rcButton2;
	RECT rcButton3;		//stage 1

	INTRO_STATE m_eCurState;
	INTRO_STATE m_ePreState;
};

