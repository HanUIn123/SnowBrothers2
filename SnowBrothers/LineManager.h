#pragma once
#include "Line.h"
#include "Object.h"

class CLineManager
{
private:
    CLineManager();
    ~CLineManager();

public:
    void		Initialize();
    void        Update();
    void		Render(HDC hDC);
    void		Release();

public:
    //bool Collision_Line(float _fX, float* pY);
    bool Collision_Line(float _fX, float _fY, float* pY);

    void Draw_Line(POINT _ptMouse);
    void Save_Line();
    void Load_Line(int _iMapNumber);

private:

    


public:
    static CLineManager* Get_Instance()
    {
        if (!m_pInstance)
            m_pInstance = new CLineManager;

        return m_pInstance;
    }

    static void			Destroy_Instance()
    {
        if (m_pInstance)
        {
            delete m_pInstance;
            m_pInstance = nullptr;
        }
    }

private:
    LINEPOINT   m_tLinePoint[END];

    list<CLine*>			m_LineList;
    static CLineManager* m_pInstance;


};

