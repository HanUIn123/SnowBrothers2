#pragma once
#include "Object.h"
class CTile : public CObject 
{
public:
    CTile();
    virtual ~CTile();

public:
    void Set_DrawID(int _iDrawID) { m_iDrawID = _iDrawID; }
    void Set_Option(int _iOption) { m_iOption = _iOption; }

    int Get_DrawID() { return m_iDrawID; }
    int Get_Option() { return m_iOption; }

public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC _hDC) override;
    virtual void Release() override;

private:
    int m_iDrawID;
    int m_iOption;

};

