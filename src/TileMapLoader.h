#pragma once

#include <Urho3D/Urho3DAll.h>
#include "enemy.h"
#include "WinnerTrigger.h"


using namespace Urho3D;

class TileMapLoader
{
public: 
    TileMapLoader() = default;
    TileMapLoader(ResourceCache* cache);
    SharedPtr<Node> CreateNodeFromTileMap(
            Scene* pScene, 
            const char* path,
            TileMapInfo2D* pInfo);
    CollisionBox2D* CreateRectangleShape(Node* node, TileMapObject2D* object, const Vector2& size, const TileMapInfo2D& info);
    CollisionCircle2D* CreateCircleShape(Node* node, TileMapObject2D* object, float radius, const TileMapInfo2D& info);
    CollisionPolygon2D* CreatePolygonShape(Node* node, TileMapObject2D* object);
    CollisionChain2D* CreatePolyLineShape(Node* node, TileMapObject2D* object);
    Enemy* CreateEnemy(Node* node, TileMapObject2D* object, const Vector2& size, const TileMapInfo2D& info);
    void CreateCollisionShapesFromTMXObjects(Node* tileMapNode, TileMapLayer2D* tileMapLayer, const TileMapInfo2D& info);
    void CreateWinTrigger(Node* tileMapNode, TileMapLayer2D* tileMapLayer, const TileMapInfo2D& info);
    void CreateEnemies(Node* tileMapNode, TileMapLayer2D* tileMapLayer, const TileMapInfo2D& info);
    WinnerTrigger* CreateTrigger(Node* node, TileMapObject2D* object, const Vector2& size, const TileMapInfo2D& info);

    Node* winnerTriggerNode;

private:
    ResourceCache* m_pCache;
};
