//
//  Checkpoint.cpp
//  Lab11
//
//  Created by Chengxi Xu on 4/9/22.
//

#include "Checkpoint.hpp"
#include "CollisionComponent.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "MoveComponent.h"
#include "Player.hpp"
#include "HUD.hpp"

Checkpoint::Checkpoint(class Game* game, Actor* parent)
:Actor(game, parent)
{
    mc = new MeshComponent(this);
    cc = new CollisionComponent(this);
    mc->SetMesh(mGame->GetRenderer()->GetMesh("Assets/Checkpoint.gpmesh"));
    cc->SetSize(25.0f, 25.0f, 25.0f);
    
}

void Checkpoint::OnUpdate(float deltaTime){
    
    if(isactive){
        Vector3 temp;
        if(cc->GetMinOverlap(mGame->pl->cc, temp) != CollSide::None){
            start = true;
            Mix_PlayChannel(-1, mGame->GetSound("Assets/Sounds/Checkpoint.wav"), 0);
            mGame->pl->SetRespawnPos(this->GetPosition());
            if(mLevelString != ""){
                mGame->setmlevel(mLevelString);
            }
            SetState(ActorState::Destroy);
            mGame->pl->h->SetCheckText(text);
            mGame->allcheck.pop();
            if(mGame->allcheck.size() != 0){
                mGame->allcheck.front()->setactive(true);
            }
        }
    }
    
}

void Checkpoint::setactive(bool b){
    isactive = b;
    if(isactive){
        mc->SetTextureIndex(0);
    }else{
        mc->SetTextureIndex(1);
    }
}
