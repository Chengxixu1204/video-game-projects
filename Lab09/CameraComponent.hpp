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
    float hori_dis = 60.0f;
    float offset = 50.0f;
    float springcons = 256.0f;
    float dampcons = 0.0f;
    Vector3 eyepos = Vector3(0.0f, 0.0f, 0.0f);
    float pitchAngle = 0.0f;
    Vector3 cameraPos = Vector3(0,0,0);
    float pitchSpeed = 0.0f;
    float GetPitchSpeed(){ return pitchSpeed; }
    void SetPitchSpeed(float pitchspeed){ pitchSpeed = pitchspeed;}
};
#endif /* CameraComponent_hpp */
