//
//  Spawner.hpp
//  Lab04
//
//  Created by Chengxi Xu on 2/7/22.
//

#ifndef Spawner_hpp
#define Spawner_hpp

#include <stdio.h>
#include "Actor.h"
#include "Game.h"
class Spawner: public Actor{
public:
    Spawner(class Game* game);
    void OnUpdate(float deltaTime) override;
};
#endif /* Spawner_hpp */
