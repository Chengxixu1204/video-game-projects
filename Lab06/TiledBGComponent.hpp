//
//  TiledBGComponent.hpp
//  Lab06
//
//  Created by Chengxi Xu on 2/17/22.
//

#ifndef TiledBGComponent_hpp
#define TiledBGComponent_hpp

#include <stdio.h>
#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"
#include <vector>
#include <fstream>
#include "CSVHelper.h"

class TiledBGComponent : public SpriteComponent{
public:
    TiledBGComponent(class Actor* owner, int drawOrder = 50);
    void Draw(SDL_Renderer* renderer);
    void LoadTileCSV(const std::string& fileName, int tileWidth, int tileHeight);
private:
    int tile_width;
    int tile_height;
    std::vector<std::vector<int>> store;
    
};


#endif /* TiledBGComponent_hpp */
