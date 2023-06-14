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

const float ANGLE_RANGE = Math::Pi/6;
const float DIS_RANGE = 300.0f;
const float RED_THRESHOLD = 2.0f;
const float DIE_THRESHOLD = 0.5f;
const float YELLOW_THRESHOLD = 0;


SecurityCone::SecurityCone(class Game* game, Actor* parent)
:Actor(game, parent)
{
    SetScale(3.0f);
    SetPosition(Vector3(30, 0, 0));
    mc = new MeshComponent(this, true);
    mc->SetMesh(mGame->GetRenderer()->GetMesh("Assets/Cone.gpmesh"));
    
}

void SecurityCone::OnUpdate(float deltaTime){
    
    Vector3 toplayer = mGame->Getpl()->GetPosition() - GetWorldPosition();
    float angle = Math::Acos(Vector3::Dot(toplayer, GetWorldForward())/toplayer.Length() * GetWorldForward().Length());
    float dis = Vector3::Dot(GetWorldForward(), toplayer);
    if(angle >= -ANGLE_RANGE && angle <= ANGLE_RANGE && dis <= DIS_RANGE){
        count += deltaTime;
    }else{
        count = 0.0f;
    }
    if(count > RED_THRESHOLD){
        mc->SetTextureIndex(2);
        die += deltaTime;
        if(die > DIE_THRESHOLD){
            mGame->Getpl()->requestspawn();
        }
    }
    else if(count > YELLOW_THRESHOLD){
        mc->SetTextureIndex(1);
    }else if(count == YELLOW_THRESHOLD){
        mc->SetTextureIndex(0);
    }
}
