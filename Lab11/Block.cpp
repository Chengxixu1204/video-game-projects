//
//  Block.cpp
//  Lab09
//
//  Created by Chengxi Xu on 3/24/22.
//

#include "Block.hpp"
#include "CollisionComponent.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "MoveComponent.h"

Block::Block(class Game* game, Actor* parent)
:Actor(game, parent)
{
    mScale = 64.0f;
    mc = new MeshComponent(this);
    cc = new CollisionComponent(this);
    mc->SetMesh(mGame->GetRenderer()->GetMesh("Assets/Cube.gpmesh"));
    cc->SetSize(1, 1, 1);
    mGame->AddBlock(this);
    movc = new MoveComponent(this);
}

Block::~Block(){
    mGame->RemoveBlock(this);
}

void Block::OnUpdate(float deltaTime){
    if(isrotate){
        movc->SetAngularSpeed((Math::PiOver2)/2);
    }
}
