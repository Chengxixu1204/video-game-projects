//
//  CameraComponent.hpp
//  Lab08
//
//  Created by Chengxi Xu on 3/20/22.
//

#ifndef CameraComponent_hpp
#define CameraComponent_hpp

#include <stdio.h>
#include "Component.h"
#include "Actor.h"
#include "Game.h"
class CameraComponent : public Component
{
public:
    CameraComponent(class Actor* owner);
    void Update(float deltaTime) override;
    float GetPitchSpeed(){ return pitchSpeed; }
    void SetPitchSpeed(float pitchspeed){ pitchSpeed = pitchspeed;}
private:
    Vector3 camera_pos;
    Vector3 camera_velocity;
    Vector3 eyepos = Vector3(0.0f, 0.0f, 0.0f);
    float pitchAngle = 0.0f;
    Vector3 cameraPos = Vector3(0,0,0);
    float pitchSpeed = 0.0f;
    Vector3 UpdateZCom(float deltaTime);
    float range = 3.0f;
    float checktime = 0.0f;
    float Angle = 0.0f;
    bool first = false;
};
#endif /* CameraComponent_hpp */
