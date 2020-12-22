#include "WinnerTrigger.h"
#include "TileMapLoader.h"
#include "enemy.h"
#include <iostream>
#include <ctime>
TileMapLoader::TileMapLoader(ResourceCache* pCache)
{
    m_pCache = pCache;
}

SharedPtr<Node> TileMapLoader::CreateNodeFromTileMap(
        Scene* pScene, 
        const char* path,
        TileMapInfo2D* pInfo)
{
    TmxFile2D* pTMXFile = m_pCache->GetResource<TmxFile2D>(path);
    SharedPtr<Node> tileMapNode(pScene->CreateChild("TileMap"));
    TileMap2D* tileMap = tileMapNode->CreateComponent<TileMap2D>();
    tileMap->SetTmxFile(pTMXFile);


    if(pInfo != nullptr)
    {
        TileMapInfo2D mapInfo = tileMap->GetInfo();
        pInfo = &mapInfo;
    }

    return tileMapNode;
}
void TileMapLoader::CreateCollisionShapesFromTMXObjects(Node* tileMapNode, TileMapLayer2D* tileMapLayer, const TileMapInfo2D& info)
{
    // Create rigid body to the root node
    auto* body = tileMapNode->CreateComponent<RigidBody2D>();
    body->SetBodyType(BT_STATIC);

    // Generate physics collision shapes and rigid bodies from the tmx file's objects located in "Physics" layer
    for (unsigned i = 0; i < tileMapLayer->GetNumObjects(); ++i)
    {
        TileMapObject2D* tileMapObject = tileMapLayer->GetObject(i);
        // Create collision shape from tmx object
        switch (tileMapObject->GetObjectType())
        {
        case OT_RECTANGLE:
        {
            CreateRectangleShape(tileMapNode, tileMapObject, tileMapObject->GetSize(), info);
        }
        break;

        case OT_ELLIPSE:
        {
            CreateCircleShape(tileMapNode, tileMapObject, tileMapObject->GetSize().x_ / 2, info); // Ellipse is built as a Circle shape as it doesn't exist in Box2D
        }
        break;

        case OT_POLYGON:
        {
            CreatePolygonShape(tileMapNode, tileMapObject);
        }
        break;

        case OT_POLYLINE:
        {
            CreatePolyLineShape(tileMapNode, tileMapObject);
        }
        break;
        }
    }
}

CollisionBox2D* TileMapLoader::CreateRectangleShape(Node* node, TileMapObject2D* object, const Vector2& size, const TileMapInfo2D& info)
{
    auto* shape = node->CreateComponent<CollisionBox2D>();
    shape->SetSize(size);
    if (info.orientation_ == O_ORTHOGONAL)
        shape->SetCenter(object->GetPosition() + size / 2);
    else
    {
        shape->SetCenter(object->GetPosition() + Vector2(info.tileWidth_ / 2, 0.0f));
        shape->SetAngle(45.0f); // If our tile map is isometric then shape is losange
    }
    shape->SetFriction(0.8f);
    if (object->HasProperty("Friction"))
        shape->SetFriction(ToFloat(object->GetProperty("Friction")));
    return shape;
}
CollisionCircle2D* TileMapLoader::CreateCircleShape(Node* node, TileMapObject2D* object, float radius, const TileMapInfo2D& info)
{
    auto* shape = node->CreateComponent<CollisionCircle2D>();
    Vector2 size = object->GetSize();
    if (info.orientation_ == O_ORTHOGONAL)
        shape->SetCenter(object->GetPosition() + size / 2);
    else
    {
        shape->SetCenter(object->GetPosition() + Vector2(info.tileWidth_ / 2, 0.0f));
    }

    shape->SetRadius(radius);
    shape->SetFriction(0.8f);
    if (object->HasProperty("Friction"))
        shape->SetFriction(ToFloat(object->GetProperty("Friction")));
    return shape;
}
CollisionPolygon2D* TileMapLoader::CreatePolygonShape(Node* node, TileMapObject2D* object)
{
    auto* shape = node->CreateComponent<CollisionPolygon2D>();
    int numVertices = object->GetNumPoints();
    shape->SetVertexCount(numVertices);
    for (int i = 0; i < numVertices; ++i)
        shape->SetVertex(i, object->GetPoint(i));
    shape->SetFriction(0.8f);
    if (object->HasProperty("Friction"))
        shape->SetFriction(ToFloat(object->GetProperty("Friction")));
    return shape;
}
CollisionChain2D* TileMapLoader::CreatePolyLineShape(Node* node, TileMapObject2D* object)
{
    auto* shape = node->CreateComponent<CollisionChain2D>();
    int numVertices = object->GetNumPoints();
    shape->SetVertexCount(numVertices);
    for (int i = 0; i < numVertices; ++i)
        shape->SetVertex(i, object->GetPoint(i));
    shape->SetFriction(0.8f);
    if (object->HasProperty("Friction"))
        shape->SetFriction(ToFloat(object->GetProperty("Friction")));
    return shape;
}
WinnerTrigger* TileMapLoader::CreateTrigger(Node* node, TileMapObject2D* object, const Vector2& size, const TileMapInfo2D& info)
{
    winnerTriggerNode = node->CreateChild("WinTrigger");
    winnerTriggerNode->SetPosition(object->GetPosition() + size / 2);
    WinnerTrigger* winnerTriggerC = winnerTriggerNode->CreateComponent<WinnerTrigger>();
    winnerTriggerC->Init();

    //RigidBody2D* rg = winnerTriggerNode->CreateComponent<RigidBody2D>();
    //rg->GetGravityScale(0)
    //shape->
    return winnerTriggerC;
}
void TileMapLoader::CreateWinTrigger(Node* tileMapNode, TileMapLayer2D* tileMapLayer, const TileMapInfo2D& info)
{
    // Create rigid body to the root node
    auto* body = tileMapNode->CreateComponent<RigidBody2D>();
    body->SetBodyType(BT_STATIC);

    int numObjects = tileMapLayer->GetNumObjects();
    srand((unsigned)time(0));
    int result = (rand() % numObjects);

    TileMapObject2D* tileMapObject = tileMapLayer->GetObject(result);
    CreateTrigger(tileMapNode, tileMapObject, tileMapObject->GetSize(), info);
}
Enemy* TileMapLoader::CreateEnemy(Node* node, TileMapObject2D* object, const Vector2& size, const TileMapInfo2D& info)
{
    Node* enemyN = node->CreateChild("Enemy");
    enemyN->SetPosition(object->GetPosition() + size / 2);
    Enemy* enemyC = enemyN->CreateComponent<Enemy>();
    enemyC->Init();

    return enemyC;
}

void TileMapLoader::CreateEnemies(Node* tileMapNode, TileMapLayer2D* tileMapLayer, const TileMapInfo2D& info)
{

    int numObjects = tileMapLayer->GetNumObjects();

    for (unsigned i = 0; i < tileMapLayer->GetNumObjects(); ++i)
    {
        TileMapObject2D* tileMapObject = tileMapLayer->GetObject(i);
        //CreateRectangleShape(tileMapNode, tileMapObject, tileMapObject->GetSize(), info);
        CreateEnemy(tileMapNode, tileMapObject, tileMapObject->GetSize(), info);
    }
}