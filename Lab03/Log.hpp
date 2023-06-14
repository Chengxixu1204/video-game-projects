//
//  Log.hpp
//  Lab03
//
//  Created by Chengxi Xu on 1/27/22.
//

#ifndef Log_hpp
#define Log_hpp

#include <stdio.h>
#include "Actor.h"
#include "Game.h"

class WrappingMove;
class CollisionComponent;
class SpriteComponent;
const int SIZE = 48.0f;
class Log: public Actor{
public:
    Log(class Game* game, int linenum, std::string l);
    ~Log();
    std::string letter;
    int line;
    SpriteComponent* sc;
    WrappingMove* wm;
    CollisionComponent* cc;
};

#endif /* Log_hpp */
