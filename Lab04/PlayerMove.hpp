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


class PlayerMove: public MoveComponent{
public:
    PlayerMove(class Actor* owner);
    void ProcessInput(const Uint8* keyState) override;
    void Update(float deltaTime) override;
    float mYSpeed;
    bool mSpacePressed;
    bool mInAir;
    std::map<SDL_Scancode, bool> nmap;
    Vector2 origin;
    void AnimationPlayer();
    bool isdead;
};
#endif /* PlayerMove_hpp */
