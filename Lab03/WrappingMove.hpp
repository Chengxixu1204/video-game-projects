//
//  WrappingMove.hpp
//  Lab03
//
//  Created by Chengxi Xu on 1/31/22.
//

#ifndef WrappingMove_hpp
#define WrappingMove_hpp

#include <stdio.h>
#include "Math.h"
#include "Actor.h"
#include "Game.h"
#include "MoveComponent.h"


class WrappingMove: public MoveComponent{
public:
    WrappingMove(class Actor* owner);
    Vector2 position;
    void SetPos(const Vector2& pos){ position = pos; }
    const Vector2& GetPos(){return position;}
    void Update(float deltaTime) override;
};
#endif /* WrappingMove_hpp */
