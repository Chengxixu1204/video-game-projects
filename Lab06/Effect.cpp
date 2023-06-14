//
//  Effect.cpp
//  Lab06
//
//  Created by Chengxi Xu on 3/3/22.
//

#include "Effect.hpp"
#include "AnimatedSprite.h"


Effect::Effect(class Game* game, Vector2 position, std::string Aniname, const char* soundname)
:Actor(game)
{
    this->SetPosition(position);
    as = new AnimatedSprite(this);
    as->LoadAnimations("Assets/Effects");
    as->SetAnimation(Aniname);
    lifetime = as->GetAnimDuration(Aniname);
    Mix_Chunk *soundsample;
    soundsample = this->GetGame()->GetSound(soundname);
    Mix_PlayChannel(-1, soundsample, 0);
};

void Effect::OnUpdate(float deltaTime){
    lifetime -= deltaTime;
    if(lifetime <= 0){
        SetState(ActorState::Destroy);
    }
}
