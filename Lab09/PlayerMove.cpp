//
//  PlayerMove.cpp
//  Lab07
//
//  Created by Chengxi Xu on 3/6/22.
//


#include "PlayerMove.hpp"
#include <cmath>
#include <time.h>
#include <string>
#include "CameraComponent.hpp"
#include "Block.hpp"



PlayerMove::PlayerMove(class Actor* owner)
:MoveComponent(owner)
{
    ChangeState(MoveState::Falling);
}

void PlayerMove::Update(float deltaTime){
    
    if(mCurrentState == MoveState::OnGround){
        UpdateOnGround(deltaTime);
    }else if(mCurrentState == MoveState::Jump){
        UpdateJump(deltaTime);
    }else if(mCurrentState == MoveState::Falling){
        UpdateFalling(deltaTime);
    }
}

void PlayerMove::ProcessInput(const Uint8* keyState){
    
    int x = 0;
    int y = 0;
    keyState = SDL_GetKeyboardState(nullptr);
    if(keyState[SDL_SCANCODE_W]){
        AddForce(mOwner->GetForward()* mSpeedMagnitude);
    }
    if(keyState[SDL_SCANCODE_S]){
        AddForce(mOwner->GetForward() * -mSpeedMagnitude);
    }
    
    if(keyState[SDL_SCANCODE_A]){
        AddForce(mOwner->GetRight() * -mSpeedMagnitude);
    }
    if(keyState[SDL_SCANCODE_D]){
        AddForce(mOwner->GetRight() * mSpeedMagnitude);
    }
    
    if(keyState[SDL_SCANCODE_SPACE] ){
        if(!mSpacePressed){
            if(mCurrentState == MoveState::OnGround){
                AddForce(mJumpForce);
                ChangeState(MoveState::Jump);
            }
        }
    }
    
    SDL_GetRelativeMouseState(&x, &y);
    float angular = x/500.0f * Math::Pi * 10.0f;
    SetAngularSpeed(angular);
    float pitch_speed = y/500.0f * Math::Pi * 10.0f;
    mOwner->GetComponent<CameraComponent>()->SetPitchSpeed(pitch_speed);
    
    mSpacePressed = keyState[SDL_SCANCODE_SPACE];
    
}


void PlayerMove::UpdateOnGround(float deltaTime){
    PhysicsUpdate(deltaTime);
    bool isonground = false;
    CollisionComponent* mc = mOwner->GetComponent<CollisionComponent>();
    for(size_t i = 0; i < mOwner->GetGame()->bvec.size(); i++){
        CollSide result = FixCollision(mc, mOwner->GetGame()->bvec[i]->GetComponent<CollisionComponent>());
        if(result == CollSide::Top){
            isonground = true;
        }
    }
    if(!isonground){
        ChangeState(MoveState::Falling);
    }
}

void PlayerMove::ChangeState(MoveState updatestate){
    mCurrentState = updatestate;
}

void PlayerMove::UpdateJump(float deltaTime){
    AddForce(mGravity);
    PhysicsUpdate(deltaTime);
    CollisionComponent* mc = mOwner->GetComponent<CollisionComponent>();
    for(size_t i = 0; i < mOwner->GetGame()->bvec.size(); i++){
        CollSide result = FixCollision(mc, mOwner->GetGame()->bvec[i]->GetComponent<CollisionComponent>());
        if(result == CollSide::Bottom){
            mVelocity.z = 0;
        }
    }
    if(mVelocity.z <= 0){
        ChangeState(MoveState::Falling);
    }
}

void PlayerMove::UpdateFalling(float deltaTime){
    
    AddForce(mGravity);
    PhysicsUpdate(deltaTime);
    CollisionComponent* mc = mOwner->GetComponent<CollisionComponent>();
    for(size_t i = 0; i < mOwner->GetGame()->bvec.size(); i++){
        CollSide result = FixCollision(mc, mOwner->GetGame()->bvec[i]->GetComponent<CollisionComponent>());
        if(result == CollSide::Top){
            mVelocity.z = 0.0f;
            ChangeState(MoveState::OnGround);
        }
    }
}

CollSide PlayerMove::FixCollision(CollisionComponent* self, CollisionComponent* block){
    
    Vector3 offset = Vector3(0, 0, 0);
    CollSide test = self->GetMinOverlap(block, offset);
    if(test != CollSide::None){
        Vector3 new_position = mOwner->GetPosition() + offset;
        mOwner->SetPosition(new_position);
    }
    return test;
}

void PlayerMove::PhysicsUpdate(float deltaTime){
    
    mAcceleration = mPendingForces * (1.0f/mMass);
    mVelocity += mAcceleration * deltaTime;
    FixXYVelocity();
    float uodatero = mOwner->GetRotation()+ mAngularSpeed * deltaTime ;
    mOwner->SetRotation(uodatero);
    
    Vector3 p = mOwner->GetPosition() + mVelocity * deltaTime;
    mOwner->SetPosition(p);
    
    mPendingForces = Vector3::Zero;
    
}

void PlayerMove::AddForce(const Vector3& force){
    
    mPendingForces += force;
}

void PlayerMove::FixXYVelocity(){
    
    Vector2 temp = Vector2(mVelocity.x, mVelocity.y);
    if(temp.Length() > mSpeedLimit){
        temp.Normalize();
        temp *= mSpeedLimit;
    }
    if(mCurrentState == MoveState::OnGround){
        if(Math::NearZero(mAcceleration.y)){
            temp.y *= mFriction;
        }
        if(Math::NearZero(mAcceleration.x)){
            temp.x *= mFriction;
        }
        
        if((mAcceleration.x < 0 && temp.x > 0) ||
           (mAcceleration.x > 0 && temp.x < 0)){
            temp.x *= mFriction;
        }
        if((mAcceleration.y < 0 && temp.y > 0) ||
           (mAcceleration.y > 0 && temp.y < 0)){
            temp.y *= mFriction;
        }
    }
    
    mVelocity.x = temp.x;
    mVelocity.y = temp.y;
    
    
}
