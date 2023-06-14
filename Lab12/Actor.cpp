#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include <algorithm>

Actor::Actor(Game* game, Actor* parent)
	:mGame(game)
	,mState(ActorState::Active)
	,mPosition(Vector3::Zero)
	,mScale(1.0f)
	,mRotation(0.0f)
{
	// TODO
    mParent = parent;
    if(mParent == nullptr){
        mGame->AddActor(this);
    }else{
        mParent->AddChild(this);
    }
    
}

Actor::~Actor()
{
	// TODO
    while(mChildren.size() != 0){
        delete mChildren.back();
    }
    if(mParent == nullptr){
       mGame->RemoveActor(this);
    }else{
        mParent->RemoveChild(this);
    }
    
    for(unsigned int i = 0; i < mComponents.size(); i++){
        delete(mComponents[i]);
    }
}

void Actor::Update(float deltaTime)
{
	// TODO
    CalcWorldTransform();
    if(mState == ActorState::Active){
        for(unsigned int i = 0; i < mComponents.size(); i++){
            mComponents[i]->Update(deltaTime);
        }
    }
    OnUpdate(deltaTime);
    CalcWorldTransform();
    for(size_t i = 0; i < mChildren.size(); i++){
        mChildren[i]->Update(deltaTime);
    }
    
    
}

void Actor::OnUpdate(float deltaTime)
{
}

void Actor::ProcessInput(const Uint8* keyState)
{
	// TODO
    if(mState == ActorState::Active){
        for(unsigned int i = 0; i < mComponents.size(); i++){
            mComponents[i]->ProcessInput(keyState);
        }
    }
    OnProcessInput(keyState);
    
}

void Actor::OnProcessInput(const Uint8* keyState)
{
}

void Actor::AddComponent(Component* c)
{
	mComponents.emplace_back(c);
	std::sort(mComponents.begin(), mComponents.end(), [](Component* a, Component* b) {
		return a->GetUpdateOrder() < b->GetUpdateOrder();
	});
}

Vector3 Actor::GetQuatForward(){
    return Vector3::Normalize(Vector3::Transform(Vector3::UnitX, qt));
}

void Actor::CalcWorldTransform(){
    Matrix4 sca = Matrix4::CreateScale(mScale);
    Matrix4 rot = Matrix4::CreateRotationZ(mRotation);
    Matrix4 trans = Matrix4::CreateTranslation(mPosition);
    Matrix4 rotx = Matrix4::CreateRotationX(RollAngle);
    Matrix4 quanx = Matrix4::CreateFromQuaternion(qt);
    mWorldTransform = sca*rot*rotx*quanx*trans;
    if(mParent != nullptr){
        if(mInheritScale){
            mWorldTransform *= mParent->mWorldTransform;
        }else{
            mWorldTransform *= mParent->GetWorldRotTrans();
        }
    }
}

Matrix4 Actor::GetWorldRotTrans(){
    Matrix4 rot = Matrix4::CreateRotationZ(mRotation);
    Matrix4 trans = Matrix4::CreateTranslation(mPosition);
    Matrix4 rotx = Matrix4::CreateRotationX(RollAngle);
    Matrix4 quanx = Matrix4::CreateFromQuaternion(qt);
    Matrix4 result = rot*rotx*quanx*trans;
    if(mParent != nullptr){
        result *= mParent->GetWorldRotTrans();
    }
    return result;
}

Vector3 Actor::GetWorldForward(){
    return mWorldTransform.GetXAxis();
}

Vector3 Actor::GetWorldPosition(){
    return mWorldTransform.GetTranslation();
}

void Actor::AddChild(Actor *child){
    mChildren.push_back(child);
}

void Actor::RemoveChild(Actor *child){
    std::vector<Actor*>::iterator position = std::find(mChildren.begin(), mChildren.end(), child);
    if (position != mChildren.end())
        mChildren.erase(position);
}
