//
//  EnemyMove.hpp
//  Lab08
//
//  Created by Chengxi Xu on 3/20/22.
//

#ifndef EnemyMove_hpp
#define EnemyMove_hpp

#include <stdio.h>
#include "Actor.h"
#include "Game.h"
#include "VehicleMove.hpp"

class EnemyMove : public VehicleMove
{
public:
    EnemyMove(class Actor* owner);
    void Update(float deltaTime) override;
private:
    std::vector<Vector3> Path_record;
    int Next_target = 1;
};
#endif /* EnemyMove_hpp */
