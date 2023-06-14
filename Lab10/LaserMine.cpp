//
//  LaserMine.cpp
//  Lab10
//
//  Created by Chengxi Xu on 4/4/22.
//

#include "LaserMine.hpp"
#include "MeshComponent.h"
#include "Renderer.h"
#include "LaserComponent.hpp"

LaserMine::LaserMine(class Game* game)
:Actor(game)
{
    mc = new MeshComponent(this);
    mc->SetMesh(mGame->GetRenderer()->GetMesh("Assets/LaserMine.gpmesh"));
    lc = new LaserComponent(this);
}
