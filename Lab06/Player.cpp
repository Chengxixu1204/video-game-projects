//
//  Player.cpp
//  Lab04
//
//  Created by Chengxi Xu on 2/3/22.
//

#include "Player.hpp"

#include "SpriteComponent.h"
#include "CollisionComponent.h"
#include "PlayerMove.hpp"
#include "AnimatedSprite.h"

const float PLAYERSIZE = 20.0f;

Player::Player(class Game* game)
:Actor(game)
{
    cc = new CollisionComponent(this);
    pm = new PlayerMove(this);
    cc->SetSize(PLAYERSIZE, PLAYERSIZE);
    as = new AnimatedSprite(this);
    as->LoadAnimations("Assets/Link");
    as->SetAnimation("StandDown");
    
};
