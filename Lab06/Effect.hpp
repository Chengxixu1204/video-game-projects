//
//  Effect.hpp
//  Lab06
//
//  Created by Chengxi Xu on 3/3/22.
//

#ifndef Effect_hpp
#define Effect_hpp

#include <stdio.h>
#include "Actor.h"
#include "Game.h"

class AnimatedSprite;
class Effect: public Actor{
public:
    Effect(class Game* game, Vector2 position, std::string Aniname, const char* soundname);
    AnimatedSprite* as;
private:
    float lifetime;
    void OnUpdate(float deltaTime) override;
};
#endif /* Effect_hpp */
