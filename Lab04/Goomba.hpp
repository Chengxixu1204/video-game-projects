//
//  Goomba.hpp
//  Lab04
//
//  Created by Chengxi Xu on 2/6/22.
//

#ifndef Goomba_hpp
#define Goomba_hpp

#include <stdio.h>
#include "Actor.h"
#include "Game.h"
class SpriteComponent;
class CollisionComponent;
class GoombaMove;
class AnimatedSprite;
class Goomba: public Actor{
public:
    Goomba(class Game* game);
    ~Goomba();
    //SpriteComponent* sc;
    CollisionComponent* cc;
    GoombaMove* gm;
    bool stomp;
    void OnUpdate(float deltaTime) override;
    float time;
    AnimatedSprite* as;
};
#endif /* Goomba_hpp */
