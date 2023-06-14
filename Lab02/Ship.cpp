//
//  Ship.cpp
//  Lab02
//
//  Created by Chengxi Xu on 1/25/22.
//

#include "Ship.hpp"
#include "Laser.hpp"
#include "SpriteComponent.h"
#include "MoveComponent.h"


Ship::Ship(class Game* game)
:Actor(game)
{
    mc = new MoveComponent(this);
    sc = new SpriteComponent(this, 100);
    sc->SetTexture(mGame->GetTexture("Assets/Ship.png"));
    tracktime = 0.0f;
    
};
void Ship::OnUpdate(float deltaTime) {
    tracktime -= deltaTime;
}
void Ship::OnProcessInput(const Uint8* keyState) {
    keyState = SDL_GetKeyboardState(nullptr);
    //update motion
    if(keyState[SDL_SCANCODE_UP] && !keyState[SDL_SCANCODE_DOWN]){
        sc->SetTexture(mGame->GetTexture("Assets/ShipThrust.png"));
        mc->SetForwardSpeed(200);
    }else if(keyState[SDL_SCANCODE_DOWN] && !keyState[SDL_SCANCODE_UP]){
        sc->SetTexture(mGame->GetTexture("Assets/ShipThrust.png"));
        mc->SetForwardSpeed(-200);
    }else{
        mc->SetForwardSpeed(0);
    }
    //not allow to move when press both
    if(keyState[SDL_SCANCODE_LEFT] && !keyState[SDL_SCANCODE_RIGHT]){
        sc->SetTexture(mGame->GetTexture("Assets/ShipThrust.png"));
        mc->SetAngularSpeed((float)Math::PiOver2/2);
    }else if(keyState[SDL_SCANCODE_RIGHT] && !keyState[SDL_SCANCODE_LEFT]){
        sc->SetTexture(mGame->GetTexture("Assets/ShipThrust.png"));
        mc->SetAngularSpeed(-(float)Math::PiOver2/2);
    }else{
        mc->SetAngularSpeed(0);
    }
    //only allow one laser per second
    if(keyState[SDL_SCANCODE_SPACE]){
        if(tracktime <= 0.0f){
            Laser* la = new Laser(mGame);
            la->SetPosition(GetPosition());
            la->SetRotation(GetRotation());
            tracktime = 1.0f;
        }
    }
    sc->SetTexture(mGame->GetTexture("Assets/Ship.png"));
}
