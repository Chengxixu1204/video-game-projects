//
//  PlayerMove.hpp
//  Lab07
//
//  Created by Chengxi Xu on 3/6/22.
//

#ifndef PlayerMove_hpp
#define PlayerMove_hpp

#include <stdio.h>
#include "Actor.h"
#include "Game.h"
#include "MoveComponent.h"
#include <map>
#include <vector>

class Block;

class PlayerMove: public MoveComponent{
public:
    PlayerMove(class Actor* owner);
    Vector3 velocity;
    void Update(float deltaTime) override;
    void ProcessInput(const Uint8* keyState) override;
    void CreateBlock();
    void CreateObs();
    std::string filepath = "Assets/Blocks";
    float x_pos = mOwner->GetPosition().x;
    float x_pos2 = mOwner->GetPosition().x;
    std::map<SDL_Scancode, bool> nmap;
    void explode(Block* bl);
    float speedmulti;
    float tracktime = 0.0f;
    std::vector<int> hurtframe;
    int hurtn;
    int framecount = 0;
    float rolltime = 0.0f;
    bool isroll = false;
    float cool = 0.0f;
    void CheckExploden(Block* bl);
    std::vector<Block*> bv;
    int play;
    bool ishurt = false;
    int damagecount = 0;
    bool first = true;
    
};
#endif /* PlayerMove_hpp */
