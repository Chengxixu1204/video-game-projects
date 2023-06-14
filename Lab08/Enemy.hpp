//
//  Enemy.hpp
//  Lab08
//
//  Created by Chengxi Xu on 3/20/22.
//

#ifndef Enemy_hpp
#define Enemy_hpp

#include <stdio.h>
#include "Actor.h"
#include "Game.h"

class MeshComponent;
class EnemyMove;
class Enemy: public Actor{
public:
    Enemy(class Game* game);
    EnemyMove* Ene_mov;
private:
    MeshComponent* Mesh_com;
};
#endif /* Enemy_hpp */
