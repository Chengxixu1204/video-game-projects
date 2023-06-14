//
//  SecurityCamera.cpp
//  Lab11
//
//  Created by Chengxi Xu on 4/12/22.
//

#include "SecurityCamera.hpp"
#include "CollisionComponent.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "MoveComponent.h"
#include "Player.hpp"
#include "Checkpoint.hpp"
#include "SecurityCone.hpp"
#include <algorithm>

SecurityCamera::SecurityCamera(class Game* game, Actor* parent)
:Actor(game, parent)
{
    mc = new MeshComponent(this);
    mc->SetMesh(mGame->GetRenderer()->GetMesh("Assets/Camera.gpmesh"));
    cone = new SecurityCone(mGame, this);
    SetQuan(startQ);
}

void SecurityCamera::OnUpdate(float deltaTime){
    if(cone->Getcountnum() == 0){
        count += deltaTime;
        Quaternion quan;
        quan = Quaternion::Slerp(startQ, endQ, count/interpTime);
        if(count < interpTime){
            SetQuan(quan);
        }else{
            if(pauseTime > 0){
                pauseTime -= deltaTime;
            }else{
                count = 0;
                std::swap(startQ, endQ);
                pauseTime = pauseTime2;
            }
        }
    }
}
