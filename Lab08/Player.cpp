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
#include "PlayerUI.h"
Player::Player(class Game* game)
:Actor(game)
{
    SetScale(0.75f);
    Mesh_com = new MeshComponent(this);
    Mesh_com->SetMesh(mGame->GetRenderer()->GetMesh("Assets/Kart.gpmesh"));
    Player_Mov = new PlayerMove(this);
    Cam_Com = new CameraComponent(this);
    Cam_Com->SnapToIdeal();
    Pl_ui = new PlayerUI(this);
};
