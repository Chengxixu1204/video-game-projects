//
//  PlayerMove.cpp
//  Lab04
//
//  Created by Chengxi Xu on 2/3/22.
//

#include "PlayerMove.hpp"
#include "CollisionComponent.h"
#include "Block.hpp"
#include "Goomba.hpp"
#include "Player.hpp"
#include "AnimatedSprite.h"

PlayerMove::PlayerMove(class Actor* owner)
:MoveComponent(owner)
{
    mYSpeed = 0.0f;
    mInAir = false;
    mSpacePressed = false;
    nmap.insert({SDL_SCANCODE_UP, false});
    origin = Vector2(0, mOwner->GetPosition().x - 300.0f);
    isdead = false;
};

void PlayerMove::Update(float deltaTime){
    Vector2 new_position(mOwner->GetPosition().x + mForwardSpeed*deltaTime, mOwner->GetPosition().y + mYSpeed*deltaTime);
    mOwner->SetPosition(new_position);
    bool ishittingblock = false;
    Vector2 temp;
    Vector2 pos_temp;
    for(unsigned int i = 0; i < mOwner->GetGame()->bvec.size(); i++){
        pos_temp = mOwner->GetPosition();
        CollSide t = mOwner->GetComponent<CollisionComponent>()->GetMinOverlap(mOwner->GetGame()->bvec[i]->cc, temp);
        if(t == CollSide::None){
            continue;
        }else if((t == CollSide::Top) && (mYSpeed > 0.0f)){
            mInAir = false;
            mYSpeed = 0.0f;
        }else if((t == CollSide::Bottom) && (mYSpeed < 0.0f)){
            mYSpeed = 0.0f;
            Mix_Chunk *sample;
            sample = mOwner->GetGame()->GetSound("Assets/Sounds/Bump.wav");
            Mix_PlayChannel(-1, sample, 0);
        }else{
        }
        ishittingblock = true;
        mOwner->SetPosition(pos_temp + temp);
        
    }
    for(unsigned int i = 0; i < mOwner->GetGame()->gvec.size(); i++){
        pos_temp = mOwner->GetPosition();
        CollSide t = mOwner->GetComponent<CollisionComponent>()->GetMinOverlap(mOwner->GetGame()->gvec[i]->cc, temp);
        if(t == CollSide::Top || (((t == CollSide::Left) || (t == CollSide::Right)) && mInAir)){
            mOwner->GetGame()->gvec[i]->stomp = true;
            mYSpeed = -350.0f;
            mInAir = true;
        }else if(t == CollSide::None){
            continue;
        }else{
            isdead = true;
            break;
        }
        if(mOwner->GetGame()->gvec[i]->stomp == true){
            Mix_Chunk *sample;
            sample = mOwner->GetGame()->GetSound("Assets/Sounds/Stomp.wav");
            Mix_PlayChannel(-1, sample, 0);
        }
    }
    if(mOwner->GetPosition().y > 448.0f){
        mInAir = false;
        mOwner->GetComponent<AnimatedSprite>()->SetAnimation("dead");
        mOwner->SetState(ActorState::Paused);
        Mix_HaltChannel(mOwner->GetGame()->music);
        Mix_Chunk *sample;
        sample = mOwner->GetGame()->GetSound("Assets/Sounds/Dead.wav");
        Mix_PlayChannel(-1, sample, 0);
      }
    if(mOwner->GetPosition().x > 6368.0f){
        Mix_HaltChannel(mOwner->GetGame()->music);
        Mix_Chunk *sample;
        sample = mOwner->GetGame()->GetSound("Assets/Sounds/StageClear.wav");
        Mix_PlayChannel(-1, sample, 0);
        mOwner->SetState(ActorState::Paused);
    }
    if(!ishittingblock){
        mInAir = true;
    }
    mOwner->GetGame()->camera.y = 0;
    if((mOwner->GetPosition().x - 300.0f) > origin.x && mOwner->GetPosition().x > origin.x){
        if((mOwner->GetPosition().x - 300.0f) < 0.0f){
            mOwner->GetGame()->camera.x = 0.0f;
        }else{
            mOwner->GetGame()->camera.x = mOwner->GetPosition().x - 300.0f;
        }
         origin = Vector2(mOwner->GetGame()->camera);
    }
    if(mOwner->GetPosition().x <= mOwner->GetGame()->camera.x){
        mOwner->SetPosition(Vector2(mOwner->GetGame()->camera.x, mOwner->GetPosition().y));
    }
    mYSpeed += 2000.0f*deltaTime;
    AnimationPlayer();
}

void PlayerMove::ProcessInput(const Uint8 *keyState){
    if(keyState[SDL_SCANCODE_LEFT]){
        SetForwardSpeed(-300.0f);
    }else if(keyState[SDL_SCANCODE_RIGHT]){
        SetForwardSpeed(300.0f);
    }else{
        SetForwardSpeed(0.0f);
    }
    if((keyState[SDL_SCANCODE_UP]) && !(nmap[SDL_SCANCODE_UP]) && !mInAir){
        Mix_Chunk *sample;
        sample = mOwner->GetGame()->GetSound("Assets/Sounds/Jump.wav");
        Mix_PlayChannel(-1, sample, 0);
        mYSpeed = -700.0f;
        mInAir = true;
    }
    nmap[SDL_SCANCODE_UP] = keyState[SDL_SCANCODE_UP];
}

void PlayerMove::AnimationPlayer(){
//    if(isdead){
//
//    }
    if(!mInAir && !isdead){
        if(mForwardSpeed > 0.0f){
            mOwner->GetComponent<AnimatedSprite>()->SetAnimation("runRight");
        }else if(mForwardSpeed < 0.0f){
            mOwner->GetComponent<AnimatedSprite>()->SetAnimation("runLeft");
        }else{
            mOwner->GetComponent<AnimatedSprite>()->SetAnimation("idle");
        }
    }else if (mInAir && !isdead){
        if(mForwardSpeed > 0.0f){
            mOwner->GetComponent<AnimatedSprite>()->SetAnimation("jumpRight");
        }else if(mForwardSpeed < 0.0f){
            mOwner->GetComponent<AnimatedSprite>()->SetAnimation("jumpLeft");
        }else{
            if(mOwner->GetComponent<AnimatedSprite>()->GetAnimName() == "runRight" || mOwner->GetComponent<AnimatedSprite>()->GetAnimName() == "jumpRight" ||
               mOwner->GetComponent<AnimatedSprite>()->GetAnimName() == "idle"){
                mOwner->GetComponent<AnimatedSprite>()->SetAnimation("jumpRight");
            }else{
                mOwner->GetComponent<AnimatedSprite>()->SetAnimation("jumpLeft");
            }
        }
    }else{
        mOwner->GetComponent<AnimatedSprite>()->SetAnimation("dead");
        mOwner->SetState(ActorState::Paused);
        Mix_Chunk *sample;
        sample = mOwner->GetGame()->GetSound("Assets/Sounds/Dead.wav");
        Mix_PlayChannel(-1, sample, 0);
    }
    
    
}
