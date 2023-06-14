//
//  Bullet.hpp
//  Lab07
//
//  Created by Chengxi Xu on 3/9/22.
//

#ifndef Bullet_hpp
#define Bullet_hpp

#include <stdio.h>
#include "Actor.h"
#include "Game.h"
#include <vector>

class MeshComponent;
class CollisionComponent;
class MoveComponent;
class Block;
class Bullet: public Actor{
public:
    Bullet(class Game* game);
    MeshComponent* mc;
    CollisionComponent* cc;
    MoveComponent* moc;
    void OnUpdate(float deltaTime) override;
    float time = 0.0f;
    void CheckExplode(Block* bl);
    std::vector<Block*> bv;
};
#endif /* Bullet_hpp */
