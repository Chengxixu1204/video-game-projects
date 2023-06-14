//
//  Collider.hpp
//  Lab06
//
//  Created by Chengxi Xu on 2/23/22.
//

#ifndef Collider_hpp
#define Collider_hpp

#include <stdio.h>
#include "Actor.h"
#include "Game.h"

class CollisionComponent;
class Collider: public Actor{
public:
    Collider(class Game* game, float width, float height);
    CollisionComponent* cc;
   
};
#endif /* Collider_hpp */
