//
//  LaserMine.hpp
//  Lab10
//
//  Created by Chengxi Xu on 4/4/22.
//

#ifndef LaserMine_hpp
#define LaserMine_hpp

#include <stdio.h>
#include "Actor.h"
#include "Game.h"

class MeshComponent;
class LaserComponent;
class LaserMine: public Actor{
public:
    LaserMine(class Game* game);
    MeshComponent* mc;
    LaserComponent* lc;
};
#endif /* LaserMine_hpp */
