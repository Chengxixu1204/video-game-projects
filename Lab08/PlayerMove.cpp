//
//  PlayerMove.cpp
//  Lab07
//
//  Created by Chengxi Xu on 3/6/22.
//

#include "PlayerMove.hpp"
#include "Renderer.h"
#include "Random.h"
#include "Player.hpp"
#include "HeightMap.hpp"
#include "PlayerUI.h"
#include "Enemy.hpp"
#include "EnemyMove.hpp"

const int FADE = 250;
const int SPEED = 4000;

PlayerMove::PlayerMove(class Actor* owner)
:VehicleMove(owner)
{
    mOwner->SetPosition(mOwner->GetGame()->Height_map->CellToWorld(39, 58));
};

void PlayerMove::Update(float deltaTime){
    VehicleMove::Update(deltaTime);
}

void PlayerMove::ProcessInput(const Uint8 *keyState){
    keyState = SDL_GetKeyboardState(nullptr);
    if(keyState[SDL_SCANCODE_W] || keyState[SDL_SCANCODE_UP]){
        this->SetPre(true);
    }else{
        this->SetPre(false);
    }
    if(keyState[SDL_SCANCODE_A] || keyState[SDL_SCANCODE_LEFT]){
        this->SetTurn(Left);
    }else if(keyState[SDL_SCANCODE_D] || keyState[SDL_SCANCODE_RIGHT]){
        this->SetTurn(Right);
    }else{
        this->SetTurn(None);
    }
    
}

void PlayerMove::OnLapChange(int newLap){
    if(newLap == 4 && !Is_visited){
        Mix_FadeOutChannel(mOwner->GetGame()->Start_time, FADE);
        Mix_PlayChannel(-1, mOwner->GetGame()->GetSound("Assets/Sounds/FinalLap.wav"), 0);
        mOwner->GetGame()->Start_time = Mix_FadeInChannel(-1, mOwner->GetGame()->GetSound("Assets/Sounds/MusicFast.ogg"), -1, SPEED);
        Is_visited = true;
    }
    if(newLap == 5){
        Mix_FadeOutChannel(mOwner->GetGame()->Start_time, FADE);
        if(newLap <= mOwner->GetGame()->Enemy_ene->Ene_mov->GetLap()){
           mOwner->GetGame()->Getpl()->Pl_ui->SetRaceState(PlayerUI::Lost);
            Mix_PlayChannel(-1, mOwner->GetGame()->GetSound("Assets/Sounds/Lost.wav"), 0);
        }else{
            mOwner->GetGame()->Getpl()->Pl_ui->SetRaceState(PlayerUI::Won);
            Mix_PlayChannel(-1, mOwner->GetGame()->GetSound("Assets/Sounds/Won.wav"), 0);
        }
        mOwner->GetGame()->Getpl()->SetState(ActorState::Paused);
        mOwner->GetGame()->Enemy_ene->SetState(ActorState::Paused);
    }else{
      mOwner->GetGame()->Getpl()->Pl_ui->OnLapChange(newLap);
    }
    
}
