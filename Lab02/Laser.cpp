//
//  Laser.cpp
//  Lab02
//
//  Created by Chengxi Xu on 1/25/22.
//

#include "Laser.hpp"
#include "Asteroid.hpp"
#include "SpriteComponent.h"
#include "MoveComponent.h"

Laser::Laser(class Game* game)
:Actor(game)
{
    //constructor
    mc = new MoveComponent(this);
    mc->SetForwardSpeed(400.0f);
    sc = new SpriteComponent(this, 100);
    sc->SetTexture(mGame->GetTexture("Assets/Laser.png"));
    lifetime = 0.0f;
};

void Laser::OnUpdate(float deltaTime){
    //delete laser after 1 second
    lifetime += deltaTime;
    if(lifetime >= 1.0f){
        this->SetState(ActorState::Destroy);
    }
    for(unsigned int i = 0; i < mGame->asv.size(); i++){
        if(Vector2::Distance(this->GetPosition(), mGame->asv[i]->GetPosition()) <= 70){
            this->SetState(ActorState::Destroy);
            mGame->asv[i]->SetState(ActorState::Destroy);
        }
    }
}
