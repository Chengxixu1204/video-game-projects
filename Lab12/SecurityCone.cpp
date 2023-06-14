//
//  SecurityCone.cpp
//  itp380labs
//
//  Created by Chengxi Xu on 4/12/22.
//

#include "SecurityCone.hpp"
#include "CollisionComponent.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "MoveComponent.h"
#include "Player.hpp"
#include "Checkpoint.hpp"

SecurityCone::SecurityCone(class Game* game, Actor* parent)
:Actor(game, parent)
{
    SetScale(3.0f);
    SetPosition(Vector3(30, 0, 0));
    mc = new MeshComponent(this, true);
    mc->SetMesh(mGame->GetRenderer()->GetMesh("Assets/Cone.gpmesh"));
    
}

void SecurityCone::OnUpdate(float deltaTime){
    
    Vector3 toplayer = mGame->pl->GetPosition() - GetWorldPosition();
    float angle = Math::Acos(Vector3::Dot(toplayer, GetWorldForward())/toplayer.Length() * GetWorldForward().Length());
    float dis = Vector3::Dot(GetWorldForward(), toplayer);
    if(angle >= -Math::Pi/6 && angle <= Math::Pi/6 && dis <= 300.0f){
        count += deltaTime;
    }else{
        count = 0.0f;
        
    }
    if(count > 2){
        mc->SetTextureIndex(2);
        die += deltaTime;
        if(die > 0.5f){
            mGame->Getpl()->SetState(ActorState::Paused);
        }
    }
    else if(count > 0){
        if(enteryellow){
           yellow = Mix_PlayChannel(Mix_GroupAvailable(1), mGame->GetSound("Assets/Sounds/SecurityDetected.wav"), 0);
            enteryellow = false;
        }
        mc->SetTextureIndex(1);
    }else if(count == 0){
        if(!enteryellow){
            Mix_HaltChannel(yellow);
            enteryellow = true;
        }
        mc->SetTextureIndex(0);
    }
}

