//
//  Bullet.cpp
//  Lab07
//
//  Created by Chengxi Xu on 3/9/22.
//

#include "Bullet.hpp"
#include "MeshComponent.h"
#include "CollisionComponent.h"
#include "Renderer.h"
#include "Player.hpp"
#include "MoveComponent.h"
#include "Block.hpp"
Bullet::Bullet(class Game* game)
:Actor(game)
{
    SetScale(5.0f);
    mc = new MeshComponent(this);
    mc->SetMesh(mGame->GetRenderer()->GetMesh("Assets/Laser.gpmesh"));
    cc = new CollisionComponent(this);
    cc->SetSize(10.0f, 10.0f, 10.0f);
    moc = new MoveComponent(this);
    moc->SetForwardSpeed(900.0f);
    
    
};

void Bullet::OnUpdate(float deltaTime){
    time += deltaTime;
    for(size_t i = 0; i < mGame->bvec.size(); i++){
        if(cc->Intersect(mGame->bvec[i]->GetComponent<CollisionComponent>())){
            SetState(ActorState::Destroy);
            if(mGame->bvec[i]->texture == 4){
                Mix_Chunk *sample;
                sample = GetGame()->GetSound("Assets/Sounds/BlockExplode.wav");
                Mix_PlayChannel(-1, sample, 0);
                CheckExplode(mGame->bvec[i]);
            }
        }
    }
    if(time >= 1.0f){
        SetState(ActorState::Destroy);
    }
    
}

void Bullet::CheckExplode(Block *bl){
    for(size_t i = 0; i < mGame->bvec.size(); i++){
        if(Vector3::Distance(bl->GetPosition(), mGame->bvec[i]->GetPosition()) <= 50){
            if(mGame->bvec[i]->texture == 4 && std::count(bv.begin(), bv.end(), mGame->bvec[i]) == 0){
                bv.push_back(mGame->bvec[i]);
                CheckExplode(mGame->bvec[i]);
            }
            mGame->bvec[i]->SetState(ActorState::Destroy);
        }
    }
    bl->SetState(ActorState::Destroy);
    return;
}
