//
//  Soldier.cpp
//  Lab01
//
//  Created by Chengxi Xu on 2/27/22.
//

#include "Soldier.hpp"
#include "SpriteComponent.h"
#include "CollisionComponent.h"
#include "AnimatedSprite.h"
#include "SoldierAI.h"
#include "PathNode.h"
#include "EnemyComponent.hpp"
#include "Effect.hpp"
#define UNUSED(expr) do { (void)(expr); } while (0)
Soldier::Soldier(class Game* game, PathNode* start, PathNode* end)
:Actor(game)
{
    cc = new CollisionComponent(this);
    cc->SetSize(32.0f, 32.0f);
    as = new AnimatedSprite(this);
    as->LoadAnimations("Assets/Soldier");
    as->SetAnimation("WalkDown");
    as->SetAnimFPS(5.0f);
    sa = new SoldierAI(this);
    sa->Setup(start, end);
    ec = new EnemyComponent(this);
    ec->Sethit(2);
    ec->SetDam([this]{
        sa->stunned();
        Effect* e = new Effect(mGame, this->GetPosition(), "Hit", "Assets/Sounds/EnemyHit.wav");
        UNUSED(e);
    });
    ec->SetDea([this]{
        Effect* e = new Effect(mGame, this->GetPosition(), "Death", "Assets/Sounds/EnemyDie.wav");
        UNUSED(e);
    });
};
