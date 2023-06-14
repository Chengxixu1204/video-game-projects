//
//  Player.hpp
//  Lab01
//
//  Created by Chengxi Xu on 3/6/22.
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include "Actor.h"
#include "Game.h"

class MeshComponent;
class CollisionComponent;
class PlayerMove;
class HUD;
class Player: public Actor{
public:
    Player(class Game* game);
    MeshComponent* mc;
    CollisionComponent* cc;
    CollisionComponent* GetColli() {return cc;}
    PlayerMove* pm;
    int slevel;
    HUD* h;
    void Addslevel(int n) {slevel += n;}
};
#endif /* Player_hpp */
