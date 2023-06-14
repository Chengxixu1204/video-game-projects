//
//  Soldier.hpp
//  Lab01
//
//  Created by Chengxi Xu on 2/27/22.
//

#ifndef Soldier_hpp
#define Soldier_hpp

#include <stdio.h>
#include "Actor.h"
#include "Game.h"

class CollisionComponent;
class AnimatedSprite;
class PathNode;
class SoldierAI;
class EnemyComponent;
class Soldier: public Actor{
public:
    Soldier(class Game* game, PathNode* start, PathNode* end);
    CollisionComponent* cc;
    AnimatedSprite* as;
private:
    SoldierAI* sa;
    EnemyComponent* ec;
   
};
#endif /* Soldier_hpp */
