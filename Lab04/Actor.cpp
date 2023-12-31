#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include <algorithm>

Actor::Actor(Game* game)
	:mGame(game)
	,mState(ActorState::Active)
	,mPosition(Vector2::Zero)
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
