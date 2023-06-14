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

const float DIS = 60.0f;
const float OFFSET = 50.0f;
const float SPRING = 256.0f;


class CameraComponent : public Component
{
public:
    CameraComponent(class Actor* owner);
    void Update(float deltaTime) override;
    void SnapToIdeal();
private:
    float Hori_dis = DIS;
    float Off_set = OFFSET;
    float Spring_cons = SPRING;
    float Damp_cons;
    Vector3 Camera_pos;
    Vector3 Camera_velocity;
    Vector3 CalPos();
    Vector3 Eye_pos = Vector3(0.0f, 0.0f, 0.0f);
};
#endif /* CameraComponent_hpp */
