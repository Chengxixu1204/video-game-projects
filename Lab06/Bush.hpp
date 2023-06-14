//
//  Bush.hpp
//  Lab06
//
//  Created by Chengxi Xu on 2/27/22.
//

#ifndef Bush_hpp
#define Bush_hpp

#include <stdio.h>
#include "Actor.h"
#include "Game.h"

class CollisionComponent;
class SpriteComponent;
class EnemyComponent;
class Bush: public Actor{
public:
    Bush(class Game* game);
    CollisionComponent* cc;
    SpriteComponent* sp;
    EnemyComponent* ec;
};
#endif /* Bush_hpp */
