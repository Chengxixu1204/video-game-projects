//
//  DeadFrog.cpp
//  Lab03
//
//  Created by Chengxi Xu on 2/1/22.
//

#include "DeadFrog.hpp"
#include "SpriteComponent.h"

DeadFrog::DeadFrog(class Game* game)
:Actor(game)
{
    sc = new SpriteComponent(this, 100);
    sc->SetTexture(mGame->GetTexture("Assets/Dead.png"));
    lifetime = 0.0f;
};

void DeadFrog::OnUpdate(float deltaTime){
    lifetime += deltaTime;
    if(lifetime >= 1.0f){
        this->SetState(ActorState::Destroy);
    }
}
