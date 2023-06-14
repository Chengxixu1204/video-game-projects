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

    
    float updaterotation = mOwner->GetRotation()+ mAngularSpeed * deltaTime;
    mOwner->SetRotation(updaterotation);
    Vector3 fordir = mOwner->GetForward();
    Vector3 currposition = mOwner->GetPosition();
    Vector3 velocity = Vector3(fordir.x* mForwardSpeed,fordir.y* mForwardSpeed,mForwardSpeed * fordir.z);
    Vector3 change = Vector3(velocity.x * deltaTime,
    velocity.y*deltaTime,velocity.y * deltaTime);
    Vector3 new_position = Vector3(change.x + currposition.x,change.y+currposition.y,change.z + currposition.z);
    mOwner->SetPosition(new_position);
    
    
    currposition = mOwner->GetPosition();
    fordir = mOwner->GetRight();
    velocity = fordir * mStrafeSpeed;
    new_position = currposition + velocity*deltaTime;
    mOwner->SetPosition(new_position);
}

