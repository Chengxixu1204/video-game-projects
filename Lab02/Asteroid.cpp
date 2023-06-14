//
//  Asteroid.cpp
//  Lab02
//
//  Created by Chengxi Xu on 1/25/22.
//

#include "Asteroid.hpp"
#include "SpriteComponent.h"
#include "MoveComponent.h"

Asteroid::Asteroid(class Game* game)
:Actor(game)
{
    //constructor
    //initialization
    mGame->AddAsteroid(this);
    mc = new MoveComponent(this);
    mc->SetForwardSpeed(150.0f);
    sc = new SpriteComponent(this, 100);
    sc->SetTexture(mGame->GetTexture("Assets/Asteroid.png"));
    mRotation = Random::GetFloatRange(0.0f, Math::TwoPi);
    Vector2 min(0.0f,0.0f);
    Vector2 max(WINDOW_WIDTH,WINDOW_HEIGHT);
    mPosition = Random::GetVector(min,max);
    
};
Asteroid::~Asteroid(){
    //remove
    mGame->RemoveAsteroid(this);
}
void Asteroid::OnUpdate(float deltaTime) {
    //make sure asteroid wove wrap around
    if(this->GetPosition().x < 0){
        this->SetPosition(Vector2(WINDOW_WIDTH-1, GetPosition().y));
    }else if(this->GetPosition().x > WINDOW_WIDTH){
        this->SetPosition(Vector2(1, GetPosition().y));
    }else if(this->GetPosition().y < 0){
        this->SetPosition(Vector2(GetPosition().x, WINDOW_HEIGHT-1));
    }else if(this->GetPosition().y > WINDOW_HEIGHT){
        this->SetPosition(Vector2(GetPosition().x, 1));
    }
}
