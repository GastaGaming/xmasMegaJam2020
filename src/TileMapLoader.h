#pragma once

#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Urho2D/TileMap2D.h>
#include <Urho3D/Urho2D/TileMapLayer2D.h>
#include <Urho3D/Urho2D/TmxFile2D.h>

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

private:
    ResourceCache* m_pCache;
};
