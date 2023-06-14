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
        Falling,
        WallClimb,
        WallRun
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
    void UpdateWallClimb(float deltaTime);
    void UpdateWallRun(float deltaTime);
    CollSide FixCollision(class CollisionComponent* self, class CollisionComponent* block);
    bool CanWallClimb(CollSide cs);
    bool CanWallRun(CollSide cs);
    Vector3 Runside = Vector3(0.0f, 0.0f, 0.0f);
    MoveState mCurrentState;
private:
    float mWallClimbTimer;
    Vector3 wallforce = Vector3(0.0f, 0.0f, 1800.0f);
    Vector3 mWallRunForce = Vector3(0.0f, 0.0f, 1200.0f);
    float mWallRunTimer = 0.0f;
    Vector3 mVelocity;
    Vector3 mAcceleration;
    Vector3 mPendingForces;
    float mMass = 1.0f;
    Vector3 mGravity = Vector3(0,0,-980.0f);
    Vector3 mJumpForce = Vector3(0,0,35000.0f);
    bool mSpacePressed = false;
    float mSpeedLimit = 400.0f;
    float mSpeedMagnitude = 700.0f;
    float mFriction = 0.9f;
    Vector3 GetNormalFromSide(CollSide s);
    
};
#endif /* PlayerMove_hpp */
