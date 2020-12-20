#include "TileMapLoader.h"

TileMapLoader::TileMapLoader(ResourceCache* pCache)
{
    m_pCache = pCache;
}

SharedPtr<Node> TileMapLoader::CreateNodeFromTileMap(
        Scene* pScene, 
        const char* path,
        TileMapInfo2D* info)
{
    TmxFile2D* pTMXFile = m_pCache->GetResource<TmxFile2D>(path);
    SharedPtr<Node> tileMapNode(pScene->CreateChild("TileMap"));
    TileMap2D* tileMap = tileMapNode->CreateComponent<TileMap2D>();
    tileMap->SetTmxFile(pTMXFile);


    if(info != nullptr)
    {
        TileMapInfo2D mapInfo = tileMap->GetInfo();
        info = &mapInfo;
    }

    return tileMapNode;
}
