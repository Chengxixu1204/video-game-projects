#include "CollisionComponent.h"
#include "Actor.h"


CollisionComponent::CollisionComponent(class Actor* owner)
:Component(owner)
,mWidth(0.0f)
,mHeight(0.0f)
,mDepth(0.0f)
{
	
}

CollisionComponent::~CollisionComponent()
{
	
}

bool CollisionComponent::Intersect(const CollisionComponent* other)
{
	Vector3 aMin = GetMin();
	Vector3 aMax = GetMax();
	Vector3 bMin = other->GetMin();
	Vector3 bMax = other->GetMax();

	bool no = aMax.x < bMin.x ||
		aMax.y < bMin.y ||
		aMax.z < bMin.z ||
		bMax.x < aMin.x ||
		bMax.y < aMin.y ||
		bMax.z < aMin.z;

	return !no;
}

Vector3 CollisionComponent::GetMin() const
{
	Vector3 v = mOwner->GetPosition();
	v.x -= mDepth * mOwner->GetScale() / 2.0f;
	v.y -= mWidth * mOwner->GetScale() / 2.0f;
	v.z -= mHeight * mOwner->GetScale() / 2.0f;
	return v;
}

Vector3 CollisionComponent::GetMax() const
{
	Vector3 v = mOwner->GetPosition();
	v.x += mDepth * mOwner->GetScale() / 2.0f;
	v.y += mWidth * mOwner->GetScale() / 2.0f;
	v.z += mHeight * mOwner->GetScale() / 2.0f;
	return v;
}

const Vector3& CollisionComponent::GetCenter() const
{
	return mOwner->GetPosition();
}

CollSide CollisionComponent::GetMinOverlap(
	const CollisionComponent* other, Vector3& offset)
{
	offset = Vector3::Zero;
	// TODO: Implement
    if(Intersect(other)){
        Vector3 maxThis = GetMax();
        Vector3 maxOther = other->GetMax();
        Vector3 minThis = GetMin();
        Vector3 minOther = other->GetMin();
        float otherMaxYdiff = abs(maxOther.y - minThis.y);
        float otherMinYdiff = abs(minOther.y - maxThis.y);
        float otherMaxXdiff = abs(maxOther.x - minThis.x);
        float otherMinXdiff = abs(minOther.x - maxThis.x);
        float otherMaxZdiff = abs(maxOther.z - minThis.z);
        float otherMinZdiff = abs(minOther.z - maxThis.z);
        float min = std::min({otherMaxYdiff,otherMinYdiff,otherMaxXdiff,
            otherMinXdiff,otherMaxZdiff,otherMinZdiff});
        
        if(min == otherMaxYdiff){
            offset.y= maxOther.y - minThis.y;
            return CollSide::Right;
        }else if(min == otherMaxZdiff){
            offset.z = maxOther.z - minThis.z;
            return CollSide::Top;
        }else if( min == otherMinZdiff){
            offset.z = minOther.z - maxThis.z;
            return CollSide::Bottom;
        }else if(min == otherMaxXdiff){
            offset.x = maxOther.x - minThis.x;
            return CollSide::Front;
        }else if(min == otherMinYdiff){
            offset.y = minOther.y - maxThis.y;
            return CollSide::Left;
        }else if(min == otherMinXdiff){
            offset.x = minOther.x - maxThis.x;
            return CollSide::Back;

        }

    }else{
        return CollSide::None;
    }
    return CollSide::None;
}
