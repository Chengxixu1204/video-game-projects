//
//  CameraComponent.cpp
//  Lab08
//
//  Created by Chengxi Xu on 3/20/22.
//

#include "CameraComponent.hpp"
#include "Renderer.h"
const float ZCOM = 70.0f;

CameraComponent::CameraComponent(Actor* owner)
:Component(owner)
{
    
}

void CameraComponent::Update(float deltaTime){
    Vector3 idealpos = CalPos();
    Vector3 displace = Eye_pos - idealpos;
    Damp_cons = 2.0f*Math::Sqrt(Spring_cons);
    Vector3 springacc = (-Spring_cons*displace) - Damp_cons*Camera_velocity;
    Camera_velocity += springacc*deltaTime;
    Eye_pos += Camera_velocity*deltaTime;
    Vector3 target = mOwner->GetPosition() + mOwner->GetForward()*Off_set;
    Matrix4 camera = Matrix4::CreateLookAt(Eye_pos, target, Vector3::UnitZ);
    mOwner->GetGame()->GetRenderer()->SetViewMatrix(camera);
    
}

Vector3 CameraComponent::CalPos(){
    Vector3 Temp_pos = mOwner->GetPosition() - mOwner->GetForward()*Hori_dis;
    Temp_pos.z = ZCOM;
    return Temp_pos;
}

void CameraComponent::SnapToIdeal(){
    Eye_pos = CalPos();
    Vector3 target = mOwner->GetPosition() + mOwner->GetForward()*Off_set;
    Matrix4 camera = Matrix4::CreateLookAt(Eye_pos, target, Vector3::UnitZ);
    mOwner->GetGame()->GetRenderer()->SetViewMatrix(camera);
}
