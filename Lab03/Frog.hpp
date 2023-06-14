//
//  Frog.hpp
//  Lab03
//
//  Created by Chengxi Xu on 1/27/22.
//

#ifndef Frog_hpp
#define Frog_hpp

#include <stdio.h>
#include "Actor.h"
#include "Game.h"
#include "CollisionComponent.h"
#include <map>

class SpriteComponent;
class Frog: public Actor{
public:
    Frog(class Game* game);
    SpriteComponent* sc;
    std::map<SDL_Scancode, bool> nmap;
    void OnProcessInput(const Uint8* keyState) override;
    bool this_frame;
    bool last_frame;
    void OnUpdate(float deltaTime) override;
    CollisionComponent* cc;
};
#endif /* Frog_hpp */
