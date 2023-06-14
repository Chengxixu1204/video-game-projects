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
#include "VehicleMove.hpp"
#include <map>
#include <vector>


class PlayerMove: public VehicleMove{
public:
    PlayerMove(class Actor* owner);
private:
    Vector3 Pl_velocity;
    void Update(float deltaTime) override;
    void ProcessInput(const Uint8* keyState) override;
    void OnLapChange(int newLap) override;
    bool Is_visited = false;
};
#endif /* PlayerMove_hpp */
