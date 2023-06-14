//
//  SecurityCamera.hpp
//  Lab11
//
//  Created by Chengxi Xu on 4/12/22.
//

#ifndef SecurityCamera_hpp
#define SecurityCamera_hpp

#include <stdio.h>
#include "Actor.h"
#include "Game.h"

class MeshComponent;
class SecurityCone;
class SecurityCamera: public Actor{
public:
    SecurityCamera(class Game* game, Actor* parent);
    void SetinterpTime(float in){interpTime = in;}
    void SetpauseTime(float pa){pauseTime = pa;}
    void SetpauseTime2(float pa){pauseTime2 = pa;}
    void SetstartQ(Quaternion q){startQ = q;}
    void SetendQ(Quaternion q){endQ = q;}
private:
    float interpTime;
    float pauseTime;
    float pauseTime2;
    Quaternion startQ;
    Quaternion endQ;
    MeshComponent* mc;
    SecurityCone* cone;
    void OnUpdate(float deltaTime) override;
    float count = 0.0f;
    bool direction = false;
    void Stop(float deltaTime);
};
#endif /* SecurityCamera_hpp */
