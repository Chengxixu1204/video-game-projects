//
//  Checkpoint.hpp
//  Lab11
//
//  Created by Chengxi Xu on 4/9/22.
//

#ifndef Checkpoint_hpp
#define Checkpoint_hpp

#include <stdio.h>
#include "Actor.h"
#include "Game.h"

class MeshComponent;
class CollisionComponent;
class Checkpoint: public Actor{
public:
    Checkpoint(class Game* game, Actor* parent);
    void setlevel(std::string l){mLevelString = l;}
    void setactive(bool b);
private:
    MeshComponent* mc;
    CollisionComponent* cc;
    bool isactive = false;
    void OnUpdate(float deltaTime) override;
    std::string mLevelString = "";
};
#endif /* Checkpoint_hpp */
