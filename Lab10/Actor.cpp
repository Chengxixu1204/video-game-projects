#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include <algorithm>

Actor::Actor(Game* game)
	:mGame(game)
	,mState(ActorState::Active)
	,mPosition(Vector3::Zero)
	,mScale(1.0f)
	,mRotation(0.0f)
{
	// TODO
    mGame->AddActor(this);
}

Actor::~Actor()
{
	// TODO
    mGame->RemoveActor(this);
    for(unsigned int i = 0; i < mComponents.size(); i++){
        delete(mComponents[i]);
    }
}

void Actor::Update(float deltaTime)
{
	// TODO
    if(mState == ActorState::Active){
        for(unsigned int i = 0; i < mComponents.size(); i++){
            mComponents[i]->Update(deltaTime);
        }
    }
    OnUpdate(deltaTime);
    Matrix4 sca = Matrix4::CreateScale(mScale);
    Matrix4 rot = Matrix4::CreateRotationZ(mRotation);
    Matrix4 trans = Matrix4::CreateTranslation(mPosition);
    Matrix4 rotx = Matrix4::CreateRotationX(RollAngle);
    Matrix4 quanx = Matrix4::CreateFromQuaternion(qt);
    mWorldTransform = sca*rot*rotx*quanx*trans;
    
    
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
