//
//  Ship.hpp
//  Lab02
//
//  Created by Chengxi Xu on 1/25/22.
//

#ifndef Ship_hpp
#define Ship_hpp
#include "Actor.h"
#include "Game.h"
#include <stdio.h>

class MoveComponent;
class SpriteComponent;

class Ship: public Actor{
public:
    Ship(class Game* game);
private:
    MoveComponent* mc;
    SpriteComponent* sc;
    void OnProcessInput(const Uint8* keyState) override;
    void OnUpdate(float deltaTime) override;
    float tracktime;
};

#endif /* Ship_hpp */
