//
//  Spawner.cpp
//  Lab04
//
//  Created by Chengxi Xu on 2/7/22.
//

#include "Spawner.hpp"
#include "Player.hpp"
#include "Goomba.hpp"

Spawner::Spawner(class Game* game)
:Actor(game)
{
    
};

void Spawner::OnUpdate(float deltaTime){
    if(Math::Abs(this->GetPosition().x - mGame->pl->GetPosition().x) < 600.0f){
        Goomba* gb = new Goomba(mGame);
        gb->SetPosition(this->GetPosition());
        this->SetState(ActorState::Destroy);
    }
}
