#pragma once

#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Urho2D/TileMap2D.h>
#include <Urho3D/Urho2D/TileMapLayer2D.h>
#include <Urho3D/Urho2D/TmxFile2D.h>
#include <Urho3D/Urho2D/CollisionBox2D.h>
#include <Urho3D/Urho2D/CollisionCircle2D.h>
#include <Urho3D/Urho2D/CollisionPolygon2D.h>
#include <Urho3D/Urho2D/CollisionChain2D.h>
#include <Urho3D/Urho2D/RigidBody2D.h>
#include <Urho3D/Core/StringUtils.h>




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

    void CreateCollisionShapesFromTMXObjects(Node* tileMapNode, TileMapLayer2D* tileMapLayer, const TileMapInfo2D& info);

private:
    ResourceCache* m_pCache;
};
