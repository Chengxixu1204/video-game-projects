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
class MoveComponent;
class Block: public Actor{
public:
    Block(class Game* game, Actor* parent);
    ~Block();
    MeshComponent* mc;
    CollisionComponent* cc;
    MoveComponent* movc;
    bool ismirror = false;
    bool isrotate = false;
    void Setmirror(bool b){ismirror = b;}
    bool Getmirror(){return ismirror;}
    void Setrotate(bool b){isrotate = b;}
    bool Getrotate(){return isrotate;}
    
    void OnUpdate(float deltaTime) override;
};
#endif /* Block_hpp */
