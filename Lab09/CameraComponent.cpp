//
//  CameraComponent.cpp
//  Lab08
//
//  Created by Chengxi Xu on 3/20/22.
//

#include "CameraComponent.hpp"
#include "Renderer.h"
CameraComponent::CameraComponent(Actor* owner)
:Component(owner)
{
    
}

void CameraComponent::Update(float deltaTime){
    Matrix4 p = Matrix4:: CreateRotationY(pitchAngle);
    Matrix4 y = Matrix4::CreateRotationZ(mOwner->GetRotation());
    Matrix4 result = p * y;
    Vector3 transformed = Vector3::Transform(Vector3(1,0,0), result);
    Vector3 target = mOwner->GetPosition() + 10*transformed;
    Matrix4 camera = Matrix4::CreateLookAt(mOwner->GetPosition(), target, Vector3::UnitZ);
    mOwner->GetGame()->GetRenderer()->SetViewMatrix(camera);
    
    pitchAngle += pitchSpeed * deltaTime;
    if(pitchAngle >= Math::Pi/4){
        pitchAngle = Math::Pi/4;
    }else if(pitchAngle <= -Math::Pi/4){
        pitchAngle = -Math::Pi/4;
    }
    
}



