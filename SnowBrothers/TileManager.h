#pragma once
#include "Tile.h"

class CTileManager
{
public:
    CTileManager();
    ~CTileManager();

public:
    void		Picking_Tile(POINT _ptMouse, int _iDrawID, int _iOption);
    void		Save_Tile();
    void		Load_Tile(int _iStageNum);
    void        Tile_Follow_MouseCursor(HDC _hDC, int _iScrollX, int _iScrollY);
    
    void        Show_TileList(HDC _hDC, int _iDrawID);

    void        Tile_Change(int _iDrawID);


    vector<CObject*> Get_TileVector() { return m_vecTile; }

    int         Get_DrawID() { return m_iDrawID; }
    int         Get_CurrentTileIndex() { return m_iCurrentTileIndex; }

    void        Change_DrawID(int _iDrawID);


public:
    void		Initialize();
    int		    Update();
    void		Late_Update();
    void		Render(HDC _hDC);
    void		Release();

public:
    static CTileManager* Get_Instance()
    {
        if (!m_pInstance)
        {
            m_pInstance = new CTileManager;
        }
        return m_pInstance;
    }

    static void         Destroy_Instance()
    {
        if (m_pInstance)
        {
            delete m_pInstance;
            m_pInstance = nullptr;
        }
    }

private:
    static CTileManager* m_pInstance;
    vector<CObject*>     m_vecTile;
    // vector<CObject*>     m_TempvecTile;
    int                  m_iDrawID;
    int                  m_iCurrentTileIndex;
    RECT                 m_rcBackRect;
};

