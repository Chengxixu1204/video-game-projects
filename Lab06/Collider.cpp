//
//  Collider.cpp
//  Lab06
//
//  Created by Chengxi Xu on 2/23/22.
//

#include "Collider.hpp"
#include "SpriteComponent.h"
#include "CollisionComponent.h"
#include "AnimatedSprite.h"

Collider::Collider(class Game* game, float width, float height)
:Actor(game)
{
    cc = new CollisionComponent(this);
    cc->SetSize(width, height);
};
