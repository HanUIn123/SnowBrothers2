#pragma once
#include "Object.h"
#include "UI.h"
#include "Item.h"

template<typename T>
class CAbstractFactory
{
public:
    CAbstractFactory() {}
    ~CAbstractFactory() {}
public:
	static CObject* Create()
	{
		CObject* pObject = new T;
		pObject->Initialize();

		return pObject;
	}

	static CObject* Create(float _fX, float _fY, OBJECT_DIRECTION _eDir)
	{
		CObject* pObject = new T;

		pObject->Initialize();
		pObject->Set_Pos(_fX, _fY);
		pObject->Set_Direction(_eDir);

		return pObject;
	}

	static CObject* Create(float _fX, float _fY)
	{
		CObject* pObject = new T;

		pObject->Initialize();
		pObject->Set_Pos(_fX, _fY);

		return pObject;
	}


	static CUI* Create_UI()
	{
		CUI* pUI = new T;
		pUI->Initialize();

		return pUI;
	}

	static CItem* Create_Item()
	{
		CItem* pItem = new CItem;
		pItem->Initialize();

		return pItem;
	}
};

