//
//  Sword.cpp
//  Lab06
//
//  Created by Chengxi Xu on 3/3/22.
//

#include "Sword.hpp"
#include "CollisionComponent.h"

const float SWORDSIZE = 28.0f;
Sword::Sword(class Game* game)
:Actor(game)
{
    cc = new CollisionComponent(this);
    cc->SetSize(SWORDSIZE, SWORDSIZE);
};

