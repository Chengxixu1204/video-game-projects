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
    }else if(mCurrentState == MoveState::WallClimb){
        UpdateWallClimb(deltaTime);
    }else if(mCurrentState == MoveState::WallRun){
        UpdateWallRun(deltaTime);
    }
}

void PlayerMove::ProcessInput(const Uint8* keyState){
    
    int x, y;
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
    bool temp = false;
    for(size_t i = 0; i < mOwner->GetGame()->bvec.size(); i++){
        CollSide result = FixCollision(mOwner->GetComponent<CollisionComponent>(), mOwner->GetGame()->bvec[i]->GetComponent<CollisionComponent>());
        if(result == CollSide::Top){
            isonground = true;
        }else if(result != CollSide::Bottom && result != CollSide::Top){
            temp = CanWallClimb(result);
            if(temp){
                SDL_Log("%s", "Climb");
                mWallClimbTimer = 0.0f;
                ChangeState(MoveState::WallClimb);
                return;
            }
        }
    }
    if(!isonground){
        ChangeState(MoveState::Falling);
    }
}

bool PlayerMove::CanWallClimb(CollSide cs){
    bool result = false;
    Vector3 normal = GetNormalFromSide(cs);
    float ndotresult = Vector3::Dot(mOwner->GetForward(), normal);
    float vdotresult = Vector2::Dot(Vector2::Normalize(Vector2(mVelocity.x, mVelocity.y)), Vector2(normal.x, normal.y));
    float vlen = Vector2(mVelocity.x, mVelocity.y).Length();
    if(ndotresult < -0.9){
        if(vdotresult < -0.9 && vlen > 350){
            result = true;
        }
    }
    return result;
}

bool PlayerMove::CanWallRun(CollSide cs){
    bool result = false;
    Vector3 normal = GetNormalFromSide(cs);
    float ndotresult = Vector3::Dot(mOwner->GetForward(), normal);
    float vdotresult = Vector2::Dot(Vector2::Normalize(Vector2(mVelocity.x, mVelocity.y)), Vector2(mOwner->GetForward().x, mOwner->GetForward().y));
    float vlen = Vector2(mVelocity.x, mVelocity.y).Length();
    if(ndotresult < 0.6){
        if(vdotresult > 0 && vlen > 350){
            result = true;
            Runside = normal;
        }
    }
    return result;
}

void PlayerMove::UpdateWallClimb(float deltaTime){
    mWallClimbTimer += deltaTime;
    AddForce(mGravity);
    if(mWallClimbTimer <= 0.4f){
        AddForce(wallforce);
    }
    PhysicsUpdate(deltaTime);
    bool test = false;
    for(size_t i = 0; i < mOwner->GetGame()->bvec.size(); i++){
        CollSide result = FixCollision(mOwner->GetComponent<CollisionComponent>(), mOwner->GetGame()->bvec[i]->GetComponent<CollisionComponent>());
        if(result != CollSide::Bottom && result != CollSide::Top){
            test = true;
        }
    }
    if(!test || mVelocity.z <= 0){
        mVelocity.z = 0.0f;
        ChangeState(MoveState::Falling);
    }
    
}

void PlayerMove::UpdateWallRun(float deltaTime){
    AddForce(mGravity);
    if(mWallRunTimer <= 0.4f){
        AddForce(mWallRunForce);
    }
    PhysicsUpdate(deltaTime);
    for(size_t i = 0; i < mOwner->GetGame()->bvec.size(); i++){
        FixCollision(mOwner->GetComponent<CollisionComponent>(), mOwner->GetGame()->bvec[i]->GetComponent<CollisionComponent>());
    }
    if(mVelocity.z <= 0){
        mVelocity.z = 0.0f;
        ChangeState(MoveState::Falling);
    }
    mWallRunTimer += deltaTime;
}

void PlayerMove::ChangeState(MoveState updatestate){
    mCurrentState = updatestate;
}

void PlayerMove::UpdateJump(float deltaTime){
    AddForce(mGravity);
    PhysicsUpdate(deltaTime);
    bool temp = false;
    for(size_t i = 0; i < mOwner->GetGame()->bvec.size(); i++){
        CollSide result = FixCollision(mOwner->GetComponent<CollisionComponent>(), mOwner->GetGame()->bvec[i]->GetComponent<CollisionComponent>());
        if(result == CollSide::Bottom){
            mVelocity.z = 0;
        }else if(result != CollSide::Bottom && result != CollSide::Top){
            temp = CanWallClimb(result);
            if(temp){
                ChangeState(MoveState::WallClimb);
                mWallClimbTimer = 0.0f;
                return;
            }else{
                if(CanWallRun(result)){
                    SDL_Log("%s", "Run");
                    ChangeState(MoveState::WallRun);
                    mWallRunTimer = 0.0f;
                    return;
                }
            }
        }
    }
    if(mVelocity.z <= 0){
        ChangeState(MoveState::Falling);
    }
}

void PlayerMove::UpdateFalling(float deltaTime){
    
    AddForce(mGravity);
    PhysicsUpdate(deltaTime);
    for(size_t i = 0; i < mOwner->GetGame()->bvec.size(); i++){
        CollSide result = FixCollision(mOwner->GetComponent<CollisionComponent>(), mOwner->GetGame()->bvec[i]->GetComponent<CollisionComponent>());
        if(result == CollSide::Top){
            mVelocity.z = 0.0f;
            ChangeState(MoveState::OnGround);
        }
    }
}

CollSide PlayerMove::FixCollision(CollisionComponent* self, CollisionComponent* block){
    
    Vector3 offset;
    CollSide test = self->GetMinOverlap(block, offset);
    if(test != CollSide::None){
        Vector3 new_position = mOwner->GetPosition() + offset;
        mOwner->SetPosition(new_position);
        if(test == CollSide::Right){
            AddForce(700.0f*Vector3(0, 1, 0));
        }else if(test == CollSide::Left){
            AddForce(700.0f*Vector3(0, -1, 0));
        }else if(test == CollSide::Front){
            AddForce(700.0f*Vector3(1, 0, 0));
        }else if(test == CollSide::Back){
            AddForce(700.0f*Vector3(-1, 0, 0));
        }
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
    if(mCurrentState == MoveState::OnGround || mCurrentState == MoveState::WallClimb){
        if(Math::NearZero(mAcceleration.y)){
            temp.y *= mFriction;
        }
        if(Math::NearZero(mAcceleration.x)){
            temp.x *= mFriction;
        }
        
        if((mAcceleration.x < 0 && temp.x > 0) || (mAcceleration.x > 0 && temp.x < 0)){
            temp.x *= mFriction;
        }
        if((mAcceleration.y < 0 && temp.y > 0) || (mAcceleration.y > 0 && temp.y < 0)){
            temp.y *= mFriction;
        }
    }
    
    mVelocity.x = temp.x;
    mVelocity.y = temp.y;
    
    
}

Vector3 PlayerMove::GetNormalFromSide(CollSide s){
    if(s == CollSide::Right){
        return Vector3(0, 1, 0);
    }else if(s == CollSide::Left){
        return Vector3(0, -1, 0);
    }else if(s == CollSide::Front){
        return Vector3(1, 0 , 0);
    }else{
        return Vector3(-1, 0, 0);
    }
}

