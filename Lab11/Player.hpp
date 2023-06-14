//
//  Player.hpp
//  Lab01
//
//  Created by Chengxi Xu on 3/6/22.
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include "Actor.h"
#include "Game.h"

class PlayerMove;
class CollisionComponent;
class CameraComponent;
class Player: public Actor{
public:
    Player(class Game* game, Actor* parent);
    PlayerMove* pm;
    CollisionComponent* cc;
    CameraComponent* mCamera;
    Vector3 respawn;
    void SetRespawnPos(Vector3 r){respawn = r;}
    void requestspawn();
};
#endif /* Player_hpp */
