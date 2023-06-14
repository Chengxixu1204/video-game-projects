//
//  SideBlock.cpp
//  Lab07
//
//  Created by Chengxi Xu on 3/6/22.
//

#include "SideBlock.hpp"
#include "MeshComponent.h"
#include "Renderer.h"
#include "Player.hpp"
SideBlock::SideBlock(class Game* game, size_t t)
:Actor(game)
{
    SetScale(500.0f);
    mc = new MeshComponent(this);
    mc->SetMesh(mGame->GetRenderer()->GetMesh("Assets/Cube.gpmesh"));
    mc->SetTextureIndex(t);
    
};

void SideBlock::OnUpdate(float deltaTime){
    if(GetPosition().x <= GetGame()->Getpl()->GetPosition().x - 2000.0f){
        SetState(ActorState::Destroy);
    }
}
