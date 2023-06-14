//
//  Player.hpp
//  Lab04
//
//  Created by Chengxi Xu on 2/3/22.
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include "Actor.h"
#include "Game.h"

class CollisionComponent;
class PlayerMove;
class AnimatedSprite;
class Player: public Actor{
public:
    Player(class Game* game);
    char t;
    CollisionComponent* cc;
    PlayerMove* pm;
    AnimatedSprite* as;
   
};
#endif /* Player_hpp */
