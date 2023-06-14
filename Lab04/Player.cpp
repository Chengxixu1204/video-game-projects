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

Player::Player(class Game* game)
:Actor(game)
{
    cc = new CollisionComponent(this);
    pm = new PlayerMove(this);
    cc->SetSize(32.0f, 32.0f);
    as = new AnimatedSprite(this);
    std::vector<SDL_Texture*> idle{
        GetGame()->GetTexture("Assets/Mario/Idle.png"),
    };
    std::vector<SDL_Texture*> dead{
        GetGame()->GetTexture("Assets/Mario/Dead.png"),
    };
    std::vector<SDL_Texture*> jumpLeft{
        GetGame()->GetTexture("Assets/Mario/JumpLeft.png"),
    };
    std::vector<SDL_Texture*> jumpRight{
        GetGame()->GetTexture("Assets/Mario/JumpRight.png"),
    };
    std::vector<SDL_Texture*> runLeft{
        GetGame()->GetTexture("Assets/Mario/RunLeft0.png"),
        GetGame()->GetTexture("Assets/Mario/RunLeft1.png"),
        GetGame()->GetTexture("Assets/Mario/RunLeft2.png")
    };
    std::vector<SDL_Texture*> runRight{
        GetGame()->GetTexture("Assets/Mario/RunRight0.png"),
        GetGame()->GetTexture("Assets/Mario/RunRight1.png"),
        GetGame()->GetTexture("Assets/Mario/RunRight2.png")
    };
    as->AddAnimation("idle", idle);
    as->AddAnimation("jumpLeft", jumpLeft);
    as->AddAnimation("jumpRight", jumpRight);
    as->AddAnimation("runLeft", runLeft);
    as->AddAnimation("runRight", runRight);
    as->AddAnimation("dead", dead);
    
    as->SetAnimation("idle");
};
