//
//  Arrow.hpp
//  Lab11
//
//  Created by Chengxi Xu on 4/9/22.
//

#ifndef Arrow_hpp
#define Arrow_hpp

#include <stdio.h>
#include "Actor.h"
#include "Game.h"

class MeshComponent;
class Arrow: public Actor{
public:
    Arrow(class Game* game, Actor* parent);
private:
    MeshComponent* mc;
    void OnUpdate(float deltaTime) override;
};
#endif /* Arrow_hpp */
