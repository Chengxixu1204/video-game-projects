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
#include "CameraComponent.hpp"
#include "HUD.hpp"

Player::Player(class Game* game, Actor* parent)
:Actor(game, parent)
{
    pm = new PlayerMove(this);
    cc = new CollisionComponent(this);
    cc->SetSize(50, 175, 50);
    mCamera = new CameraComponent(this);
    h = new HUD(this);
};

void Player::requestspawn(){
    pm->getrespawn();
}
