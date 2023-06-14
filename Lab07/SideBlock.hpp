//
//  SideBlock.hpp
//  Lab07
//
//  Created by Chengxi Xu on 3/6/22.
//

#ifndef SideBlock_hpp
#define SideBlock_hpp

#include <stdio.h>
#include "Actor.h"
#include "Game.h"

class MeshComponent;
class SideBlock: public Actor{
public:
    SideBlock(class Game* game, size_t t);
    MeshComponent* mc;
    void OnUpdate(float deltaTime) override;
};
#endif /* SideBlock_hpp */
