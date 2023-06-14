//
//  PlayerMove.hpp
//  Lab07
//
//  Created by Chengxi Xu on 3/6/22.
//
#ifndef PlayerMove_hpp
#define PlayerMove_hpp

#include <stdio.h>
#include "Actor.h"
#include "Game.h"
#include "MoveComponent.h"
#include <map>
#include <vector>
#include "CollisionComponent.h"



class PlayerMove: public MoveComponent
{
public:
    enum MoveState {
        OnGround,
        Jump,
        Falling
    };
    PlayerMove(class Actor* owner);
    void Update(float deltaTime);
    void ProcessInput(const Uint8* keyState);
    void ChangeState(MoveState updatestate);
    void PhysicsUpdate(float deltaTime);
    void AddForce(const Vector3& force);
    void FixXYVelocity();
    void UpdateOnGround(float deltaTime);
    void UpdateJump(float deltaTime);
    void UpdateFalling(float deltaTime);
    CollSide FixCollision(class CollisionComponent* self,
                          class CollisionComponent* block);
private:
    MoveState mCurrentState = MoveState::Falling;
    Vector3 mVelocity = Vector3(0, 0, 0);
    Vector3 mAcceleration = Vector3(0, 0, 0);;
    Vector3 mPendingForces = Vector3(0, 0, 0);;
    float mMass = 1.0f;
    Vector3 mGravity = Vector3(0.0f, 0.0f, -980.0f);
    Vector3 mJumpForce = Vector3(0.0f, 0.0f ,35000.0f);
    bool mSpacePressed = false;
    float mSpeedLimit = 400.0f;
    float mSpeedMagnitude = 700.0f;
    float mFriction = 0.9f;
    
};
#endif /* PlayerMove_hpp */
