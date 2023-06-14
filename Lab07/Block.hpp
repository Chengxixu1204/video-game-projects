//
//  Block.hpp
//  Lab07
//
//  Created by Chengxi Xu on 3/8/22.
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
    Block(class Game* game, size_t t);
    ~Block();
    MeshComponent* mc;
    CollisionComponent* cc;
    void OnUpdate(float deltaTime) override;
    bool explode;
    size_t texture;
};
#endif /* Block_hpp */
