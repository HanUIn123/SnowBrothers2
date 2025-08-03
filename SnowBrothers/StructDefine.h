#pragma once
#include "pch.h"

struct tagUiInfo
{
    float fX;
    float fY;
    float fCX;
    float fCY;
};

struct tagObjectInfo
{
    float fX;
    float fY;
    float fCX;
    float fCY;
};

typedef struct tagFrame
{
    int		iStart;
    int		iEnd;
    int		iMotion;

    DWORD	    dwSpeed;
    ULONGLONG	dwTime;

}FRAME;

template<typename T>
void Safe_Delete(T& _pTemp)
{
    if (_pTemp)
    {
        delete _pTemp;
        _pTemp = nullptr;
    }
}

struct tagDeleteMap
{
    template<typename T>
    void operator()(T& MyPair)
    {
        if (MyPair.second)
        {
            delete MyPair.second;
            MyPair.second = nullptr;
        }
    }
};

struct tagDelete
{
    template<typename T>
    void operator()(T& Tmp)
    {
        if (Tmp)
        {
            delete Tmp;
            Tmp = nullptr;
        }
    }
};

class CTag_Finder
{
public:
    CTag_Finder(const TCHAR* _pString)
        : m_pString(_pString) {}
public:
    template<typename T>
    bool    operator()(T& MyPair)
    {
        return !lstrcmp(m_pString, MyPair.first);
    }

private:
    const TCHAR* m_pString;
};

typedef	struct tagLinePoint
{
    float	fX, fY;

    tagLinePoint() { ZeroMemory(this, sizeof(tagLinePoint)); }
    tagLinePoint(float _fX, float _fY) : fX(_fX), fY(_fY) {}

}LINEPOINT;

typedef struct tagLine
{
    LINEPOINT	tLeft;
    LINEPOINT	tRight;

    tagLine() { ZeroMemory(this, sizeof(tagLine)); }
    tagLine(LINEPOINT& _tLeft, LINEPOINT& _tRight) : tLeft(_tLeft), tRight(_tRight) {}

}LINE;

struct tagSpawnerInfo
{
    int iMonsterType;
    int iSubMonsterType;
    float fX;
    float fY;
    float fCX;
    float fCY;

    tagSpawnerInfo() { ZeroMemory(this, sizeof(tagSpawnerInfo)); }
    tagSpawnerInfo(int& _iMonsterType, float& _fX, float& _fY, float& _fCX, float& _fCY)
        : iMonsterType(_iMonsterType), fX(_fX), fY(_fY), fCX(_fCX), fCY(_fCY)
    {

    }
};