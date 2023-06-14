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
    ~SecurityCamera();
    MeshComponent* mc;
    SecurityCone* cone;
    Quaternion startQ;
    Quaternion endQ;
    float interpTime;
    float pauseTime;
    float pauseTime2;
    void OnUpdate(float deltaTime) override;
    float count = 0.0f;
    bool dir = false;
    void Stop(float deltaTime);
    int rotate;
    int stoprotate;
    void UpdateSound();
    bool set = true;
    bool set2 = true;
    void VoiceDis();
    void VoiceStopDis();
};
#endif /* SecurityCamera_hpp */
