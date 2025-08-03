#pragma once
#include "Object.h"
class CItem : public CObject
{
public:
    CItem();
    CItem(float _fX,float _fY, float _fCX, float _fCY, const TCHAR* _pName);

    virtual ~CItem();
public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC _hDC) override;
    virtual void Release() override;

protected:
};

