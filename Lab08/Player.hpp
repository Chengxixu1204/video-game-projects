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

class MeshComponent;
class PlayerMove;
class CameraComponent;
class PlayerUI;
class Player: public Actor{
public:
    Player(class Game* game);
    PlayerMove* Player_Mov;
    PlayerUI* Pl_ui;
private:
    MeshComponent* Mesh_com;
    CameraComponent* Cam_Com;
    
};
#endif /* Player_hpp */
