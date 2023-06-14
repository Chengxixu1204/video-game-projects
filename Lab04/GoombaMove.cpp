//
//  GoombaMove.cpp
//  Lab04
//
//  Created by Chengxi Xu on 2/7/22.
//

#include "GoombaMove.hpp"
#include "CollisionComponent.h"
#include "Block.hpp"
#include "Goomba.hpp"
#include "Player.hpp"


GoombaMove::GoombaMove(class Actor* owner)
:MoveComponent(owner)
{
    mYSpeed = 0.0f;
    SetForwardSpeed(-100.0f);
    move = true;
};

void GoombaMove::Update(float deltaTime){
    if(move){
        Vector2 new_position(mOwner->GetPosition().x + mForwardSpeed*deltaTime, mOwner->GetPosition().y + mYSpeed*deltaTime);
        mOwner->SetPosition(new_position);
        Vector2 temp;
        float sign = 0.0f;
        if(GetForwardSpeed() < 0.0f){
            sign = 1.0f;
        }else if(GetForwardSpeed() > 0.0f){
            sign = -1.0f;
        }
        for(unsigned int i = 0; i < mOwner->GetGame()->bvec.size(); i ++){
                CollSide t = mOwner->GetComponent<CollisionComponent>()->GetMinOverlap(mOwner->GetGame()->bvec[i]->cc, temp);
                if(t == CollSide::Right || t == CollSide::Left){
                    float diff = mOwner->GetPosition().y - mOwner->GetGame()->bvec[i]->GetPosition().y;
                    if(Math::NearZero(diff, 0.6f)){
                        SetForwardSpeed(100.0f * sign);
                        mOwner->SetPosition(mOwner->GetPosition() + temp);
                    }
                
                }
                if(t == CollSide::Top && (mYSpeed > 0.0f)){
                    mYSpeed = 0.0f;
                    mOwner->SetPosition(mOwner->GetPosition() + temp);
                }
                
            }
            for(unsigned int i = 0; i < mOwner->GetGame()->gvec.size(); i ++){
                CollSide t = mOwner->GetComponent<CollisionComponent>()->GetMinOverlap(mOwner->GetGame()->gvec[i]->cc, temp);
                if(t == CollSide::Right || t == CollSide::Left){
                        SetForwardSpeed(100.0f * sign);
                        mOwner->SetPosition(mOwner->GetPosition() + temp);
                
                }
                if(t == CollSide::Top && (mYSpeed > 0.0f)){
                    mYSpeed = 0.0f;
                    mOwner->SetPosition(mOwner->GetPosition() + temp);
                }
            }
    }
    if(mOwner->GetPosition().y > 448.0f){
      mOwner->SetState(ActorState::Destroy);
    }
    mYSpeed += 2000.0f*deltaTime;
}
