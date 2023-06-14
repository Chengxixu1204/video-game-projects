//
//  WrappingMove.cpp
//  Lab03
//
//  Created by Chengxi Xu on 1/31/22.
//

#include "WrappingMove.hpp"

WrappingMove::WrappingMove(class Actor* owner)
:MoveComponent(owner)
{

};

void WrappingMove::Update(float deltaTime){
    Vector2 velocity = position*mForwardSpeed;
    mOwner->SetPosition(mOwner->GetPosition() + velocity*deltaTime);
    float oy = mOwner->GetPosition().y;
    if(mOwner->GetPosition().x > WINDOW_WIDTH*2){
        mOwner->SetPosition(Vector2(0, oy));
    }else if(mOwner->GetPosition().x < 0.0f){
        mOwner->SetPosition(Vector2(WINDOW_WIDTH*2, oy));
    }
}
