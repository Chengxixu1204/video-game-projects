//
//  Laser.hpp
//  Lab02
//
//  Created by Chengxi Xu on 1/25/22.
//

#ifndef Laser_hpp
#define Laser_hpp

#include <stdio.h>
#include "Actor.h"
#include "Game.h"
#include <stdio.h>
class MoveComponent;
class SpriteComponent;

class Laser: public Actor{
public:
    Laser(class Game* game);
private:
    MoveComponent* mc;
    SpriteComponent* sc;
    void OnUpdate(float deltaTime) override;
    float lifetime;
};

#endif /* Laser_hpp */
