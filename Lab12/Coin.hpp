//
//  Coin.hpp
//  Lab11
//
//  Created by Chengxi Xu on 4/9/22.
//

#ifndef Coin_hpp
#define Coin_hpp

#include <stdio.h>
#include "Actor.h"
#include "Game.h"

class MeshComponent;
class CollisionComponent;
class MoveComponent;
class Coin: public Actor{
public:
    Coin(class Game* game, Actor* parent);
    MeshComponent* mc;
    CollisionComponent* cc;
    MoveComponent* movc;
    void OnUpdate(float deltaTime) override;
};
#endif /* Coin_hpp */
