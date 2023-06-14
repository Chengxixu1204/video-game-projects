//
//  TiledBGComponent.cpp
//  Lab06
//
//  Created by Chengxi Xu on 2/17/22.
//

#include "TiledBGComponent.hpp"


TiledBGComponent::TiledBGComponent(Actor* owner, int drawOrder)
    :SpriteComponent(owner)
{
   
}
void TiledBGComponent::Draw(SDL_Renderer* renderer)
{
    if (mTexture)
    {
        int length = GetTexWidth();
        int num = length/tile_width;
        SDL_Rect s;
        s.w = tile_width;
        s.h = tile_height;
        SDL_Rect r;
        r.w = tile_width;
        r.h = tile_height;
        for(size_t i = 0; i < store.size(); i++){
            for(size_t j = 0; j <store[i].size(); j++){
                if(store[i][j] != -1){
                    s.x = (store[i][j]%num)*tile_width;
                    s.y = (store[i][j]/num)*tile_height;
                    r.x = static_cast<int>(j*tile_width);
                    r.y = static_cast<int>(i*tile_height);
                    r.x -= static_cast<int>(mOwner->GetGame()->camera.x);
                    r.y -= static_cast<int>(mOwner->GetGame()->camera.y);
                    SDL_RenderCopyEx(renderer,
                            mTexture,
                            &s,
                            &r,
                            0.0,
                            nullptr,
                            SDL_FLIP_NONE);
                    }
                }
            }
        }
        
}

void TiledBGComponent::LoadTileCSV(const std::string& fileName, int tileWidth, int tileHeight){
    std::ifstream infile(fileName);
    std::string line;
    int count = 0;
    tile_width = tileWidth;
    tile_height = tileHeight;
    while (std::getline(infile, line)){
        std::vector<std::string> temp;
        std::vector<int> trans;
        if(line.size() != 0){
            temp = CSVHelper::Split(line);
            for(size_t i = 0; i < temp.size(); i++){
                trans.push_back(std::stoi(temp[i]));
            }
        }
        store.push_back(trans);
        count++;
    }
    
}
