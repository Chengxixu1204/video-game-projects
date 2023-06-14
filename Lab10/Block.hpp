//
//  Block.hpp
//  Lab09
//
//  Created by Chengxi Xu on 3/24/22.
//

#ifndef Block_hpp
#define Block_hpp

#include <stdio.h>
#include "Actor.h"
#include "Game.h"

class MeshComponent;
class CollisionComponent;
class Block: public Actor{
public:
    Block(class Game* game);
    ~Block();
    MeshComponent* mc;
    CollisionComponent* cc;
    bool ismirror = false;
    void Setmirror(bool b){ismirror = b;}
    bool Getmirror(){return ismirror;}
};
#endif /* Block_hpp */
