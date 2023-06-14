//
//  Enemy.cpp
//  Lab08
//
//  Created by Chengxi Xu on 3/20/22.
//

#include "Enemy.hpp"
#include "MeshComponent.h"
#include "Renderer.h"
#include "CollisionComponent.h"
#include "PlayerMove.hpp"
#include "EnemyMove.hpp"

Enemy::Enemy(class Game* game)
:Actor(game)
{
    SetScale(0.75f);
    Mesh_com = new MeshComponent(this);
    Mesh_com->SetMesh(mGame->GetRenderer()->GetMesh("Assets/Kart.gpmesh"));
    Mesh_com->SetTextureIndex(6);
    Ene_mov = new EnemyMove(this);
    
};
