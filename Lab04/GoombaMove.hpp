//
//  GoombaMove.hpp
//  Lab04
//
//  Created by Chengxi Xu on 2/7/22.
//

#ifndef GoombaMove_hpp
#define GoombaMove_hpp

#include <stdio.h>
#include "Actor.h"
#include "Game.h"
#include "MoveComponent.h"


class GoombaMove: public MoveComponent{
public:
    GoombaMove(class Actor* owner);
    void Update(float deltaTime) override;
    float mYSpeed;
    bool move;
};
#endif /* GoombaMove_hpp */
