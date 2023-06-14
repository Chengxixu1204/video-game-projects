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
    MeshComponent* mc;
    CollisionComponent* cc;
    bool isactive = false;
    void OnUpdate(float deltaTime) override;
    void setactive(bool b);
    std::string mLevelString = "";
    void setlevel(std::string l){mLevelString = l;}
    std::string text;
    void settext(std::string s){text = s;}
    float countdown = 5.0f;
    bool start = false;
};
#endif /* Checkpoint_hpp */
