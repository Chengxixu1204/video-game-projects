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
    //update the velocity of component
    mOwner->SetRotation(mOwner->GetRotation()+deltaTime*mAngularSpeed);
    Vector2 velocity = mOwner->GetForward()*mForwardSpeed;
    mOwner->SetPosition(mOwner->GetPosition() + velocity*deltaTime);

}
