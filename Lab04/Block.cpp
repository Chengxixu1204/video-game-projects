//
//  Block.cpp
//  Lab04
//
//  Created by Chengxi Xu on 2/3/22.
//

#include "Block.hpp"
#include "SpriteComponent.h"
#include "CollisionComponent.h"

Block::Block(class Game* game, char type)
:Actor(game)
{
    sc = new SpriteComponent(this, 100);
    cc = new CollisionComponent(this);
    t = type;
    mGame->AddBlock(this);
    cc->SetSize(32.0f, 32.0f);
    std::string texname = "Assets/Block";
    texname += type;
    texname += ".png";
    sc->SetTexture(mGame->GetTexture(texname));
    
};

Block::~Block(){
    mGame->RemoveBlock(this);
}
