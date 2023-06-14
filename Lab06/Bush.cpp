//
//  Bush.cpp
//  Lab06
//
//  Created by Chengxi Xu on 2/27/22.
//

#include "Bush.hpp"
#include "SpriteComponent.h"
#include "CollisionComponent.h"
#include "AnimatedSprite.h"
#include "EnemyComponent.hpp"
#include "PathFinder.h"
#include "Effect.hpp"
#define UNUSED(expr) do { (void)(expr); } while (0)
const float BUSHSIZE = 32.0f;

Bush::Bush(class Game* game)
:Actor(game)
{
    cc = new CollisionComponent(this);
    cc->SetSize(BUSHSIZE, BUSHSIZE);
    sp = new SpriteComponent(this);
    sp->SetTexture(mGame->GetTexture("Assets/Bush.png"));
    ec = new EnemyComponent(this);
    ec->Sethit(1);
    ec->SetDea([this]{
        mGame->Getpf()->SetIsBlocked(static_cast<size_t>(GetPosition().y/32.0f), static_cast<size_t>(GetPosition().x/32), false);
        Effect* e = new Effect(mGame, this->GetPosition(), "BushDeath", "Assets/Sounds/BushDie.wav");
        UNUSED(e);
    });
};
