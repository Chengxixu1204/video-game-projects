//
//  Vehicle.cpp
//  Lab03
//
//  Created by Chengxi Xu on 1/27/22.
//

#include "Vehicle.hpp"
#include "SpriteComponent.h"

Vehicle::Vehicle(class Game* game, int linenum, std::string type)
:Actor(game)
{
    line = linenum;
    sc = new SpriteComponent(this, 100);
    wm = new WrappingMove(this);
    cc = new CollisionComponent(this);
    t = type;
    mGame->AddVehicle(this);
    if(line%2 == 1){
        wm->SetPos(Vector2(-1, 0));
    }else{
        wm->SetPos(Vector2(1, 0));
    }
    wm->SetForwardSpeed(75.0f);
    if(t == "T"){
        cc->SetSize(BSIZE*2, 48.0f);
    }else{
        cc->SetSize(BSIZE, BSIZE);
    }
    if(t == "A"){
        sc->SetTexture(mGame->GetTexture("Assets/CarA.png"));
    }else if(t == "B"){
        sc->SetTexture(mGame->GetTexture("Assets/CarB.png"));
    }else if(t == "C"){
        sc->SetTexture(mGame->GetTexture("Assets/CarC.png"));
    }else if(t == "D"){
        sc->SetTexture(mGame->GetTexture("Assets/CarD.png"));
    }else if(t == "T"){
        sc->SetTexture(mGame->GetTexture("Assets/Truck.png"));
    }
    
};

Vehicle::~Vehicle(){
    //remove
    mGame->RemoveVehicle(this);
}

void Vehicle::OnUpdate(float deltaTime){
    Vector2 first = this->wm->GetPos();
    float len1 = first.Length();
    Vector2 second((mGame->fg->GetPosition().x - this->GetPosition().x), (mGame->fg->GetPosition().y - this->GetPosition().y));
    float len2 = second.Length();
    float result = Vector2::Dot(first, second);
    float r = len1*len2;
    if(Math::Acos(result/r) <= Math::PiOver2/3){
        this->wm->SetForwardSpeed(75.0f/2.0f);
    }else{
        this->wm->SetForwardSpeed(75.0f);
    }
}
