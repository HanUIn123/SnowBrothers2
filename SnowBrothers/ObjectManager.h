#pragma once
#include "Object.h"

class CObjectManager
{
private:
    CObjectManager();
    ~CObjectManager();

public:
    void Add_Object(OBJECT_LIST _eObList, CObject* _pObject);

    list<CObject*> Get_ObjectList(OBJECT_LIST _eObjList) { return m_ObjectList[(UINT)_eObjList]; }

    int Update();
    void Late_Update();
    void Render(HDC _hDC);
    void Release();

public:
    void Object_Collision();

public:



public:
    static CObjectManager* Get_Instance()
    {
        if (!m_pInstance)
            m_pInstance = new CObjectManager;

        return m_pInstance;
    }

    static void Destroy_Instance()
    {
        if (m_pInstance)
        {
            delete m_pInstance;
            m_pInstance = nullptr;
        }
    }

private:
    static CObjectManager* m_pInstance;

private:
    list<CObject*> m_ObjectList[(UINT)OBJECT_LIST::OL_END];

private:
    ULONGLONG       m_dwPlayerTime;

private:
    CObject*        m_pObject;

private:
    int             m_iDrawIdNumber;
};

