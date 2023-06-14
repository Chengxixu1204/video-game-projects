//
//  PlayerMove.hpp
//  Lab04
//
//  Created by Chengxi Xu on 2/3/22.
//

#ifndef PlayerMove_hpp
#define PlayerMove_hpp

#include <stdio.h>

#include "Actor.h"
#include "Game.h"
#include "MoveComponent.h"
#include <map>

class Sword;
enum Type
{
    UP,
    DOWN,
    RIGHT,
    LEFT
};

class PlayerMove: public MoveComponent{
public:
    PlayerMove(class Actor* owner);
    void ProcessInput(const Uint8* keyState) override;
    void Update(float deltaTime) override;
    std::map<SDL_Scancode, bool> nmap;
    Vector2 origin;
    Vector2 Dir;
    Type mType;
    bool checkif_move = false;
    bool checkif_attack = false;
    float timestamp = 0.0f;
private:
    Sword* sd;
    void UpdateSD();
    void UpdateAni(Type n);
    void CheckColli();
    std::string up = "Up";
    std::string down = "Down";
    std::string left = "Left";
    std::string right = "Right";
    

};
#endif /* PlayerMove_hpp */
