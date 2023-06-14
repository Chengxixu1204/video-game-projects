//
//  Coin.cpp
//  Lab11
//
//  Created by Chengxi Xu on 4/9/22.
//

#include "Coin.hpp"
#include "CollisionComponent.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "MoveComponent.h"
#include "Player.hpp"

Coin::Coin(class Game* game, Actor* parent)
:Actor(game, parent)
{
    mc = new MeshComponent(this);
    cc = new CollisionComponent(this);
    mc->SetMesh(mGame->GetRenderer()->GetMesh("Assets/Coin.gpmesh"));
    cc->SetSize(100, 100, 100);
    movc = new MoveComponent(this);
}

void Coin::OnUpdate(float deltaTime){
    movc->SetAngularSpeed(Math::Pi);
    Vector3 temp;
    if(cc->Intersect(mGame->Getpl()->cc)){
        SetState(ActorState::Destroy);
    }
}
