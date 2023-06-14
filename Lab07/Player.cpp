//
//  Player.cpp
//  Lab01
//
//  Created by Chengxi Xu on 3/6/22.
//

#include "Player.hpp"
#include "MeshComponent.h"
#include "Renderer.h"
#include "CollisionComponent.h"
#include "PlayerMove.hpp"
#include "HUD.h"
Player::Player(class Game* game)
:Actor(game)
{
    SetScale(2.0f);
    mc = new MeshComponent(this);
    mc->SetMesh(mGame->GetRenderer()->GetMesh("Assets/Arwing.gpmesh"));
    cc = new CollisionComponent(this);
    cc->SetSize(40.0f, 25.0f, 15.0f);
    pm = new PlayerMove(this);
    slevel = 3;
    h = new HUD(this);
    
};
