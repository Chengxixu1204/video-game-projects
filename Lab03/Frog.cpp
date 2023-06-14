//
//  Frog.cpp
//  Lab03
//
//  Created by Chengxi Xu on 1/27/22.
//

#include "Frog.hpp"
#include "Vehicle.hpp"
#include "SpriteComponent.h"
#include "DeadFrog.hpp"

Frog::Frog(class Game* game)
:Actor(game)
{
    sc = new SpriteComponent(this, 100);
    nmap.insert({SDL_SCANCODE_UP, false});
    nmap.insert({SDL_SCANCODE_DOWN, false});
    nmap.insert({SDL_SCANCODE_RIGHT, false});
    nmap.insert({SDL_SCANCODE_LEFT, false});
    cc = new CollisionComponent(this);
    cc->SetSize(50.0f, 50.0f);
    mGame->SetFrog(this);
};

void Frog::OnProcessInput(const Uint8* keyState){
    
    if((keyState[SDL_SCANCODE_UP]) && !(nmap[SDL_SCANCODE_UP])){
        Vector2 current_position = this->GetPosition();
        float new_y = Math::Clamp(current_position.y - 64.0f, 0.0f, 1024.0f);
        this->SetPosition(Vector2(current_position.x, new_y));
    }else if((keyState[SDL_SCANCODE_DOWN]) && !(nmap[SDL_SCANCODE_DOWN])){
        Vector2 current_position = this->GetPosition();
        float new_y = Math::Clamp(current_position.y + 64.0f, 0.0f, 1024.0f);
        this->SetPosition(Vector2(current_position.x, new_y));
    }else if((keyState[SDL_SCANCODE_RIGHT]) && !(nmap[SDL_SCANCODE_RIGHT])){
        Vector2 current_position = this->GetPosition();
        float new_x = Math::Clamp(current_position.x + 64.0f, 0.0f, 896.0f);
        this->SetPosition(Vector2(new_x, current_position.y));
    }else if((keyState[SDL_SCANCODE_LEFT]) && !(nmap[SDL_SCANCODE_LEFT])){
        Vector2 current_position = this->GetPosition();
        float new_x = Math::Clamp(current_position.x - 64.0f, 0.0f, 896.0f);
        this->SetPosition(Vector2(new_x, current_position.y));
    }
    nmap[SDL_SCANCODE_LEFT] = keyState[SDL_SCANCODE_LEFT];
    nmap[SDL_SCANCODE_RIGHT] = keyState[SDL_SCANCODE_RIGHT];
    nmap[SDL_SCANCODE_UP] = keyState[SDL_SCANCODE_UP];
    nmap[SDL_SCANCODE_DOWN] = keyState[SDL_SCANCODE_DOWN];
}

void Frog::OnUpdate(float deltaTime){
    bool water = true;
    bool goal = false;
    for(auto l: mGame->getterv()){
        if(cc->Intersect(l->cc)){
            DeadFrog* v = new DeadFrog(mGame);
            v->SetPosition(this->GetPosition());
            this->SetPosition(Vector2(448.0f, 928.0f));
            return;
        }
    }
    for(unsigned int  i = 0; i < mGame->getterl().size(); i++){
        Vector2 temp;
        CollSide t = this->cc->GetMinOverlap(mGame->getterl()[i]->cc, temp);
        if(t != CollSide::None){
            water = false;
            this->SetPosition(Vector2(this->GetPosition().x, mGame->logv[i]->GetPosition().y));
            Vector2 ve = mGame->logv[i]->wm->GetPos()*mGame->logv[i]->wm->GetForwardSpeed();
            this->SetPosition(this->GetPosition() + ve*deltaTime);
            if(t == CollSide::Left){
                this->SetPosition(Vector2(this->GetPosition().x + 32, this->GetPosition().y));
            }else if(t == CollSide::Right){
                this->SetPosition(Vector2(this->GetPosition().x - 32, this->GetPosition().y));
            }
        }
        
    }
    if(water && this->GetPosition().y > 180.0f && this->GetPosition().y < 510.0f){
        DeadFrog* v = new DeadFrog(mGame);
        v->SetPosition(this->GetPosition());
        this->SetPosition(Vector2(448.0f, 928.0f));
    }
    if(this->cc->Intersect(mGame->goal->GetComponent<CollisionComponent>())){
        this->SetPosition(mGame->goal->GetPosition());
        this->SetState(ActorState::Paused);
        goal = true;
    }
    if(this->GetPosition().y <= 180.0f && !goal){
        DeadFrog* v = new DeadFrog(mGame);
        v->SetPosition(this->GetPosition());
        this->SetPosition(Vector2(448.0f, 928.0f));
    }
    if(this->GetPosition().x < 0.0f || this->GetPosition().x > 896.0f){
        DeadFrog* v = new DeadFrog(mGame);
        v->SetPosition(this->GetPosition());
        this->SetPosition(Vector2(448.0f, 928.0f));
    }
    
}
