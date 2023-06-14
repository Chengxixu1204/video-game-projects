//
//  Arrow.cpp
//  Lab11
//
//  Created by Chengxi Xu on 4/9/22.
//

#include "Arrow.hpp"
#include "CollisionComponent.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "MoveComponent.h"
#include "Player.hpp"
#include "Checkpoint.hpp"

Arrow::Arrow(class Game* game, Actor* parent)
:Actor(game, parent)
{
    mScale = 0.15f;
    mc = new MeshComponent(this);
    mc->SetMesh(mGame->GetRenderer()->GetMesh("Assets/Arrow.gpmesh"));
    
}

void Arrow::OnUpdate(float deltaTime){
    if(mGame->allcheck.size() != 0){
        Vector3 dis = mGame->allcheck.front()->GetPosition() - mGame->pl->GetPosition();
        dis.Normalize();
        Quaternion qt;
        if(Vector3::Dot(dis, Vector3::UnitX) == 1.0f ){
            qt = Quaternion::Identity;
        }else if(Vector3::Dot(dis, Vector3::UnitX) == -1.0f ){
            qt = Quaternion(Vector3::UnitZ, Math::Pi);
        }else{
            float angle = Math::Acos(Vector3::Dot(dis, Vector3::UnitX));
            Vector3 axis = Vector3::Cross(Vector3::UnitX, dis);
            axis.Normalize();
            qt = Quaternion(axis, angle);
            SetQuan(qt);
        }
    }else{
        SetQuan(Quaternion::Identity);
    }
    SetPosition(mGame->GetRenderer()->Unproject(Vector3(0.0f, 250.0f, 0.1f)));
}
