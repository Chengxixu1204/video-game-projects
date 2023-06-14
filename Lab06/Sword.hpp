//
//  Sword.hpp
//  Lab06
//
//  Created by Chengxi Xu on 3/3/22.
//

#ifndef Sword_hpp
#define Sword_hpp

#include <stdio.h>
#include "Actor.h"
#include "Game.h"

class CollisionComponent;
class Sword: public Actor{
public:
    Sword(class Game* game);
    CollisionComponent* cc;
};
#endif /* Sword_hpp */
