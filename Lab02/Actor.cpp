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

    mGame->AddActor(this);
}

Actor::~Actor()
{
    //delte components of actor and delete it
    mGame->RemoveActor(this);
    for(unsigned int i = 0; i < mComponents.size(); i++){
        delete(mComponents[i]);
    }
}

void Actor::Update(float deltaTime)
{
    //update actor with time
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
    //process actor with key state
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
    //add component to actor
	mComponents.emplace_back(c);
	std::sort(mComponents.begin(), mComponents.end(), [](Component* a, Component* b) {
		return a->GetUpdateOrder() < b->GetUpdateOrder();
	});
}
