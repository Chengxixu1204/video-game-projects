//
//  EnemyComponent.cpp
//  Lab06
//
//  Created by Chengxi Xu on 3/2/22.
//

#include "EnemyComponent.hpp"
#include "CollisionComponent.h"

const float TIME = 0.25f;

EnemyComponent::EnemyComponent(class Actor* owner)
:Component(owner)
{
    mOwner->GetGame()->AddEnemy(this);
    cc = mOwner->GetComponent<CollisionComponent>();
}
EnemyComponent:: ~EnemyComponent(){
    mOwner->GetGame()->RemoveEnemy(this);
}

void EnemyComponent::Update(float deltaTime){
    time += deltaTime;
}

void EnemyComponent::TakeDamage(){
    if(time > TIME){
        hitpoint -= 1;
        if(OnDamage){
            OnDamage();
        }
        time = 0.0f;
    }
    if(hitpoint <= 0){
        mOwner->SetState(ActorState::Destroy);
        if(OnDeath){
            OnDeath();
        }
        
    }
    
}
