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

SecurityCamera::SecurityCamera(class Game* game, Actor* parent)
:Actor(game, parent)
{
    mc = new MeshComponent(this);
    mc->SetMesh(mGame->GetRenderer()->GetMesh("Assets/Camera.gpmesh"));
    cone = new SecurityCone(mGame, this);
    SetQuan(startQ);
    mGame->AddCam(this);
}

void SecurityCamera::OnUpdate(float deltaTime){
    if(cone->count == 0){
        count += deltaTime;
        if(!dir){
            if(count < interpTime){
                Quaternion qt = Quaternion::Slerp(startQ, endQ, count/interpTime);
                SetQuan(qt);
                if(set){
                    rotate = Mix_PlayChannel(Mix_GroupAvailable(1), mGame->GetSound("Assets/Sounds/CameraMotor.wav"), 0);
                    set = false;
                    VoiceDis();
                }
                VoiceDis();
            }else{
                set = true;
                
                if(set2){
                    Mix_HaltChannel(rotate);
                    stoprotate = Mix_PlayChannel(Mix_GroupAvailable(1), mGame->GetSound("Assets/Sounds/CameraMotorStop.wav"), 0);
                    VoiceStopDis();
                    set2 = !Mix_Playing(stoprotate);
                }
                if(pauseTime > 0){
                    pauseTime -= deltaTime;
                }else{
                    count = 0;
                    dir = true;
                    pauseTime = pauseTime2;
                    set2 = true;
                }
            }
        }else{
            if(count < interpTime){
                Quaternion qt = Quaternion::Slerp(endQ, startQ, count/interpTime);
                SetQuan(qt);
                if(set){
                    rotate = Mix_PlayChannel(Mix_GroupAvailable(1), mGame->GetSound("Assets/Sounds/CameraMotor.wav"), 0);
                    set = false;
                    VoiceDis();
                }
                VoiceDis();
            }else{
                set = true;
                if(set2){
                    Mix_HaltChannel(rotate);
                    stoprotate = Mix_PlayChannel(Mix_GroupAvailable(1), mGame->GetSound("Assets/Sounds/CameraMotorStop.wav"), 0);
                    set2 = !Mix_Playing(stoprotate);
                    VoiceStopDis();
                }
                if(pauseTime > 0){
                    pauseTime -= deltaTime;
                }else{
                    count = 0;
                    dir = false;
                    pauseTime = pauseTime2;
                    set2 = true;
                }
            }
        }
    }else{
        Mix_HaltChannel(rotate);
    }
}

SecurityCamera::~SecurityCamera(){
    mGame->RemoveCam(this);
    if(rotate){
        Mix_HaltChannel(rotate);
    }
}

void SecurityCamera::VoiceDis(){
    float dis = Vector3::Distance(mGame->pl->GetPosition(), this->GetPosition());
    if(dis > 1500.0f){
        Mix_Volume(rotate, 0);
    }else if(dis < 1500.0f && dis > 500.0f){
        float volume = -0.128f * dis + 192.0f;
        Mix_Volume(rotate, volume);
    }else if(dis < 500.0f){
        Mix_Volume(rotate, 128);
    }
}

void SecurityCamera::VoiceStopDis(){
    float dis = Vector3::Distance(mGame->pl->GetPosition(), this->GetPosition());
    if(dis > 1500.0f){
        Mix_Volume(stoprotate, 0);
    }else if(dis < 1500.0f && dis > 500.0f){
        float volume = -0.128f * dis + 192.0f;
        Mix_Volume(stoprotate, volume);
    }else if(dis < 500.0f){
        Mix_Volume(stoprotate, 128);
    }
}
