//
//  LaserComponent.hpp
//  Lab10
//
//  Created by Chengxi Xu on 4/4/22.
//

#ifndef LaserComponent_hpp
#define LaserComponent_hpp

#include <stdio.h>
#include "MeshComponent.h"
#include "Actor.h"
#include "Game.h"
#include "SegmentCast.h"

class LaserComponent : public MeshComponent
{
public:
    LaserComponent(class Actor* owner);
    void Update(float deltaTime) override;
    void Draw(class Shader *shader) override;
    std::vector<LineSegment> vls;
    Matrix4 helper(LineSegment lines);
};
#endif /* LaserComponent_hpp */
