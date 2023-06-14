//
//  DeadFrog.hpp
//  Lab03
//
//  Created by Chengxi Xu on 2/1/22.
//

#ifndef DeadFrog_hpp
#define DeadFrog_hpp
#include "Actor.h"
#include "Game.h"
#include <stdio.h>

class SpriteComponent;
class DeadFrog: public Actor{
public:
    DeadFrog(class Game* game);
    SpriteComponent* sc;
    void OnUpdate(float deltaTime) override;
    float lifetime;
};
#endif /* DeadFrog_hpp */
