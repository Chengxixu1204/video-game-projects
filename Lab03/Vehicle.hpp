//
//  Vehicle.hpp
//  Lab03
//
//  Created by Chengxi Xu on 1/27/22.
//

#ifndef Vehicle_hpp
#define Vehicle_hpp

#include <stdio.h>
#include "Actor.h"
#include "Game.h"
#include "WrappingMove.hpp"
#include "MoveComponent.h"
#include "CollisionComponent.h"

class SpriteComponent;
const int BSIZE = 64.0f;
class Vehicle: public Actor{
public:
    Vehicle(class Game* game, int linenum, std::string type);
    ~Vehicle();
    int line;
    std::string t;
    SpriteComponent* sc;
    WrappingMove* wm;
    CollisionComponent* cc;
    void OnUpdate(float deltaTime) override;
};

#endif /* Vehicle_hpp */
