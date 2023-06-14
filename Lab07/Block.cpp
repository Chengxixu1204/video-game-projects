//
//  Block.cpp
//  Lab07
//
//  Created by Chengxi Xu on 3/8/22.
//

#include "Block.hpp"
#include "MeshComponent.h"
#include "CollisionComponent.h"
#include "Renderer.h"
#include "Player.hpp"
Block::Block(class Game* game, size_t t)
:Actor(game)
{
    SetScale(25.0f);
    mc = new MeshComponent(this);
    mc->SetMesh(mGame->GetRenderer()->GetMesh("Assets/Cube.gpmesh"));
    mc->SetTextureIndex(t);
    texture = t;
    cc = new CollisionComponent(this);
    cc->SetSize(1.0f, 1.0f, 1.0f);
    mGame->AddBlock(this);
    if(t == 4){
        explode = true;
    }else{
        explode = false;
    }
    
    
};

Block::~Block(){
    mGame->RemoveBlock(this);
}

void Block::OnUpdate(float deltaTime){
    if(GetPosition().x <= GetGame()->Getpl()->GetPosition().x - 2000.0f){
        SetState(ActorState::Destroy);
    }
}
