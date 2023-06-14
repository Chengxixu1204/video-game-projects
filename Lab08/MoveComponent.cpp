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
	// TODO: Implement in Part 2
    mOwner->SetRotation(mOwner->GetRotation()+deltaTime*mAngularSpeed);
    Vector3 velocity = mOwner->GetForward()*mForwardSpeed;
    mOwner->SetPosition(mOwner->GetPosition() + velocity*deltaTime);
//    mAngularSpeed = 0;
//    mForwardSpeed = 0;
    
}
