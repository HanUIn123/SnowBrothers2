#pragma once
#include "Object.h"

class CCollisionManager
{
public:
    CCollisionManager();
    ~CCollisionManager();

public:
    static void Collision_Rect(list<CObject*> _pObject1, list<CObject*> _pObject2);

    static void Collision_Tile_Player(list<CObject*> _pPlayer, vector<CObject*> _vecTile);

    static void Collision_Snow_Player(list<CObject*> _pPlayer, list<CObject*> _pSnow);

    static void Collision_Snow_Player_Minion(list<CObject*> _pPlayer, list<CObject*> _pSnow);

    static void Collision_Tile_Monster(list<CObject*> _pMonster, vector<CObject*> _vecTile);
    
    static void Collision_Tile_Minion(list<CObject*> _pMonster, vector<CObject*> _vecTile);


    static void Collision_Tile_Boss(list<CObject*> _pBossOne, vector<CObject*> _vecTile);

    static void Collision_Tile_BossTwo(list<CObject*> _pBossTwo, vector<CObject*> _vecTile);

    static void Collision_RectEx(list<CObject*> _pObject1, list<CObject*> _pObject2, bool _bCanPush);


    static void Collision_Snow(list<CObject*> _pObject1, list<CObject*> _pObject2);

    static void Collision_BetweenSnow(list<CObject*> _pObject1, list<CObject*> _pObject2);

    static void Collision_Between_Snow(list<CObject*> _pObject1, list<CObject*> _pObject2);

    static void Collision_Between_Monsters(list<CObject*> _pMonster1, list<CObject*> _pMonster2);

    static void Collision_Between_Minions(list<CObject*> _pMonster1, list<CObject*> _pMonster2);

    static void Collision_BossOne_Minions(list<CObject*> _pBoss, list<CObject*> _pMinions);

    static void Collision_BossTwo_Minions(list<CObject*> _pBoss, list<CObject*> _pMinions);

    //static void Collision_Between_Snow2(list<CObject*> _pObject1, vector<CObject*> _vecSnow);

    static void Collision_SnowKick(list<CObject*> _pObject1, list<CObject*> _pObject2);

    static void Collision_Circle(list<CObject*> _pObject1, list<CObject*> _pObject2);


    static void Collision_With_Items(list<CObject*> _pPlayer, list<CObject*> _pItems);



    static bool Check_Rect(CObject* _pObject1, CObject* _pObject2, float* _pWidth, float* _pHeight);

    static bool Check_BossOne(CObject* _pObject1, CObject* _pObject2, float* _pWidth, float* _pHeight);

    static bool Check_RectHeight(CObject* _pObject1, CObject* _pObject2, float* _pWidth, float* _pHeight);


    static bool Check_Circle(CObject* _pObject1, CObject* _pObject2);

    static bool Check_BossOne(CObject* _pObject1, CObject* _pObject2);

    static bool Check_BossTwo(CObject* _pObject1, CObject* _pObject2);

    static bool Object_Collide(list<CObject*> _Object1, list<CObject*> _Object2, CObject*& _ObjectType1, CObject*& _ObjectType2);
    
    static bool Player_Bullet_BossOne(list<CObject*> _Object1, list<CObject*> _Object2, CObject*& _ObjectType1, CObject*& _ObjectType2);
    
    static bool Player_Bullet_BossTwo(list<CObject*> _Object1, list<CObject*> _Object2, CObject*& _ObjectType1, CObject*& _ObjectType2);

    static bool Check_ObjectCollide(CObject* _pObject1, CObject* _pObject2);

};

