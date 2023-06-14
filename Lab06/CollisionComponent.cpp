#include "CollisionComponent.h"
#include "Actor.h"

CollisionComponent::CollisionComponent(class Actor* owner)
:Component(owner)
,mWidth(0.0f)
,mHeight(0.0f)
{
	
}

CollisionComponent::~CollisionComponent()
{
	
}

bool CollisionComponent::Intersect(const CollisionComponent* other)
{
	// TODO: Implement
    if(this->GetMax().x < other->GetMin().x){
        return false;
    }else if(other->GetMax().x < this->GetMin().x){
        return false;
    }else if(this->GetMax().y < other->GetMin().y){
        return false;
    }else if(other->GetMax().y < this->GetMin().y){
        return false;
    }else{
        return true;
    }
}

Vector2 CollisionComponent::GetMin() const
{
	// TODO: Implement
    return Vector2(mOwner->GetPosition().x-(mWidth*mOwner->GetScale())/2, mOwner->GetPosition().y-(mHeight*mOwner->GetScale()/2));
	//return Vector2::Zero;
}

Vector2 CollisionComponent::GetMax() const
{
	// TODO: Implement
    return Vector2(mOwner->GetPosition().x+(mWidth*mOwner->GetScale())/2, mOwner->GetPosition().y+(mHeight*mOwner->GetScale()/2));
	//return Vector2::Zero;
}

const Vector2& CollisionComponent::GetCenter() const
{
	return mOwner->GetPosition();
}

CollSide CollisionComponent::GetMinOverlap(
	const CollisionComponent* other, Vector2& offset)
{
	offset = Vector2::Zero;
    if(!this->Intersect(other)){
        return CollSide::None;
    }
    float diff1 = Math::Abs(this->GetMin().y - other->GetMax().y);
    float diff2 = Math::Abs(this->GetMax().y - other->GetMin().y);
    float diff3 = Math::Abs(this->GetMax().x - other->GetMin().x);
    float diff4 = Math::Abs(this->GetMin().x - other->GetMax().x);
    float result = Math::Min(Math::Min(diff1, diff2), Math::Min(diff3, diff4));
    if(result == diff1){
        offset.y = diff1;
        return CollSide::Bottom;
    }else if(result == diff2){
        offset.y = -diff2;
        return CollSide::Top;
    }else if(result == diff3){
        offset.x = -diff3;
        return CollSide::Left;
    }else{
        offset.x = diff4;
        return CollSide::Right;
    }
	
}
