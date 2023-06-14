//
//  PlayerMove.cpp
//  Lab04
//
//  Created by Chengxi Xu on 2/3/22.
//

#include "PlayerMove.hpp"
#include "CollisionComponent.h"
#include "Player.hpp"
#include "AnimatedSprite.h"
#include "Collider.hpp"
#include "EnemyComponent.hpp"
#include "Sword.hpp"

const float SPEED = 150.0f;
const float TIMELIMIT = 0.25f;
const float SWORDWID = 20.0f;
const float SWORDHEI = 32.0f;
const float SWORDWID2 = 28.0f;
const float SWORDHEI2 = 40.0f;
const float OFFSETWID = 256.0f;
const float OFFSETHEI = 224.0f;


PlayerMove::PlayerMove(class Actor* owner)
:MoveComponent(owner)
{
    nmap.insert({SDL_SCANCODE_UP, false});
    nmap.insert({SDL_SCANCODE_SPACE, false});
    origin = Vector2(0, mOwner->GetPosition().x - 300.0f);
    sd = new Sword(mOwner->GetGame());
};

void PlayerMove::Update(float deltaTime){
    mForwardSpeed = SPEED;
    //check current status of the player
    if(checkif_move && !checkif_attack){
       mOwner->SetPosition(mOwner->GetPosition() + mForwardSpeed*Dir*deltaTime);
    }else if(!checkif_move && !checkif_attack){
        UpdateAni(mType);
    }else if(!checkif_move && checkif_attack && timestamp <= TIMELIMIT){
        timestamp += deltaTime;
    }else{
        checkif_attack = false;
        timestamp = 0.0f;
    }
    //check collision status
    CheckColli();
    
    
}

void PlayerMove::ProcessInput(const Uint8 *keyState){
    keyState = SDL_GetKeyboardState(nullptr);
    if(keyState[SDL_SCANCODE_UP] && !checkif_attack){
        Dir = Vector2(0.0f, -1.0f);
        mType = UP;
        checkif_move = true;
    }else if(keyState[SDL_SCANCODE_DOWN] && !checkif_attack){
        Dir = Vector2(0.0f, 1.0f);
        mType = DOWN;
        checkif_move = true;
    }else if(keyState[SDL_SCANCODE_RIGHT] && !checkif_attack){
        Dir = Vector2(1.0f, 0.0f);
        mType = RIGHT;
        checkif_move = true;
    }else if(keyState[SDL_SCANCODE_LEFT] && !checkif_attack){
        Dir = Vector2(-1.0f, 0.0f);
        mType = LEFT;
        checkif_move = true;
    }else{
        Dir = Vector2(0.0f, 0.0f);
        checkif_move = false;
    }
    if(keyState[SDL_SCANCODE_SPACE] && !nmap[SDL_SCANCODE_SPACE]){
        checkif_attack = true;
        checkif_move = false;
        //UpdateSD();
        if(timestamp <= 0.25){
            UpdateSD();
            Mix_Chunk *sample;
            sample = mOwner->GetGame()->GetSound("Assets/Sounds/SwordSlash.wav");
            Mix_PlayChannel(-1, sample, 0);
            mOwner->GetComponent<AnimatedSprite>()->ResetAnimTimer();
        }
        
    }
    nmap[SDL_SCANCODE_SPACE] = keyState[SDL_SCANCODE_SPACE];
    UpdateAni(mType);
    
    
}

void PlayerMove::UpdateSD(){
    if(mType == UP){
        sd->SetPosition(mOwner->GetPosition() + Vector2(0.0f, -SWORDHEI2));
        sd->cc->SetSize(SWORDWID, SWORDWID2);
    }else if(mType == DOWN){
        sd->SetPosition(mOwner->GetPosition() + Vector2(0.0f, SWORDHEI2));
        sd->cc->SetSize(SWORDWID, SWORDWID2);
    }else if(mType == RIGHT){
        sd->SetPosition(mOwner->GetPosition() + Vector2(SWORDHEI, 0.0f));
        sd->cc->SetSize(SWORDWID2, SWORDWID);
    }else{
        sd->SetPosition(mOwner->GetPosition() + Vector2(-SWORDHEI, 0.0f));
        sd->cc->SetSize(SWORDWID2, SWORDWID);
    }
}

void PlayerMove::UpdateAni(Type n){
    std::string temp;
    if(!checkif_move && !checkif_attack){
        temp = "Stand";
    }else if(!checkif_move && checkif_attack){
        temp = "Attack";
    }else if(checkif_move){
        temp = "Walk";
    }
    if(n == UP){
       mOwner->GetComponent<AnimatedSprite>()->SetAnimation(temp + up);
    }else if(n == DOWN){
       mOwner->GetComponent<AnimatedSprite>()->SetAnimation(temp + down);
    }else if(n == LEFT){
       mOwner->GetComponent<AnimatedSprite>()->SetAnimation(temp + left);
    }else if(n == RIGHT){
        mOwner->GetComponent<AnimatedSprite>()->SetAnimation(temp + right);
    }
    
    
}

void PlayerMove::CheckColli(){
    if(checkif_attack){
        for(size_t i = 0; i < mOwner->GetGame()->gettere().size(); i++){
            Vector2 temp;
            CollSide t = sd->cc->GetMinOverlap(mOwner->GetGame()->gettere()[i]->cc, temp);
            if(t != CollSide::None){
                mOwner->GetGame()->gettere()[i]->TakeDamage();
            }
        }
    }
    CollisionComponent* tempc = mOwner->GetComponent<CollisionComponent>();
    for(size_t i = 0; i < mOwner->GetGame()->gettere().size(); i++){
        Vector2 temp;
        CollSide t = tempc->GetMinOverlap(mOwner->GetGame()->gettere()[i]->cc, temp);
        if(t != CollSide::None){
            mOwner->SetPosition(mOwner->GetPosition() + temp);
            mForwardSpeed = 0.0f;
            checkif_move = false;
        }
    }
    for(size_t i = 0; i < mOwner->GetGame()->getterc().size(); i++){
        Vector2 temp;
        CollSide t = tempc->GetMinOverlap(mOwner->GetGame()->getterc()[i]->cc, temp);
        if(t != CollSide::None){
            mOwner->SetPosition(mOwner->GetPosition() + temp);
            mForwardSpeed = 0.0f;
            checkif_move = false;
        }
    }
    Vector2 offset(-OFFSETWID, -OFFSETHEI);
    mOwner->GetGame()->camera = mOwner->GetPosition() + offset;
}

