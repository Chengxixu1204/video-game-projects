//
//  CameraComponent.cpp
//  Lab08
//
//  Created by Chengxi Xu on 3/20/22.
//

#include "CameraComponent.hpp"
#include "Renderer.h"
#include "Player.hpp"
#include "PlayerMove.hpp"
CameraComponent::CameraComponent(Actor* owner)
:Component(owner)
{
    
}

void CameraComponent::Update(float deltaTime){
    Matrix4 p = Matrix4::CreateRotationY(pitchAngle);
    Matrix4 y = Matrix4::CreateRotationZ(mOwner->GetRotation());
    Matrix4 result = p * y;
    Vector3 transformed = Vector3::Transform(Vector3(1,0,0), result);
    Vector3 target = mOwner->GetPosition() + 10*transformed;
    Vector3 zcom = UpdateZCom(deltaTime);
    Matrix4 camera = Matrix4::CreateLookAt(mOwner->GetPosition(), target, zcom);
    mOwner->GetGame()->GetRenderer()->SetViewMatrix(camera);
    
    pitchAngle += pitchSpeed * deltaTime;
    if(pitchAngle >= Math::Pi/4){
        pitchAngle = Math::Pi/4;
    }else if(pitchAngle <= -Math::Pi/4){
        pitchAngle = -Math::Pi/4;
    }
    
}

Vector3 CameraComponent::UpdateZCom(float deltaTime){
    
    if(mOwner->GetGame()->Getpl()->GetComponent<PlayerMove>()->mCurrentState == PlayerMove::MoveState::WallRun){
        checktime += deltaTime;
        first = false;
        SDL_Log("%s", "checkrun");
        if(mOwner->GetGame()->Getpl()->GetComponent<PlayerMove>()->Runside.x == 1){
            Angle = Math::Lerp(0, Math::PiOver2, checktime/range);
            Angle = -Angle;
            Matrix4 roll = Matrix4::CreateRotationY(Angle);
            
            Vector3 result = Vector3::Transform(Vector3::UnitZ, roll);
            return result;
        }else if(mOwner->GetGame()->Getpl()->GetComponent<PlayerMove>()->Runside.x == -1){
            Angle = Math::Lerp(0, Math::PiOver2, checktime/range);
            
            Matrix4 roll = Matrix4::CreateRotationY(Angle);
            Vector3 result = Vector3::Transform(Vector3::UnitZ, roll);
            return result;
        }else if(mOwner->GetGame()->Getpl()->GetComponent<PlayerMove>()->Runside.y == 1){
            Angle = Math::Lerp(0, Math::PiOver2, checktime/range);
            Angle = -Angle;
            Matrix4 roll = Matrix4::CreateRotationX(Angle);
            Vector3 result = Vector3::Transform(Vector3::UnitZ, roll);
            return result;
        }else if(mOwner->GetGame()->Getpl()->GetComponent<PlayerMove>()->Runside.y == -1){
            Angle = Math::Lerp(0, Math::PiOver2, checktime/range);
            
            Matrix4 roll = Matrix4::CreateRotationX(Angle);
            Vector3 result = Vector3::Transform(Vector3::UnitZ, roll);
            return result;
        }
    }else{
        checktime = 0.0f;
        return Vector3::UnitZ;
    }
    return Vector3::UnitZ;
}



