//
//  Log.cpp
//  Lab03
//
//  Created by Chengxi Xu on 1/27/22.
//

#include "Log.hpp"
#include "SpriteComponent.h"
#include "WrappingMove.hpp"
#include "CollisionComponent.h"

Log::Log(class Game* game, int linenum, std::string l)
:Actor(game)
{
    line = linenum;
    letter = l;
    sc = new SpriteComponent(this, 100);
    wm = new WrappingMove(this);
    mGame->AddLog(this);
    cc = new CollisionComponent(this);
    if(line%2 == 1){
        wm->SetPos(Vector2(-1, 0));
    }else{
        wm->SetPos(Vector2(1, 0));
    }
    wm->SetForwardSpeed(75.0f);
    if(letter == "X"){
        cc->SetSize(192.0f, SIZE);
        sc->SetTexture(mGame->GetTexture("Assets/LogX.png"));
    }else if(letter == "Y"){
        cc->SetSize(256.0f, SIZE);
        sc->SetTexture(mGame->GetTexture("Assets/LogY.png"));
    }else{
        cc->SetSize(384.0f, SIZE);
        sc->SetTexture(mGame->GetTexture("Assets/LogZ.png"));
    }
};

Log::~Log(){
    mGame->RemoveLog(this);
}
