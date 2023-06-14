#include "MoveComponent.h"
#include "Actor.h"

MoveComponent::MoveComponent(class Actor* owner)
:Component(owner, 50)
,mAngularSpeed(0.0f)
,mForwardSpeed(0.0f)
{
	
}

void MoveComponent::Update(float deltaTime)
{

    mOwner->SetRotation(mOwner->GetRotation()+deltaTime*mAngularSpeed);
    Vector2 velocity = mOwner->GetForward()*mForwardSpeed;
    mOwner->SetPosition(mOwner->GetPosition() + velocity*deltaTime);
//    mAngularSpeed = 0;
//    mForwardSpeed = 0;
    
}
