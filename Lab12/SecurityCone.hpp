//
//  SecurityCone.hpp
//  itp380labs
//
//  Created by Chengxi Xu on 4/12/22.
//

#ifndef SecurityCone_hpp
#define SecurityCone_hpp

#include <stdio.h>
#include "Actor.h"
#include "Game.h"

class MeshComponent;
class SecurityCone: public Actor{
public:
    SecurityCone(class Game* game, Actor* parent);
    MeshComponent* mc;
    void OnUpdate(float deltaTime) override;
    float count = 0.0f;
    float die = 0.0f;
    int yellow;
    void UpdateSound();
    bool enteryellow = true;
};
#endif /* SecurityCone_hpp */
