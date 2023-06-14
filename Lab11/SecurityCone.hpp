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
    float Getcountnum(){return count;}
private:
    float count = 0.0f;
    MeshComponent* mc;
    void OnUpdate(float deltaTime) override;
    float die = 0.0f;
};
#endif /* SecurityCone_hpp */
