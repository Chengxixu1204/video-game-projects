//
//  Goomba.cpp
//  Lab04
//
//  Created by Chengxi Xu on 2/6/22.
//

#include "Goomba.hpp"
#include "SpriteComponent.h"
#include "GoombaMove.hpp"
#include "CollisionComponent.h"
#include "AnimatedSprite.h"

Goomba::Goomba(class Game* game)
:Actor(game)
{
    cc = new CollisionComponent(this);
    cc->SetSize(32.0f, 32.0f);
    mGame->AddGoomba(this);
    gm = new GoombaMove(this);
    stomp = false;
    time = 0.0f;
    as = new AnimatedSprite(this);
    std::vector<SDL_Texture*> walkAnim{
        GetGame()->GetTexture("Assets/Goomba/Walk0.png"),
        GetGame()->GetTexture("Assets/Goomba/Walk1.png")
    };
    
    std::vector<SDL_Texture*> dead{
        GetGame()->GetTexture("Assets/Goomba/Dead.png"),
    };

    as->AddAnimation("walk", walkAnim);
    as->SetAnimation("walk");
    as->AddAnimation("dead", dead);
    
};

Goomba::~Goomba(){
    mGame->RemoveGoomba(this);
}

void Goomba::OnUpdate(float deltaTime){
    
    if(stomp){
        time += deltaTime;
        as->SetAnimation("dead");
        this->SetPosition(this->GetPosition());
        gm->move = false;
        //this->cc = nullptr;
        if(time >= 0.25f ){
            this->SetState(ActorState::Destroy);
        }
    }
    
}
