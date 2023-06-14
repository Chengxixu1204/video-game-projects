//
//  Asteroid.hpp
//  Lab02
//
//  Created by Chengxi Xu on 1/25/22.
//

#ifndef Asteroid_hpp
#define Asteroid_hpp
#include "Actor.h"
#include "Game.h"
#include <stdio.h>
class MoveComponent;
class SpriteComponent;

class Asteroid: public Actor{
public:
    Asteroid(class Game* game);
    ~Asteroid();
private:
    MoveComponent* mc;
    SpriteComponent* sc;
    void OnUpdate(float deltaTime) override;
};

#endif /* Asteroid_hpp */
