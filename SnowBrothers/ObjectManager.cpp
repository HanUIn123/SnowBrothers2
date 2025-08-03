#include "pch.h"
#include "ObjectManager.h"
#include "CollisionManager.h"
#include "Player.h"
#include "Item.h"
#include "Monster.h"

#include "Bullet.h"

#include "Player.h"


#include "Tile.h"
#include "TileManager.h"

#include "SoundMgr.h"
#include "EffectManager.h"

CObjectManager* CObjectManager::m_pInstance = nullptr;

CObjectManager::CObjectManager() :
    m_pObject(nullptr),
    m_dwPlayerTime(GetTickCount64()),
    m_iDrawIdNumber(0)
{
}

CObjectManager::~CObjectManager()
{
    Release();
}

void CObjectManager::Add_Object(OBJECT_LIST _eObList, CObject* _pObject)
{
    if ((UINT)OBJECT_LIST::OL_END <= (UINT)_eObList || nullptr == _pObject)
    {
        return;
    }

    m_ObjectList[(UINT)_eObList].emplace_back(_pObject);
}

int CObjectManager::Update()
{
    int iResult(0);

    for (UINT i = 0; i < (UINT)OBJECT_LIST::OL_END; ++i)
    {
        for (auto iter = m_ObjectList[i].begin(); iter != m_ObjectList[i].end();)
        {
            iResult = (*iter)->Update();

            if (iResult == (UINT)OBJECT_STATE::OBJ_DEAD)
            {
                Safe_Delete<CObject*>(*iter);

                if ((UINT)OBJECT_LIST::PLAYER)
                {
                    iter = m_ObjectList[i].erase(iter);
                }
                iter = m_ObjectList[i].erase(iter);
            }
            else
                ++iter;
        }
    }
    return iResult;
}

void CObjectManager::Late_Update()
{
    for (UINT i = 0; i < (UINT)OBJECT_LIST::OL_END; ++i)
    {
        for (auto& pObject : m_ObjectList[i])
            pObject->Late_Update();
    }

    Object_Collision();
}


void CObjectManager::Render(HDC _hDC)
{
    for (UINT i = 0; i < (UINT)OBJECT_LIST::OL_END; ++i)
    {
        for (auto& pObject : m_ObjectList[i])
            pObject->Render(_hDC);
    }
}

void CObjectManager::Release()
{
    // PLAYER, MONSTER, ITEM, BULLET, TILE, MOUSE, UI, EFFECT, BUTTON, OL_END
    for (UINT i = 0; i < (UINT)OBJECT_LIST::OL_END; ++i)
    {
        for (auto& pObject : m_ObjectList[i])
        {
            Safe_Delete<CObject*>(pObject);
        }

        m_ObjectList[i].clear();
    }
}

void CObjectManager::Object_Collision()
{
    CObject* _pObject1(nullptr);
    CObject* _pObject2(nullptr);

    m_pObject = CObjectManager::Get_Instance()->Get_ObjectList(OBJECT_LIST::PLAYER).front();

    // 플레이어 투사체와 몬스터 충돌, 
    if (CCollisionManager::Object_Collide(m_ObjectList[(UINT)OBJECT_LIST::BULLET], m_ObjectList[(UINT)OBJECT_LIST::MONSTER],
        _pObject1, _pObject2))
    {
        if (_pObject2->Get_CollisionName() == L"ENEMYONE" || _pObject2->Get_CollisionName() == L"ENEMYONESNOW")
        {
            _pObject1 = Get_ObjectList(OBJECT_LIST::BULLET).front();
            _pObject1->Set_Dead(true);

            CEffectManager::Get_Instance()->Set_BeTriggered(true);
            CEffectManager::Get_Instance()->Get_Effect_Pos(_pObject2->Get_ObjectInfo().fX, _pObject2->Get_ObjectInfo().fY);

            dynamic_cast<CMonster*>(_pObject2)->Set_Hited(true);

            if (dynamic_cast<CMonster*>(_pObject2)->Get_Hited())
            {
                dynamic_cast<CMonster*>(_pObject2)->Set_FallingTrue();
            }

            if (!dynamic_cast<CBullet*>(_pObject1)->Get_BulletUpgraded())
                dynamic_cast<CMonster*>(_pObject2)->Set_SnowStat(1);
            else
                dynamic_cast<CMonster*>(_pObject2)->Set_SnowStat(2);

            if (!dynamic_cast<CBullet*>(_pObject1)->Get_BulletRanged())
                dynamic_cast<CBullet*>(_pObject1)->Set_Speed(7.0f);
            else
                dynamic_cast<CBullet*>(_pObject1)->Set_Speed(14.0f);
        }
        if (_pObject2->Get_CollisionName() == L"ENEMYONESNOW")
        {
            if (dynamic_cast<CPlayer*>(m_pObject)->Get_Ranged())
            {
                if (_pObject1->Get_Direction() == OBJECT_DIRECTION::DIR_RIGHT)
                    _pObject2->Set_PosX(-7.0f);
                else if (_pObject1->Get_Direction() == OBJECT_DIRECTION::DIR_LEFT)
                    _pObject2->Set_PosX(7.0f);
            }
            else
            {
                if (_pObject1->Get_Direction() == OBJECT_DIRECTION::DIR_RIGHT)
                    _pObject2->Set_PosX(-2.0f);
                else if (_pObject1->Get_Direction() == OBJECT_DIRECTION::DIR_LEFT)
                    _pObject2->Set_PosX(2.0f);
            }

        }
    }

    // ================================================================================================

    // 플레이어 투사체와 미니언들 충돌,
    if (CCollisionManager::Object_Collide(m_ObjectList[(UINT)OBJECT_LIST::BULLET], m_ObjectList[(UINT)OBJECT_LIST::MINION],
        _pObject1, _pObject2))
    {
        if (_pObject2->Get_CollisionName() == L"MINION" || _pObject2->Get_CollisionName() == L"MINIONSNOW")
        {
            _pObject1 = Get_ObjectList(OBJECT_LIST::BULLET).front();
            _pObject1->Set_Dead(true);

            CEffectManager::Get_Instance()->Set_BeTriggered(true);
            CEffectManager::Get_Instance()->Get_Effect_Pos(_pObject2->Get_ObjectInfo().fX, _pObject2->Get_ObjectInfo().fY);

            dynamic_cast<CMonster*>(_pObject2)->Set_Hited(true);

            if (!dynamic_cast<CBullet*>(_pObject1)->Get_BulletUpgraded())
                dynamic_cast<CMonster*>(_pObject2)->Set_SnowStat(1);
            else
                dynamic_cast<CMonster*>(_pObject2)->Set_SnowStat(2);

        }
        if (_pObject2->Get_CollisionName() == L"MINIONSNOW")
        {
            if (_pObject1->Get_Direction() == OBJECT_DIRECTION::DIR_RIGHT)
                _pObject2->Set_PosX(-2.0f);
            else if (_pObject1->Get_Direction() == OBJECT_DIRECTION::DIR_LEFT)
                _pObject2->Set_PosX(2.0f);
        }
    }

    // ================================================================================================

    // 플레이어 투사체와 보스(슬롯) 충돌,
    if (CCollisionManager::Player_Bullet_BossOne(m_ObjectList[(UINT)OBJECT_LIST::BULLET], m_ObjectList[(UINT)OBJECT_LIST::BOSS],
        _pObject1, _pObject2))
    {
        if (_pObject2->Get_CollisionName() == L"BOSSONE")
        {
            _pObject1 = Get_ObjectList(OBJECT_LIST::BULLET).front();
            _pObject1->Set_Dead(true);

            CEffectManager::Get_Instance()->Set_BeTriggered(true);
            CEffectManager::Get_Instance()->Get_Effect_Pos(_pObject2->Get_ObjectInfo().fX, _pObject2->Get_ObjectInfo().fY);

            dynamic_cast<CMonster*>(_pObject2)->Set_Hited(true);
        }
    }

    // 플레이어 투사체와 보스(기차) 충돌,
    if (CCollisionManager::Player_Bullet_BossTwo(m_ObjectList[(UINT)OBJECT_LIST::BULLET], m_ObjectList[(UINT)OBJECT_LIST::BOSS],
        _pObject1, _pObject2))
    {
        if (_pObject2->Get_CollisionName() == L"BOSSTWO")
        {
            _pObject1 = Get_ObjectList(OBJECT_LIST::BULLET).front();
            _pObject1->Set_Dead(true);

            CEffectManager::Get_Instance()->Set_BeTriggered(true);
            CEffectManager::Get_Instance()->Get_Effect_Pos(_pObject2->Get_ObjectInfo().fX, _pObject2->Get_ObjectInfo().fY);

            dynamic_cast<CMonster*>(_pObject2)->Set_Hited(true);
        }
    }



    // 몬스터 투사체와 플레이어 충돌,
    if (CCollisionManager::Object_Collide(m_ObjectList[(UINT)OBJECT_LIST::MONSTERBULLET], m_ObjectList[(UINT)OBJECT_LIST::PLAYER],
        _pObject1, _pObject2))
    {
        if (_pObject2->Get_CollisionName() == L"TOM")
        {
            _pObject1 = Get_ObjectList(OBJECT_LIST::MONSTERBULLET).front();
            _pObject1->Set_Dead(true);
            dynamic_cast<CPlayer*>(_pObject2)->Set_BeforeDie(true);
        }
    }

    // 보스 투사체와 플레이어 충돌,
    if (CCollisionManager::Object_Collide(m_ObjectList[(UINT)OBJECT_LIST::BOSSBULLET], m_ObjectList[(UINT)OBJECT_LIST::PLAYER],
        _pObject1, _pObject2))
    {
        if (_pObject2->Get_CollisionName() == L"TOM")
        {
            _pObject1 = Get_ObjectList(OBJECT_LIST::BOSSBULLET).front();
            _pObject1->Set_Dead(true);
            dynamic_cast<CPlayer*>(_pObject2)->Set_BeforeDie(true);
        }
    }

    if (dynamic_cast<CPlayer*>(m_pObject)->Get_UnlimitedSuperMode() == false)
    {
        if (dynamic_cast<CPlayer*>(m_pObject)->Get_SuperMode() == false)
        {
            // 플레이어와 몬스터의 충돌,(눈덩이 밀기) 
            if (CCollisionManager::Object_Collide(m_ObjectList[(UINT)OBJECT_LIST::PLAYER], m_ObjectList[(UINT)OBJECT_LIST::MONSTER],
                _pObject1, _pObject2))
            {
                float fx(0.0f);
                float fy(0.0f);
                if (_pObject2->Get_CollisionName() == L"ENEMYONESNOW")
                {
                    if (CCollisionManager::Check_Rect(_pObject1, _pObject2, &fx, &fy))
                    {
                        dynamic_cast<CPlayer*>(_pObject1)->Set_CanPush(true);
                    }
                    else
                    {
                        dynamic_cast<CPlayer*>(_pObject1)->Set_CanPush(false);
                    }
                }
                else if (_pObject2->Get_CollisionName() == L"ENEMYONE" && dynamic_cast<CMonster*>(_pObject2)->Get_SnowStat() == 0 &&
                    dynamic_cast<CMonster*>(_pObject2)->Get_ReadyToDie() == false)
                {
                    if (CCollisionManager::Check_Rect(_pObject1, _pObject2, &fx, &fy))
                    {
                        dynamic_cast<CPlayer*>(_pObject1)->Set_BeforeDie(true);
                        CSoundMgr::Get_Instance()->PlaySound(L"Player_Dead.wav", PLAYER_DEAD, 1.0f);
                    }
                    else
                    {
                        dynamic_cast<CPlayer*>(_pObject1)->Set_BeforeDie(false);
                    }
                }

                if (dynamic_cast<CPlayer*>(_pObject1)->Get_CanPush() == true)
                {
                    dynamic_cast<CPlayer*>(_pObject1)->Set_TargeetMonster(_pObject2);
                    CCollisionManager::Collision_Snow(m_ObjectList[(UINT)OBJECT_LIST::PLAYER], m_ObjectList[(UINT)OBJECT_LIST::MONSTER]);
                }

                if (dynamic_cast<CMonster*>(_pObject2)->Get_Dead() == true)
                {
                    dynamic_cast<CPlayer*>(_pObject1)->Set_CanPush(false);
                }
            }

            // ================================================================================================

            // 플레이어와 미니언들의 충돌,(눈덩이 밀기) 
            if (CCollisionManager::Object_Collide(m_ObjectList[(UINT)OBJECT_LIST::PLAYER], m_ObjectList[(UINT)OBJECT_LIST::MINION],
                _pObject1, _pObject2))
            {
                float fx(0.0f);
                float fy(0.0f);
                if (_pObject2->Get_CollisionName() == L"MINIONSNOW")
                {
                    if (dynamic_cast<CMonster*>(_pObject2)->Get_SnowBallMove() == false)
                    {
                        if (CCollisionManager::Check_Rect(_pObject1, _pObject2, &fx, &fy))
                        {
                            dynamic_cast<CPlayer*>(_pObject1)->Set_CanPush(true);
                        }
                        else
                        {
                            dynamic_cast<CPlayer*>(_pObject1)->Set_CanPush(false);
                        }
                    }
                }
                else if (_pObject2->Get_CollisionName() == L"MINION" && dynamic_cast<CMonster*>(_pObject2)->Get_SnowStat() == 0 &&
                    dynamic_cast<CMonster*>(_pObject2)->Get_ReadyToDie() == false)
                {
                    if (CCollisionManager::Check_Rect(_pObject1, _pObject2, &fx, &fy))
                    {
                        dynamic_cast<CPlayer*>(_pObject1)->Set_BeforeDie(true);
                        CSoundMgr::Get_Instance()->PlaySound(L"Player_Dead.wav", PLAYER_DEAD, 1.0f);
                    }
                    else
                    {
                        dynamic_cast<CPlayer*>(_pObject1)->Set_BeforeDie(false);
                    }
                }

                if (dynamic_cast<CPlayer*>(_pObject1)->Get_CanPush() == true)
                {
                    dynamic_cast<CPlayer*>(_pObject1)->Set_TargeetMonster(_pObject2);
                    CCollisionManager::Collision_Snow(m_ObjectList[(UINT)OBJECT_LIST::PLAYER], m_ObjectList[(UINT)OBJECT_LIST::MINION]);
                }

                if (dynamic_cast<CMonster*>(_pObject2)->Get_Dead() == true)
                {
                    dynamic_cast<CPlayer*>(_pObject1)->Set_CanPush(false);
                }
            }

            // ================================================================================================

            // 플레이어와 보스들의 충돌
            if (CCollisionManager::Object_Collide(m_ObjectList[(UINT)OBJECT_LIST::PLAYER], m_ObjectList[(UINT)OBJECT_LIST::BOSS],
                _pObject1, _pObject2))
            {
                float fx(0.0f);
                float fy(0.0f);
                if (_pObject2->Get_CollisionName() == L"BOSSONE")
                {
                    if (CCollisionManager::Check_BossOne(_pObject1, _pObject2, &fx, &fy))
                    {
                        dynamic_cast<CPlayer*>(_pObject1)->Set_BeforeDie(true);
                        CSoundMgr::Get_Instance()->PlaySound(L"Player_Dead.wav", PLAYER_DEAD, 1.0f);
                    }
                    else
                    {
                        dynamic_cast<CPlayer*>(_pObject1)->Set_BeforeDie(false);
                    }
                }
            }

        }

        // 플레이어와 눈 충돌(플레이어가 눈을 타고 같이 돌아감)

        if (CCollisionManager::Object_Collide(m_ObjectList[(UINT)OBJECT_LIST::PLAYER], m_ObjectList[(UINT)OBJECT_LIST::MONSTER],
            _pObject1, _pObject2))
        {
            float fx(0.0f);
            float fy(0.0f);
            if (_pObject2->Get_CollisionName() == L"ENEMYONESNOW" && dynamic_cast<CMonster*>(_pObject2)->Get_SnowBallMove() &&
                (abs(dynamic_cast<CMonster*>(_pObject2)->Get_SnowBallSpeed()) >= 9.0f) && dynamic_cast<CMonster*>(_pObject2)->Get_CollideCount() >= 1)
            {
                if (CCollisionManager::Check_Rect(_pObject1, _pObject2, &fx, &fy))
                {
                    dynamic_cast<CPlayer*>(_pObject1)->Set_CanRolling(true);

                    dynamic_cast<CMonster*>(_pObject2)->Set_WithPlayer(true);
                }
            }

            if (dynamic_cast<CMonster*>(_pObject2)->Get_CollideCount() >= 9)
            {
                dynamic_cast<CPlayer*>(_pObject1)->Set_CanRolling(false);
                dynamic_cast<CMonster*>(_pObject2)->Set_WithPlayer(false);
            }


        }

        // 플레이어와 미니언눈 충돌(플레이어가 눈을 타고 같이 돌아감)
        if (CCollisionManager::Object_Collide(m_ObjectList[(UINT)OBJECT_LIST::PLAYER], m_ObjectList[(UINT)OBJECT_LIST::MINION],
            _pObject1, _pObject2))
        {
            float fx(0.0f);
            float fy(0.0f);
            if (_pObject2->Get_CollisionName() == L"MINIONSNOW" && dynamic_cast<CMonster*>(_pObject2)->Get_SnowBallMove() &&
                (abs(dynamic_cast<CMonster*>(_pObject2)->Get_SnowBallSpeed()) >= 9.0f) && dynamic_cast<CMonster*>(_pObject2)->Get_CollideCount() >= 1)
            {
                if (CCollisionManager::Check_Rect(_pObject1, _pObject2, &fx, &fy))
                {
                    //dynamic_cast<CPlayer*>(_pObject1)->Set_CanRolling(true);

                    //dynamic_cast<CMonster*>(_pObject2)->Set_WithPlayer(true);
                }
            }

            if (dynamic_cast<CMonster*>(_pObject2)->Get_CollideCount() >= 5)
            {
                dynamic_cast<CPlayer*>(m_pObject)->Set_CanRolling(false);
                dynamic_cast<CMonster*>(_pObject2)->Set_WithPlayer(false);
            }
        }

        // ================================================================================================
    }


    // 플레이어와 타일 상 충돌,
    CCollisionManager::Collision_Tile_Player(m_ObjectList[(UINT)OBJECT_LIST::PLAYER], CTileManager::Get_Instance()->Get_TileVector());

    // 플레이어와 눈 상 충돌.
    if (dynamic_cast<CPlayer*>(m_pObject)->Get_SuperMode() == false)
        CCollisionManager::Collision_Snow_Player(m_ObjectList[(UINT)OBJECT_LIST::PLAYER], m_ObjectList[(UINT)OBJECT_LIST::MONSTER]);

    // 플레이어와 미니언 눈 상 충돌.
    if (dynamic_cast<CPlayer*>(m_pObject)->Get_SuperMode() == false)
        CCollisionManager::Collision_Snow_Player_Minion(m_ObjectList[(UINT)OBJECT_LIST::PLAYER], m_ObjectList[(UINT)OBJECT_LIST::MINION]);

    // 몬스터들과 타일 상 충돌,
    CCollisionManager::Collision_Tile_Monster(m_ObjectList[(UINT)OBJECT_LIST::MONSTER], CTileManager::Get_Instance()->Get_TileVector());

    //CCollisionManager::Collision_Tile_Monster(m_ObjectList[(UINT)OBJECT_LIST::MINION], CTileManager::Get_Instance()->Get_TileVector());

    // 미니언들과 타일 상 충돌,
    CCollisionManager::Collision_Tile_Minion(m_ObjectList[(UINT)OBJECT_LIST::MINION], CTileManager::Get_Instance()->Get_TileVector());

    // 보스1과 타일 충돌
    CCollisionManager::Collision_Tile_Boss(m_ObjectList[(UINT)OBJECT_LIST::BOSS], CTileManager::Get_Instance()->Get_TileVector());

    // 보스2와 타일 충돌 
    CCollisionManager::Collision_Tile_BossTwo(m_ObjectList[(UINT)OBJECT_LIST::BOSS], CTileManager::Get_Instance()->Get_TileVector());

    // 몬스터들끼리 충돌 (눈으로 처치하는 충돌식 + 눈과 눈의 충돌까지 )
    CCollisionManager::Collision_Between_Monsters(m_ObjectList[(UINT)OBJECT_LIST::MONSTER], m_ObjectList[(UINT)OBJECT_LIST::MONSTER]);

    // 미니언들끼리 충돌 (눈으로 처치하는 충돌식 + 눈과 눈의 충돌까지 )
    CCollisionManager::Collision_Between_Minions(m_ObjectList[(UINT)OBJECT_LIST::MINION], m_ObjectList[(UINT)OBJECT_LIST::MINION]);

    // ================================================================================================

    // 미니언(눈)들과 보스(슬롯)의 충돌 
    CCollisionManager::Collision_BossOne_Minions(m_ObjectList[(UINT)OBJECT_LIST::BOSS], m_ObjectList[(UINT)OBJECT_LIST::MINION]);

    // 미니언(눈)들과 보스(기차)의 충돌 
    CCollisionManager::Collision_BossTwo_Minions(m_ObjectList[(UINT)OBJECT_LIST::BOSS], m_ObjectList[(UINT)OBJECT_LIST::MINION]);

    // 플레이어와 아이템 충돌
    if (CCollisionManager::Object_Collide(m_ObjectList[(UINT)OBJECT_LIST::PLAYER], m_ObjectList[(UINT)OBJECT_LIST::ITEM],
        _pObject1, _pObject2))
    {
        CSoundMgr::Get_Instance()->PlaySound(L"Get_Item.wav", SOUND_ITEM, 1.0f);

        if (_pObject2->Get_CollisionName() == L"SPEED")
        {
            CSoundMgr::Get_Instance()->PlaySound(L"SpeedUp.wav", SOUND_ITEM, 1.0f);
            dynamic_cast<CPlayer*>(_pObject1)->Set_Speed(4.5f);
        }
        else if (_pObject2->Get_CollisionName() == L"POWER")
        {
            // player's power 관련. 
            CSoundMgr::Get_Instance()->PlaySound(L"PowerUp.wav", SOUND_ITEM, 1.0f);
            dynamic_cast<CPlayer*>(_pObject1)->Set_UpgradeBullet(true);
            dynamic_cast<CItem*>(_pObject2)->Set_BulletUpgrade(true);
        }
        else if (_pObject2->Get_CollisionName() == L"RANGE")
        {
            CSoundMgr::Get_Instance()->PlaySound(L"RangeUp.wav", SOUND_ITEM, 1.0f);
            dynamic_cast<CPlayer*>(_pObject1)->Set_Ranged(true);
            dynamic_cast<CItem*>(_pObject2)->Set_BulletRanged(true);
        }

        dynamic_cast<CItem*>(_pObject2)->Set_Dead(true);
    }

}
