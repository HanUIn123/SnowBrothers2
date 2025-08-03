#include "pch.h"
#include "CollisionManager.h"
#include "ObjectManager.h"
#include "Tile.h"
#include "Monster.h"
#include "Player.h"
#include "SpawnManager.h"
#include "ScrollManager.h"
#include "BossTwo.h"
#include "BossOne.h"

CCollisionManager::CCollisionManager()
{

}

CCollisionManager::~CCollisionManager()
{
}

void CCollisionManager::Collision_Rect(list<CObject*> _pObject1, list<CObject*> _pObject2)
{
    RECT    rc{};

    for (auto& pObject1 : _pObject1)
    {
        for (auto& pObject2 : _pObject2)
        {
            if (IntersectRect(&rc, (pObject1->Get_Rect()), (pObject2->Get_Rect())))
            {
                //pObject1->Set_Dead(true);
                //pObject2->Set_Dead(true);

                pObject1->Setting_PosY(pObject2->Get_Rect()->top - pObject2->Get_ObjectInfo().fCY * 0.5f);
            }


        }
    }
}

// ==============================================================================

void CCollisionManager::Collision_Tile_Player(list<CObject*> _pPlayer, vector<CObject*> _vecTile)
{
    float fWidth(0.0f), fHeight(0.0f);

    for (auto& pObject1 : _pPlayer)
    {
        for (auto& pObject2 : _vecTile)
        {
            if (dynamic_cast<CTile*>(pObject2)->Get_DrawID() != 6)
            {
                if (dynamic_cast<CPlayer*>(pObject1)->Get_DownJump() == false)
                {
                    if (Check_Rect(pObject1, pObject2, &fWidth, &fHeight))
                    {
                        // 상하 충돌
                        if (fWidth > fHeight)
                        {
                            if (pObject1->Get_ObjectInfo().fY < pObject2->Get_ObjectInfo().fY)
                            {
                                //Dst->Set_PosY(fHeight);

                                if (pObject1->Get_ObjectInfo().fY + pObject1->Get_ObjectInfo().fCY * 0.5f >
                                    pObject2->Get_ObjectInfo().fY - pObject2->Get_ObjectInfo().fCY * 0.5f)
                                {
                                    if (dynamic_cast<CPlayer*>(pObject1)->Get_PlayerFalling())
                                    {
                                        dynamic_cast<CPlayer*>(pObject1)->Set_PlayerJumpPower(16.5f);
                                        dynamic_cast<CPlayer*>(pObject1)->Set_PlayerJumpFalse();
                                        dynamic_cast<CPlayer*>(pObject1)->Set_PlayerFallingFalse();
                                    }
                                    else
                                    {
                                        if (!dynamic_cast<CPlayer*>(pObject1)->Get_PlayerJump())
                                        {
                                            pObject1->Set_PosY(-fHeight);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void CCollisionManager::Collision_Snow_Player(list<CObject*> _pPlayer, list<CObject*> _pSnow)
{
    float fWidth(0.0f), fHeight(0.0f);

    for (auto& pObject1 : _pPlayer)
    {
        for (auto& pObject2 : _pSnow)
        {
            if (dynamic_cast<CMonster*>(pObject2)->Get_CollisionName() == L"ENEMYONESNOW" && !dynamic_cast<CPlayer*>(pObject1)->Get_CanRolling())
            {
                if (dynamic_cast<CPlayer*>(pObject1)->Get_DownJump() == false)
                {
                    if (Check_Rect(pObject1, pObject2, &fWidth, &fHeight))
                    {
                        // 상하 충돌
                        if (fWidth > fHeight)
                        {
                            if (pObject1->Get_ObjectInfo().fY < pObject2->Get_ObjectInfo().fY)
                            {
                                if (pObject1->Get_ObjectInfo().fY + pObject1->Get_ObjectInfo().fCY * 0.5f >
                                    pObject2->Get_ObjectInfo().fY - pObject2->Get_ObjectInfo().fCY * 0.5f)
                                {
                                    if (dynamic_cast<CPlayer*>(pObject1)->Get_PlayerFalling())
                                    {
                                        dynamic_cast<CPlayer*>(pObject1)->Set_PlayerJumpPower(16.5f);
                                        dynamic_cast<CPlayer*>(pObject1)->Set_PlayerJumpFalse();
                                        dynamic_cast<CPlayer*>(pObject1)->Set_PlayerFallingFalse();
                                    }
                                    else
                                    {
                                        if (!dynamic_cast<CPlayer*>(pObject1)->Get_PlayerJump())
                                        {
                                            //dynamic_cast<CPlayer*>(pObject1)->Set_IsOnSnow(true);

                                            pObject1->Set_PosY(-fHeight - 2.0f);
                                            dynamic_cast<CPlayer*>(pObject1)->Set_CanPush(false);
                                        }
                                    }
                                }
                            }
                            else
                            {
                                //dynamic_cast<CPlayer*>(pObject1)->Set_IsOnSnow(false);
                                pObject2->Set_PosY(-fHeight - 2.0f);
                            }
                        }

                    }
                }
            }
        }
    }

}

void CCollisionManager::Collision_Snow_Player_Minion(list<CObject*> _pPlayer, list<CObject*> _pSnow)
{
    float fWidth(0.0f), fHeight(0.0f);

    for (auto& pObject1 : _pPlayer)
    {
        for (auto& pObject2 : _pSnow)
        {
            if (dynamic_cast<CMonster*>(pObject2)->Get_CollisionName() == L"MINIONSNOW" && !dynamic_cast<CPlayer*>(pObject1)->Get_CanRolling())
            {
                if (dynamic_cast<CPlayer*>(pObject1)->Get_DownJump() == false)
                {
                    if (Check_Rect(pObject1, pObject2, &fWidth, &fHeight))
                    {
                        // 상하 충돌
                        if (fWidth > fHeight)
                        {
                            if (pObject1->Get_ObjectInfo().fY < pObject2->Get_ObjectInfo().fY)
                            {
                                if (pObject1->Get_ObjectInfo().fY + pObject1->Get_ObjectInfo().fCY * 0.5f >
                                    pObject2->Get_ObjectInfo().fY - pObject2->Get_ObjectInfo().fCY * 0.5f)
                                {
                                    if (dynamic_cast<CPlayer*>(pObject1)->Get_PlayerFalling())
                                    {
                                        dynamic_cast<CPlayer*>(pObject1)->Set_PlayerJumpPower(16.5f);
                                        dynamic_cast<CPlayer*>(pObject1)->Set_PlayerJumpFalse();
                                        dynamic_cast<CPlayer*>(pObject1)->Set_PlayerFallingFalse();
                                    }
                                    else
                                    {
                                        if (!dynamic_cast<CPlayer*>(pObject1)->Get_PlayerJump())
                                        {
                                            //dynamic_cast<CPlayer*>(pObject1)->Set_IsOnSnow(true);

                                            pObject1->Set_PosY(-fHeight - 2.0f);
                                            dynamic_cast<CPlayer*>(pObject1)->Set_CanPush(false);
                                        }
                                    }
                                }
                            }
                            else
                            {
                                //dynamic_cast<CPlayer*>(pObject1)->Set_IsOnSnow(false);
                                pObject2->Set_PosY(-fHeight - 2.0f);
                            }
                        }

                    }
                }
            }
        }
    }
}

// ==============================================================================

void CCollisionManager::Collision_Tile_Monster(list<CObject*> _pMonster, vector<CObject*> _vecTile)
{
    float fWidth(0.0f), fHeight(0.0f);

    for (auto& pObject1 : _pMonster)
    {
        for (auto& pObject2 : _vecTile)
        {
            if (dynamic_cast<CTile*>(pObject2)->Get_DrawID() != 6)
            {
                if (dynamic_cast<CMonster*>(pObject1)->Get_ReadyToDie() == false)
                {
                    if (Check_Rect(pObject1, pObject2, &fWidth, &fHeight))
                    {
                        // 상하 충돌
                        if (fWidth > fHeight)
                        {
                            if (pObject1->Get_ObjectInfo().fY < pObject2->Get_ObjectInfo().fY)
                            {
                                //Dst->Set_PosY(fHeight);

                                if (pObject1->Get_ObjectInfo().fY + pObject1->Get_ObjectInfo().fCY * 0.5f >
                                    pObject2->Get_ObjectInfo().fY - pObject2->Get_ObjectInfo().fCY * 0.5f)
                                {
                                    if (dynamic_cast<CMonster*>(pObject1)->Get_Falling())
                                    {
                                        dynamic_cast<CMonster*>(pObject1)->Set_GrvityValue(16.0f);
                                        dynamic_cast<CMonster*>(pObject1)->Set_JumpFalse();
                                        dynamic_cast<CMonster*>(pObject1)->Set_FallingFalse();
                                    }
                                    else
                                    {
                                        if (!dynamic_cast<CMonster*>(pObject1)->Get_Jump())
                                            pObject1->Set_PosY(-fHeight);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

// ==============================================================================

void CCollisionManager::Collision_Tile_Minion(list<CObject*> _pMonster, vector<CObject*> _vecTile)
{
    float fWidth(0.0f), fHeight(0.0f);

    for (auto& pObject1 : _pMonster)
    {
        for (auto& pObject2 : _vecTile)
        {
            if (dynamic_cast<CTile*>(pObject2)->Get_DrawID() != 6)
            {
                if (Check_Rect(pObject1, pObject2, &fWidth, &fHeight))
                {
                    // 상하 충돌
                    if (fWidth > fHeight)
                    {
                        if (pObject1->Get_ObjectInfo().fY < pObject2->Get_ObjectInfo().fY)
                        {
                            //Dst->Set_PosY(fHeight);

                            if (pObject1->Get_ObjectInfo().fY + pObject1->Get_ObjectInfo().fCY * 0.5f >
                                pObject2->Get_ObjectInfo().fY - pObject2->Get_ObjectInfo().fCY * 0.5f)
                            {
                                if (dynamic_cast<CMonster*>(pObject1)->Get_Falling())
                                {
                                    dynamic_cast<CMonster*>(pObject1)->Set_GrvityValue(16.0f);
                                    dynamic_cast<CMonster*>(pObject1)->Set_JumpFalse();
                                    dynamic_cast<CMonster*>(pObject1)->Set_FallingFalse();
                                }
                                else
                                {
                                    if (!dynamic_cast<CMonster*>(pObject1)->Get_Jump())
                                    {
                                        pObject1->Set_PosY(-fHeight);
                                        dynamic_cast<CMonster*>(pObject1)->Set_Landing(true);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void CCollisionManager::Collision_Tile_Boss(list<CObject*> _pBossOne, vector<CObject*> _vecTile)
{
    float fWidth(0.0f), fHeight(0.0f);

    for (auto& pObject1 : _pBossOne)
    {
        for (auto& pObject2 : _vecTile)
        {
            if (dynamic_cast<CTile*>(pObject2)->Get_DrawID() != 6 && dynamic_cast<CTile*>(pObject2)->Get_DrawID() != 3)
            {
                if (Check_Rect(pObject1, pObject2, &fWidth, &fHeight))
                {
                    if (dynamic_cast<CMonster*>(pObject1)->Get_Falling())
                    {
                        dynamic_cast<CMonster*>(pObject1)->Set_GrvityValue(13.0f);
                        dynamic_cast<CMonster*>(pObject1)->Set_JumpFalse();
                        dynamic_cast<CMonster*>(pObject1)->Set_FallingFalse();
                    }
                    else
                    {
                        if (!dynamic_cast<CMonster*>(pObject1)->Get_Jump())
                        {
                            pObject1->Set_PosY(-fHeight);
                        }
                    }
                }
            }

        }
    }
}


void CCollisionManager::Collision_Tile_BossTwo(list<CObject*> _pBossTwo, vector<CObject*> _vecTile)
{
    float fWidth(0.0f), fHeight(0.0f);

    for (auto& pObject1 : _pBossTwo)
    {
        for (auto& pObject2 : _vecTile)
        {
            if (dynamic_cast<CTile*>(pObject2)->Get_DrawID() != 6 && dynamic_cast<CTile*>(pObject2)->Get_DrawID() != 3)
            {
                if (Check_Rect(pObject1, pObject2, &fWidth, &fHeight))
                {
                    pObject1->Set_PosY(-fHeight);
                }
            }

        }
    }
}

void CCollisionManager::Collision_Snow(list<CObject*> _pObject1, list<CObject*> _pObject2)
{
    float fWidth(0.0f), fHeight(0.0f);
    for (auto& pObject1 : _pObject1)
    {
        for (auto& pObject2 : _pObject2)
        {
            if (dynamic_cast<CMonster*>(pObject2)->Get_SnowStat() >= 6)
            {
                if (Check_Rect(pObject1, pObject2, &fWidth, &fHeight))
                {
                    // 좌우 충돌
                    if (fWidth < fHeight)
                    {
                        //좌 충돌
                        if (pObject1->Get_ObjectInfo().fX < pObject2->Get_ObjectInfo().fX)
                        {
                            pObject2->Set_PosX(fWidth);
                        }

                        else
                        {
                            pObject2->Set_PosX(-fWidth);
                        }
                    }
                }
                else
                {
                }
            }
            if ((pObject1->Get_ObjectInfo().fY + pObject1->Get_ObjectInfo().fCY * 0.5f >= pObject2->Get_ObjectInfo().fY - pObject2->Get_ObjectInfo().fCY * 0.5f) &&
                (pObject1->Get_ObjectInfo().fX >= pObject2->Get_ObjectInfo().fX - pObject2->Get_ObjectInfo().fCX * 0.5f &&
                    pObject1->Get_ObjectInfo().fX <= pObject2->Get_ObjectInfo().fX + pObject2->Get_ObjectInfo().fCX * 0.5f)
                )
            {
            }
        }
    }
}

void CCollisionManager::Collision_BetweenSnow(list<CObject*> _pObject1, list<CObject*> _pObject2)
{
    float fWidth(0.0f), fHeight(0.0f);
    for (auto& pObject1 : _pObject1)
    {
        for (auto& pObject2 : _pObject2)
        {
            if (dynamic_cast<CMonster*>(pObject2)->Get_SnowStat() >= 6 || dynamic_cast<CMonster*>(pObject1)->Get_SnowStat() >= 6)
            {
                if (Check_Rect(pObject1, pObject2, &fWidth, &fHeight))
                {
                    // 좌우 충돌
                    if (fWidth < fHeight)
                    {
                        //좌 충돌
                        if (pObject1->Get_ObjectInfo().fX < pObject2->Get_ObjectInfo().fX)
                        {
                            pObject2->Set_PosX(fWidth);
                        }

                        else
                        {
                            pObject2->Set_PosX(-fWidth);
                        }
                    }
                }

            }


        }
    }
}

void CCollisionManager::Collision_Between_Snow(list<CObject*> _pObject1, list<CObject*> _pObject2)
{
    float fWidth(0.0f), fHeight(0.0f);
    for (auto& pObject1 : _pObject1)
    {
        for (auto& pObject2 : _pObject2)
        {
            if (Check_Rect(pObject1, pObject2, &fWidth, &fHeight))
            {
                if (fWidth < fHeight)
                {
                    if (pObject1->Get_ObjectInfo().fX < pObject2->Get_ObjectInfo().fX)
                    {
                    }

                    else
                    {
                    }
                }
            }
        }
    }
}

void CCollisionManager::Collision_Between_Monsters(list<CObject*> _pMonster1, list<CObject*> _pMonster2)
{
    float fWidth(0.0f), fHeight(0.0f);

    for (auto& pObject1 : _pMonster1)
    {
        for (auto& pObject2 : _pMonster2)
        {
            if (pObject1 == pObject2)
                continue;

            if (dynamic_cast<CMonster*>(pObject1)->Get_SnowBallMove() || dynamic_cast<CMonster*>(pObject2)->Get_SnowBallMove())
            {
                if (pObject1->Get_CollisionName() == L"ENEMYONESNOW" && pObject2->Get_CollisionName() == L"ENEMYONE")
                {
                    if (Check_Circle(pObject1, pObject2))
                    {
                        dynamic_cast<CMonster*>(pObject2)->Set_ReadyToDie(true);
                    }
                }
                if (pObject1->Get_CollisionName() == L"ENEMYONESNOW" && pObject2->Get_CollisionName() == L"ENEMYONESNOW")
                {
                    if (Check_Rect(pObject1, pObject2, &fWidth, &fHeight))
                    {
                        // 상하 충돌
                        if (fWidth > fHeight)
                        {
                            pObject1->Set_PosX(fWidth);
                            pObject2->Set_PosX(-fWidth);
                        }


                        // 좌우 충돌
                        if (fWidth < fHeight)
                        {
                            //좌 충돌
                            if (pObject1->Get_ObjectInfo().fX < pObject2->Get_ObjectInfo().fX)
                            {
                                //Dst->Set_PosX(-fWidth);
                                pObject1->Set_PosX(fWidth);
                                pObject2->Set_PosX(-fWidth);
                            }
                            else
                            {
                                //Dst->Set_PosX(fWidth);
                                pObject1->Set_PosX(-fWidth);
                                pObject2->Set_PosX(fWidth);
                            }
                        }
                    }
                }
            }
        }
    }
}

void CCollisionManager::Collision_Between_Minions(list<CObject*> _pMonster1, list<CObject*> _pMonster2)
{
    float fWidth(0.0f), fHeight(0.0f);

    for (auto& pObject1 : _pMonster1)
    {
        for (auto& pObject2 : _pMonster2)
        {
            if (pObject1 == pObject2)
                continue;

            if (dynamic_cast<CMonster*>(pObject1)->Get_SnowBallMove() || dynamic_cast<CMonster*>(pObject2)->Get_SnowBallMove())
            {
                if ((pObject1->Get_CollisionName() == L"MINIONSNOW" && pObject2->Get_CollisionName() == L"MINION"))
                {
                    if (Check_Circle(pObject1, pObject2))
                    {
                        dynamic_cast<CMonster*>(pObject2)->Set_ReadyToDie(true);
                    }
                }
                if ((pObject1->Get_CollisionName() == L"MINION" && pObject2->Get_CollisionName() == L"MINIONSNOW"))
                {
                    if (Check_Circle(pObject1, pObject2))
                    {
                        dynamic_cast<CMonster*>(pObject1)->Set_ReadyToDie(true);
                    }
                }
                if (pObject1->Get_CollisionName() == L"MINIONSNOW" && pObject2->Get_CollisionName() == L"MINIONSNOW")
                {
                    if (Check_Rect(pObject1, pObject2, &fWidth, &fHeight))
                    {
                        // 상하 충돌
                        if (fWidth > fHeight)
                        {
                            pObject1->Set_PosX(fWidth);
                            pObject2->Set_PosX(-fWidth);
                        }

                        // 좌우 충돌
                        if (fWidth < fHeight)
                        {
                            //좌 충돌
                            if (pObject1->Get_ObjectInfo().fX < pObject2->Get_ObjectInfo().fX)
                            {
                                pObject1->Set_PosX(fWidth);
                                pObject2->Set_PosX(-fWidth);
                            }
                            else
                            {
                                pObject1->Set_PosX(-fWidth);
                                pObject2->Set_PosX(fWidth);
                            }
                        }
                    }
                }
            }

        }
    }
}

void CCollisionManager::Collision_BossOne_Minions(list<CObject*> _pBoss, list<CObject*> _pMinions)
{
    float fWidth(0.0f), fHeight(0.0f);

    for (auto& pObject1 : _pBoss)
    {
        for (auto& pObject2 : _pMinions)
        {
            if (dynamic_cast<CMonster*>(pObject2)->Get_SnowBallMove())
            {
                if ((pObject2->Get_CollisionName() == L"MINIONSNOW" && pObject1->Get_CollisionName() == L"BOSSONE"))
                {
                    if (Check_BossOne(pObject1, pObject2))
                    {
                        pObject2->Set_Dead(true);

                        dynamic_cast<CBossOne*>(pObject1)->Set_CurrentBossOneHp(20.0f);
                    }
                }
            }
        }
    }
}

void CCollisionManager::Collision_BossTwo_Minions(list<CObject*> _pBoss, list<CObject*> _pMinions)
{
    float fWidth(0.0f), fHeight(0.0f);

    for (auto& pObject1 : _pBoss)
    {
        for (auto& pObject2 : _pMinions)
        {
            if (dynamic_cast<CMonster*>(pObject2)->Get_SnowBallMove())
            {
                if ((pObject2->Get_CollisionName() == L"MINIONSNOW" && pObject1->Get_CollisionName() == L"BOSSTWO"))
                {
                    if (Check_Circle(pObject1, pObject2))
                    {
                        pObject2->Set_Dead(true);

                        dynamic_cast<CBossTwo*>(pObject1)->Set_CurrentBossTwoHp(15.0f);
                    }
                }
            }
        }
    }
}



void CCollisionManager::Collision_SnowKick(list<CObject*> _pObject1, list<CObject*> _pObject2)
{
    float fWidth(0.0f), fHeight(0.0f);

    for (auto& pObject1 : _pObject1)
    {
        for (auto& pObject2 : _pObject2)
        {
            if (Check_Rect(pObject1, pObject2, &fWidth, &fHeight))
            {
                if (pObject1->Get_ObjectInfo().fX > pObject2->Get_ObjectInfo().fX)
                {
                    pObject2->Set_PosX(-fWidth);
                }
                else
                {
                    pObject2->Set_PosX(fWidth * 10);
                }
            }
        }
    }
}

void CCollisionManager::Collision_RectEx(list<CObject*> _pObject1, list<CObject*> _pObject2, bool _bCanPush)
{
    float fWidth(0.0f), fHeight(0.0f);

    for (auto& pObject1 : _pObject1)
    {
        for (auto& pObject2 : _pObject2)
        {
            if (Check_Rect(pObject1, pObject2, &fWidth, &fHeight))
            {
                if (fWidth > fHeight)
                {
                    if (pObject1->Get_ObjectInfo().fY < pObject2->Get_ObjectInfo().fY)
                    {
                        pObject1->Set_PosY(-fHeight);
                    }
                    else
                    {
                        pObject1->Set_PosY(fHeight);
                    }
                }
                else
                {
                    if (pObject1->Get_ObjectInfo().fX > pObject2->Get_ObjectInfo().fX)
                    {
                        pObject1->Set_PosX(-fWidth);
                    }
                    else
                    {
                        pObject1->Set_PosX(fWidth);
                    }
                }
            }
        }
    }
}

void CCollisionManager::Collision_Circle(list<CObject*> _pObject1, list<CObject*> _pObject2)
{
    for (auto& pObject1 : _pObject1)
    {
        for (auto& pObject2 : _pObject2)
        {
            if (Check_Circle(pObject1, pObject2))
            {
                pObject2->Set_Dead(true);
            }
        }
    }
}


void CCollisionManager::Collision_With_Items(list<CObject*> _pPlayer, list<CObject*> _pItems)
{
    for (auto& pObject1 : _pPlayer)
    {
        for (auto& pObject2 : _pItems)
        {
            if (Check_Circle(pObject1, pObject2))
            {
                pObject2->Set_Dead(true);
            }
        }
    }
}

bool CCollisionManager::Check_Rect(CObject* _pObject1, CObject* _pObject2, float* _pWidth, float* _pHeight)
{
    float	fWidth = fabs(_pObject1->Get_ObjectInfo().fX - _pObject2->Get_ObjectInfo().fX);
    float	fHeight = fabs(_pObject1->Get_ObjectInfo().fY - _pObject2->Get_ObjectInfo().fY);

    float	fRadiusX = (_pObject1->Get_ObjectInfo().fCX + _pObject2->Get_ObjectInfo().fCX) * 0.5f;
    float	fRadiusY = (_pObject1->Get_ObjectInfo().fCY + _pObject2->Get_ObjectInfo().fCY) * 0.5f;

    if ((fRadiusX >= fWidth) && (fRadiusY >= fHeight))
    {
        *_pWidth = fRadiusX - fWidth;
        *_pHeight = fRadiusY - fHeight;

        return true;
    }

    return false;
}

bool CCollisionManager::Check_BossOne(CObject* _pObject1, CObject* _pObject2, float* _pWidth, float* _pHeight)
{
    float	fWidth = fabs(_pObject1->Get_ObjectInfo().fX - _pObject2->Get_ObjectInfo().fX);
    float	fHeight = fabs(_pObject1->Get_ObjectInfo().fY - _pObject2->Get_ObjectInfo().fY);

    float	fRadiusX = (_pObject1->Get_ObjectInfo().fCX + _pObject2->Get_ObjectInfo().fCX) * 0.5f;
    float	fRadiusY = (_pObject1->Get_ObjectInfo().fCY + _pObject2->Get_ObjectInfo().fCY) * 0.5f;

    if ((fRadiusX - fWidth >= 60 ) && (fRadiusY - fHeight >= 60 ))
    {
        *_pWidth = fRadiusX - fWidth;
        *_pHeight = fRadiusY - fHeight;

        return true;
    }
    return false;
}

bool CCollisionManager::Check_RectHeight(CObject* _pObject1, CObject* _pObject2, float* _pWidth, float* _pHeight)
{
    float	fWidth = fabs(_pObject1->Get_ObjectInfo().fX - _pObject2->Get_ObjectInfo().fX);
    float	fHeight = fabs(_pObject1->Get_ObjectInfo().fY - _pObject2->Get_ObjectInfo().fY);

    float	fRadiusX = (_pObject1->Get_ObjectInfo().fCX + _pObject2->Get_ObjectInfo().fCX) * 0.5f;
    float	fRadiusY = (_pObject1->Get_ObjectInfo().fCY + _pObject2->Get_ObjectInfo().fCY) * 0.5f;

    if ((fRadiusX >= fWidth) && (fRadiusY >= fHeight))
    {
        *_pWidth = fRadiusX - fWidth;
        *_pHeight = fRadiusY - fHeight;

        return true;
    }

    return false;
}

bool CCollisionManager::Check_Circle(CObject* _pObject1, CObject* _pObject2)
{
    float fWidth = abs(_pObject1->Get_ObjectInfo().fX - _pObject2->Get_ObjectInfo().fX);
    float fHeight = abs(_pObject1->Get_ObjectInfo().fY - _pObject2->Get_ObjectInfo().fY);

    float fDiagonal = sqrt(fWidth * fWidth + fHeight * fHeight);

    float fRadius = (_pObject1->Get_ObjectInfo().fCX + _pObject2->Get_ObjectInfo().fCX) * 0.5f;

    if (fRadius >= fDiagonal)
        return true;

    return false;
}

bool CCollisionManager::Check_BossOne(CObject* _pObject1, CObject* _pObject2)
{
    float fWidth = abs(_pObject1->Get_ObjectInfo().fX- _pObject2->Get_ObjectInfo().fX);
    float fHeight = abs(_pObject1->Get_ObjectInfo().fY - _pObject2->Get_ObjectInfo().fY);

    float fDiagonal = sqrt(fWidth * fWidth + fHeight * fHeight);

    float fRadius = ((_pObject1->Get_ObjectInfo().fCX + _pObject2->Get_ObjectInfo().fCX) * 0.5f) - 50.0f;

    if (fRadius >= fDiagonal)
        return true;

    return false;
}

bool CCollisionManager::Check_BossTwo(CObject* _pObject1, CObject* _pObject2)
{
    float fWidth = abs(_pObject1->Get_ObjectInfo().fX - _pObject2->Get_ObjectInfo().fX);
    float fHeight = abs(_pObject1->Get_ObjectInfo().fY - _pObject2->Get_ObjectInfo().fY);

    float fDiagonal = sqrt(fWidth * fWidth + fHeight * fHeight);

    float fRadius = ((_pObject1->Get_ObjectInfo().fCX + _pObject2->Get_ObjectInfo().fCX) * 0.5f) - 20.0f;

    if (fRadius - fDiagonal >= 50)
        return true;

    return false;
}

bool CCollisionManager::Object_Collide(list<CObject*> _Object1, list<CObject*> _Object2, CObject*& _ObjectType1, CObject*& _ObjectType2)
{
    for (auto& Object1 : _Object1)
    {
        for (auto& Object2 : _Object2)
        {
            if (Check_ObjectCollide(Object1, Object2))
            {
                if (Object1 == Object2)
                    continue;

                _ObjectType1 = Object1;
                _ObjectType2 = Object2;
                return true;
            }
        }
    }
    return false;
}

bool CCollisionManager::Player_Bullet_BossOne(list<CObject*> _Object1, list<CObject*> _Object2, CObject*& _ObjectType1, CObject*& _ObjectType2)
{
    for (auto& Object1 : _Object1)
    {
        for (auto& Object2 : _Object2)
        {
            if (Check_BossOne(Object1, Object2))
            {
                if (Object1 == Object2)
                    continue;

                _ObjectType1 = Object1;
                _ObjectType2 = Object2;
                return true;
            }
        }
    }
    return false;
}

bool CCollisionManager::Player_Bullet_BossTwo(list<CObject*> _Object1, list<CObject*> _Object2, CObject*& _ObjectType1, CObject*& _ObjectType2)
{
    for (auto& Object1 : _Object1)
    {
        for (auto& Object2 : _Object2)
        {
            if (Check_BossTwo(Object1, Object2))
            {
                if (Object1 == Object2)
                    continue;

                _ObjectType1 = Object1;
                _ObjectType2 = Object2;
                return true;
            }
        }
    }

    return false;
}

bool CCollisionManager::Check_ObjectCollide(CObject* _pObject1, CObject* _pObject2)
{
    float fWidth = fabs(_pObject1->Get_ObjectInfo().fX - _pObject2->Get_ObjectInfo().fX);
    float fHeight = fabs(_pObject1->Get_ObjectInfo().fY - _pObject2->Get_ObjectInfo().fY);

    float fRadiusX = (_pObject1->Get_ObjectInfo().fCX + _pObject2->Get_ObjectInfo().fCX) * 0.5f;
    float fRadiusY = (_pObject1->Get_ObjectInfo().fCY + _pObject2->Get_ObjectInfo().fCY) * 0.5f;

    if ((fRadiusX >= fWidth) && (fRadiusY >= fHeight))
        return true;

    return false;
}



