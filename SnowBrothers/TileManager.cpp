#include "pch.h"
#include "TileManager.h"
#include "AbstractFactory.h"
#include "ScrollManager.h"
#include "BmpManager.h"
#include "ObjectManager.h"
#include "KeyManager.h"

CTileManager* CTileManager::m_pInstance = nullptr;

CTileManager::CTileManager() :
    m_iDrawID(0),
    m_iCurrentTileIndex(m_iDrawID)
{
    m_vecTile.reserve(TILEX * TILEY * 2);
    ZeroMemory(&m_rcBackRect, sizeof(RECT));

  
}

CTileManager::~CTileManager()
{
    Release();
}

void CTileManager::Picking_Tile(POINT _ptMouse, int _iDrawID, int _iOption)
{
    int x = _ptMouse.x / TILECX;
    int y = _ptMouse.y / TILECY;

    int iIndex = y * TILEX + x;

    if ((0 > iIndex) || (m_vecTile.size() <= (size_t)iIndex))
        return;

    dynamic_cast<CTile*>(m_vecTile[iIndex])->Set_DrawID(_iDrawID);
    dynamic_cast<CTile*>(m_vecTile[iIndex])->Set_Option(_iOption);
}

void CTileManager::Save_Tile()
{
    HANDLE	hFile = CreateFile(L"../Data/Tile.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    if (INVALID_HANDLE_VALUE == hFile)
        return;

    int iDrawID(0), iOption(0);
    DWORD dwByte(0);

    for (auto& pTile : m_vecTile)
    {
        iDrawID = dynamic_cast<CTile*>(pTile)->Get_DrawID();
        iOption = dynamic_cast<CTile*>(pTile)->Get_Option();

        tagObjectInfo tTempInfo{};
        tTempInfo = pTile->Get_ObjectInfo();

        WriteFile(hFile, &(tTempInfo), sizeof(tagObjectInfo), &dwByte, NULL);
        WriteFile(hFile, &iDrawID, sizeof(int), &dwByte, NULL);
        WriteFile(hFile, &iOption, sizeof(int), &dwByte, NULL);
    }

    CloseHandle(hFile);
    MessageBox(g_hWnd, L"Tile Save", L"성공", MB_OK);
}

void CTileManager::Load_Tile(int _iStageNum)
{
    if (_iStageNum == 1)
    {
        HANDLE	hFile = CreateFile(L"../Data/Stage1Data/Tile.dat", GENERIC_READ,
            NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

        if (INVALID_HANDLE_VALUE == hFile)
            return;

        tagObjectInfo	tInfo{};
        int iDrawID(0), iOption(0);
        DWORD dwByte(0);

        Release();

        while (true)
        {
            ReadFile(hFile, &tInfo, sizeof(tagObjectInfo), &dwByte, NULL);
            ReadFile(hFile, &iDrawID, sizeof(int), &dwByte, NULL);
            ReadFile(hFile, &iOption, sizeof(int), &dwByte, NULL);

            if (0 == dwByte)
                break;

            CObject* pTile = CAbstractFactory<CTile>::Create(tInfo.fX, tInfo.fY, OBJECT_DIRECTION::DIR_END);

            dynamic_cast<CTile*>(pTile)->Set_DrawID(iDrawID);
            dynamic_cast<CTile*>(pTile)->Set_Option(iOption);

            m_vecTile.push_back(pTile);


        }

        CloseHandle(hFile);
        //MessageBox(g_hWnd, L"Tile Load", L"성공", MB_OK);
    }

    if (_iStageNum == 2)
    {
        HANDLE	hFile = CreateFile(L"../Data/BossOneStageData/Tile.dat", GENERIC_READ,
            NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

        if (INVALID_HANDLE_VALUE == hFile)
            return;

        tagObjectInfo	tInfo{};
        int iDrawID(0), iOption(0);
        DWORD dwByte(0);

        Release();

        while (true)
        {
            ReadFile(hFile, &tInfo, sizeof(tagObjectInfo), &dwByte, NULL);
            ReadFile(hFile, &iDrawID, sizeof(int), &dwByte, NULL);
            ReadFile(hFile, &iOption, sizeof(int), &dwByte, NULL);

            if (0 == dwByte)
                break;

            CObject* pTile = CAbstractFactory<CTile>::Create(tInfo.fX, tInfo.fY, OBJECT_DIRECTION::DIR_END);

            dynamic_cast<CTile*>(pTile)->Set_DrawID(iDrawID);
            dynamic_cast<CTile*>(pTile)->Set_Option(iOption);

            m_vecTile.push_back(pTile);


        }

        CloseHandle(hFile);
        //MessageBox(g_hWnd, L"Tile Load", L"성공", MB_OK);
    }

    if (_iStageNum == 3)
    {
        HANDLE	hFile = CreateFile(L"../Data/BossTwoStageData/bosstwoTile.dat", GENERIC_READ,
            NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

        if (INVALID_HANDLE_VALUE == hFile)
            return;

        tagObjectInfo	tInfo{};
        int iDrawID(0), iOption(0);
        DWORD dwByte(0);

        Release();

        while (true)
        {
            ReadFile(hFile, &tInfo, sizeof(tagObjectInfo), &dwByte, NULL);
            ReadFile(hFile, &iDrawID, sizeof(int), &dwByte, NULL);
            ReadFile(hFile, &iOption, sizeof(int), &dwByte, NULL);

            if (0 == dwByte)
                break;

            CObject* pTile = CAbstractFactory<CTile>::Create(tInfo.fX, tInfo.fY, OBJECT_DIRECTION::DIR_END);

            dynamic_cast<CTile*>(pTile)->Set_DrawID(iDrawID);
            dynamic_cast<CTile*>(pTile)->Set_Option(iOption);

            m_vecTile.push_back(pTile);


        }

        CloseHandle(hFile);
        //MessageBox(g_hWnd, L"Tile Load", L"성공", MB_OK);
    }

    if (_iStageNum == 4)
    {
        HANDLE	hFile = CreateFile(L"../Data/Stage2Data/Stage02Tile.dat", GENERIC_READ,
            NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

        if (INVALID_HANDLE_VALUE == hFile)
            return;

        tagObjectInfo	tInfo{};
        int iDrawID(0), iOption(0);
        DWORD dwByte(0);

        Release();

        while (true)
        {
            ReadFile(hFile, &tInfo, sizeof(tagObjectInfo), &dwByte, NULL);
            ReadFile(hFile, &iDrawID, sizeof(int), &dwByte, NULL);
            ReadFile(hFile, &iOption, sizeof(int), &dwByte, NULL);

            if (0 == dwByte)
                break;

            CObject* pTile = CAbstractFactory<CTile>::Create(tInfo.fX, tInfo.fY, OBJECT_DIRECTION::DIR_END);

            dynamic_cast<CTile*>(pTile)->Set_DrawID(iDrawID);
            dynamic_cast<CTile*>(pTile)->Set_Option(iOption);

            m_vecTile.push_back(pTile);


        }

        CloseHandle(hFile);
        //MessageBox(g_hWnd, L"Tile Load", L"성공", MB_OK);
    }

    if (_iStageNum == 5)
    {
        HANDLE	hFile = CreateFile(L"../Data/EndScene/EndTile.dat", GENERIC_READ,
            NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

        if (INVALID_HANDLE_VALUE == hFile)
            return;

        tagObjectInfo	tInfo{};
        int iDrawID(0), iOption(0);
        DWORD dwByte(0);

        Release();

        while (true)
        {
            ReadFile(hFile, &tInfo, sizeof(tagObjectInfo), &dwByte, NULL);
            ReadFile(hFile, &iDrawID, sizeof(int), &dwByte, NULL);
            ReadFile(hFile, &iOption, sizeof(int), &dwByte, NULL);

            if (0 == dwByte)
                break;

            CObject* pTile = CAbstractFactory<CTile>::Create(tInfo.fX, tInfo.fY, OBJECT_DIRECTION::DIR_END);

            dynamic_cast<CTile*>(pTile)->Set_DrawID(iDrawID);
            dynamic_cast<CTile*>(pTile)->Set_Option(iOption);

            m_vecTile.push_back(pTile);


        }

        CloseHandle(hFile);
        //MessageBox(g_hWnd, L"Tile Load", L"성공", MB_OK);
    }
}

void CTileManager::Tile_Follow_MouseCursor(HDC _hDC, int _iScrollX, int _iScrollY)
{
    POINT mousePoint{};
    GetCursorPos(&mousePoint);
    ScreenToClient(g_hWnd, &mousePoint);

    int iImageSizeX = 32;
    int iImageSizeY = 32;

    HDC hMemDC = CBmpManager::Get_Instance()->Find_Img(L"Tile");

    GdiTransparentBlt
    (
        _hDC,
        int(mousePoint.x),
        int(mousePoint.y),
        int(iImageSizeX),
        int(iImageSizeY),
        //int(m_vecTile[m_iDrawID]->Get_ObjectInfo().fX * 2),
        //int(m_vecTile[m_iDrawID]->Get_ObjectInfo().fY * 2),
        hMemDC,
        0,
        0,
        int(iImageSizeX),
        int(iImageSizeY),
        RGB(255, 0, 255)
    );
}

void CTileManager::Show_TileList(HDC _hDC, int _iDrawID)
{
    POINT mousePoint{};
    GetCursorPos(&mousePoint);
    ScreenToClient(g_hWnd, &mousePoint);

    HDC hMemDC = CBmpManager::Get_Instance()->Find_Img(L"Tile");

    GdiTransparentBlt
    (
        _hDC,
        int(0),
        int(0),
        int(192),
        int(32),
        hMemDC,
        0,
        0,
        int(32 * _iDrawID),
        int(32),
        RGB(255, 0, 255)
    );

    //if(mousePoint.x == (32*m_iDrawID))
}

void CTileManager::Initialize()
{
    for (int i = 0; i < TILEY; ++i)
    {
        for (int k = 0; k < TILEX; ++k)
        {
            float fX = (TILECX >> 1) + float(TILECX * k);
            float fY = (TILECY >> 1) + float(TILECY * i);

            
            CObject* pObject = CAbstractFactory<CTile>::Create((float)fX, (float)fY, OBJECT_DIRECTION::DIR_END);

            CObjectManager::Get_Instance()->Add_Object(OBJECT_LIST::TILE, pObject);
            
            m_vecTile.emplace_back(pObject);
        }
    }
}

int CTileManager::Update()
{
    for (auto& pTile : m_vecTile)
    {
        pTile->Update();
    }

    //Tile_Change();

    return (UINT)OBJECT_STATE::OBJ_DEAD;
}

void CTileManager::Late_Update()
{
    for (auto& pTile : m_vecTile)
    {
        pTile->Late_Update();
    }
}

void CTileManager::Render(HDC _hDC)
{
    int	iCullX = abs((int)CScrollManager::Get_Instance()->Get_ScrollX() / TILECX);
    int	iCullY = abs((int)CScrollManager::Get_Instance()->Get_ScrollY() / TILECY);

    int	iMaxX = iCullX + WINCX / TILECX + 2;
    int	iMaxY = iCullY + WINCY / TILECY + 2;

    for (auto& pTile : m_vecTile)
    {
        m_iDrawID = dynamic_cast<CTile*>(pTile)->Get_DrawID();
    }

    for (int i = iCullY; i < iMaxY; ++i)
    {
        for (int j = iCullX; j < iMaxX; ++j)
        {
            int		iIndex = i * TILEX + j;

            if (0 > iIndex || (size_t)iIndex >= m_vecTile.size())
                continue;

            m_vecTile[iIndex]->Render(_hDC);
        }
    }
    //Tile_Follow_MouseCursor(_hDC, iCullX, iCullY);



    //Show_TileList(_hDC, m_iDrawID);

    //for (int i = 0; i < 6; ++i)
    //{
    //    Rectangle(_hDC,
    //        m_rcBackRect.left +(32 * i),
    //        0, 
    //        m_rcBackRect.right + (32 + (i * 32)),
    //        32);
    //}
}

void CTileManager::Release()
{
    // 타일 있는데, 지웠어, 지우는건 좋은데, 차피 지우는 건 objectManager에서 지워버린단 말이지? 
    // 근데 for_each 여따가 살려두면, objectManager에서 지운 걸 tileManager에서 또 지워버린단 말야? 
    // 이미 지웟는데 또 지우래. -> 터짐 1
    // 그럼 어카냐, ojbectManager에서 타일들을 safe_delete해서 nullptr 시키고, clear도 했는데, tile manager에서는 
    // objectManager가 그랫다는 걸 몰라, 그래가지고 여기서도 for_Each 또 하면 되지 않냐 -> 터짐 1 반복
    // 차피 tile은 objectManager에서 nullptr해놧고 clear도 했으니, 우리는 그냥 여기서 clear만 해서, 
    // tile매니져가 아직 tile이 있다라고 아는 걸 clear해서 지워준다. 
    // clear만 하니까 두번 delete할 일도 없고 해서 안터지고, 
    // Edit클래스에서 나갓다 들어왓다 해도, 타일이 없어졋다가 들어갈때만 다시 깔리고 하니까 렉도 안걸림
    // 
    for_each(m_vecTile.begin(), m_vecTile.end(), Safe_Delete<CObject*>);
    m_vecTile.clear();
}
