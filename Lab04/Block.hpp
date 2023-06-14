//
//  Block.hpp
//  Lab04
//
//  Created by Chengxi Xu on 2/3/22.
//

#ifndef Block_hpp
#define Block_hpp

#include <stdio.h>
#include "Actor.h"
#include "Game.h"

class SpriteComponent;
class CollisionComponent;
class Block: public Actor{
public:
    Block(class Game* game, char type);
    ~Block();
    char t;
    SpriteComponent* sc;
    CollisionComponent* cc;
};
#endif /* Block_hpp */
