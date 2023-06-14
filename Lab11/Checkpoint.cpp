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
        if(cc->Intersect(mGame->Getpl()->cc)){
            mGame->Getpl()->SetRespawnPos(this->GetPosition());
            if(mLevelString != ""){
                mGame->setmlevel(mLevelString);
            }
            SetState(ActorState::Destroy);
            mGame->getallcheckpoint().pop();
            if(mGame->getallcheckpoint().size() != 0){
                mGame->getallcheckpoint().front()->setactive(true);
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
