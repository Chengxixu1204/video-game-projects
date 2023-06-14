//
//  PlayerMove.cpp
//  Lab07
//
//  Created by Chengxi Xu on 3/6/22.
//

#include "PlayerMove.hpp"
#include "Renderer.h"
#include "SideBlock.hpp"
#include "Block.hpp"
#include "Random.h"
#include "Bullet.hpp"
#include "CollisionComponent.h"
#include "Player.hpp"
#include "HUD.h"

PlayerMove::PlayerMove(class Actor* owner)
:MoveComponent(owner)
{
    nmap.insert({SDL_SCANCODE_SPACE, false});
    nmap.insert({SDL_SCANCODE_Q, false});
    velocity = Vector3(400.0f, 0.0f, 0.0f);
    speedmulti = 1.0f;
    for(size_t i = 0; i <= 4000 ; i += 500){
        SideBlock* s1 = new SideBlock(mOwner->GetGame(), 0);
        s1->SetPosition(Vector3(i, 500.0f, 0.0f));
        s1->SetRotation(Math::Pi);
        SideBlock* s2 = new SideBlock(mOwner->GetGame(), 0);
        s2->SetPosition(Vector3(i, -500.0f, 0.0f));
        SideBlock* s3 = new SideBlock(mOwner->GetGame(), 5);
        s3->SetPosition(Vector3(i, 0.0f, -500.0f));
        SideBlock* s4 = new SideBlock(mOwner->GetGame(), 6);
        s4->SetPosition(Vector3(i, 0.0f, 500.0f));
    }
    for(int i = 1; i <= 4; i ++){
        std::string index = std::to_string(i);
        std::string result = filepath + "/" + index + ".txt";
        mOwner->GetGame()->LoadBlocks(result.c_str(), i);
    }
};

void PlayerMove::Update(float deltaTime){
    framecount++;
    cool -= deltaTime;
    mOwner->SetPosition(mOwner->GetPosition() + deltaTime*velocity*speedmulti);
    mOwner->SetPosition(Vector3(mOwner->GetPosition().x, Math::Clamp(mOwner->GetPosition().y, -180.0f, 180.0f), Math::Clamp(mOwner->GetPosition().z, -225.0f, 225.0f)));
    Vector3 eyepos = mOwner->GetPosition() - Vector3(1.0f, 0.0f, 0.0f)*300;
    eyepos.z = 0.0f;
    Vector3 target = mOwner->GetPosition() + Vector3(1.0f, 0.0f, 0.0f)*20;
    Matrix4 camera = Matrix4::CreateLookAt(eyepos, target, Vector3::UnitZ);
    mOwner->GetGame()->GetRenderer()->SetViewMatrix(camera);
    CreateBlock();
    CreateObs();
    for(size_t i = 0; i < mOwner->GetGame()->bvec.size(); i++){
        if(mOwner->GetComponent<CollisionComponent>()
       ->Intersect(mOwner->GetGame()->bvec[i]->GetComponent<CollisionComponent>())){
            if(mOwner->GetGame()->bvec[i]->texture == 4){
                Mix_PlayChannel(-1, mOwner->GetGame()->GetSound("Assets/Sounds/BlockExplode.wav"), 0);
                explode(mOwner->GetGame()->bvec[i]);
            }else{
                mOwner->GetGame()->bvec[i]->SetState(ActorState::Destroy);
            }
            ishurt = true;
            if(hurtframe.size() != 0){
              hurtn = hurtframe.back();
            }
            hurtframe.push_back(framecount);
        }
    }
    if(hurtframe.size() != 0){
        if(ishurt  && (hurtn != framecount - 1)){
            mOwner->GetGame()->pl->slevel -= 1;
            Mix_PlayChannel(-1, mOwner->GetGame()->GetSound("Assets/Sounds/ShipHit.wav"), 0);
            if(mOwner->GetGame()->pl->slevel <=0 ){
                mOwner->SetState(ActorState::Paused);
                Mix_PlayChannel(-1, mOwner->GetGame()->GetSound("Assets/Sounds/ShipDie.wav"), 0);
            }
            ishurt = false;
        }
    }else{
        if(ishurt){
            mOwner->GetGame()->pl->slevel -= 1;
            Mix_PlayChannel(-1, mOwner->GetGame()->GetSound("Assets/Sounds/ShipHit.wav"), 0);
            if(mOwner->GetGame()->pl->slevel <=0 ){
                mOwner->SetState(ActorState::Paused);
                Mix_PlayChannel(-1, mOwner->GetGame()->GetSound("Assets/Sounds/ShipDie.wav"), 0);
            }
            ishurt = false;
        }
        
    }
    if(tracktime >= 10){
        speedmulti += 0.15f;
        tracktime = 0.0f;
    }
    if(isroll && rolltime <= 0.5f){
        rolltime += deltaTime;
        mOwner->SetRollAngle(mOwner->GetRollAngle() + deltaTime*8.0f * Math::Pi);
    }else if(isroll && rolltime > 0.5f){
        mOwner->SetRollAngle(0.0f);
        rolltime = 0.0f;
        isroll = false;
    }
//    if((mOwner->GetGame()->Getpl()->slevel < 3) && cool <= 0){
//        if(damagecount == 0){
//            mOwner->GetGame()->Getpl()->h->DoABarrelRoll();
//            cool = Random::GetFloatRange(15.0f, 25.0f);
//            damagecount = 1;
//        }else{
//            cool = Random::GetFloatRange(15.0f, 25.0f);
//            damagecount -= 1;
//        }
//    }
//    if((mOwner->GetGame()->Getpl()->slevel < 3) && cool <= 0){
//            mOwner->GetGame()->Getpl()->h->DoABarrelRoll();
//            cool = Random::GetFloatRange(15.0f, 25.0f);
//    }
    if(mOwner->GetGame()->Getpl()->slevel < 3 && first){
        cool = Random::GetFloatRange(15.0f, 25.0f);
        first = false;
    }
    if((mOwner->GetGame()->Getpl()->slevel < 3) && cool <= 0 && !first){
            mOwner->GetGame()->Getpl()->h->DoABarrelRoll();
            cool = Random::GetFloatRange(15.0f, 25.0f);
    }else if((mOwner->GetGame()->Getpl()->slevel < 3) && damagecount == 0 && !first){
        mOwner->GetGame()->Getpl()->h->DoABarrelRoll();
        cool = Random::GetFloatRange(15.0f, 25.0f);
        damagecount = 1;
    }
    if(mOwner->GetGame()->Getpl()->slevel == 3){
        first = true;
    }
    tracktime += deltaTime;
    if(mOwner->GetGame()->pl->slevel == 1 && !Mix_Playing(mOwner->GetGame()->alert)){
        mOwner->GetGame()->alert = Mix_PlayChannel(-1, mOwner->GetGame()->GetSound("Assets/Sounds/DamageAlert.ogg"), -1);
        mOwner->GetGame()->fff = true;
    }
    
}

void PlayerMove::ProcessInput(const Uint8 *keyState){
    keyState = SDL_GetKeyboardState(nullptr);
    if(keyState[SDL_SCANCODE_W] && !keyState[SDL_SCANCODE_S]){
        velocity.z = 300.0f*speedmulti;
    }else if(keyState[SDL_SCANCODE_S] && !keyState[SDL_SCANCODE_W]){
        velocity.z = -300.0f*speedmulti;
    }else{
        velocity.z = 0.0f;
    }
    if(keyState[SDL_SCANCODE_D] && !keyState[SDL_SCANCODE_A]){
        velocity.y = 300.0f*speedmulti;
    }else if(keyState[SDL_SCANCODE_A] && !keyState[SDL_SCANCODE_D]){
        velocity.y = -300.0f*speedmulti;
    }else{
        velocity.y = 0.0f;
    }
    if(keyState[SDL_SCANCODE_SPACE] && !nmap[SDL_SCANCODE_SPACE]){
        Mix_PlayChannel(-1, mOwner->GetGame()->GetSound("Assets/Sounds/Shoot.wav"), 0);
        Bullet* bt = new Bullet(mOwner->GetGame());
        bt->SetPosition(mOwner->GetPosition());
        bt->GetComponent<MoveComponent>()->SetForwardSpeed(900*speedmulti);
    }
    if(keyState[SDL_SCANCODE_Q] && !nmap[SDL_SCANCODE_Q]){
        Mix_PlayChannel(-1, mOwner->GetGame()->GetSound("Assets/Sounds/Boost.wav"), 0);
        isroll = true;
        if(mOwner->GetGame()->Getpl()->slevel < 3){
           mOwner->GetGame()->Getpl()->Addslevel(1);
        }
    }
    nmap[SDL_SCANCODE_Q] = keyState[SDL_SCANCODE_Q];
    nmap[SDL_SCANCODE_SPACE] = keyState[SDL_SCANCODE_SPACE];
    
}

void PlayerMove::CreateBlock(){
    int extra = static_cast<int>(mOwner->GetPosition().x/500);
    if(mOwner->GetPosition().x >= x_pos + 500){
        SideBlock* s1 = new SideBlock(mOwner->GetGame(), 0);
        s1->SetPosition(Vector3(4000 + 500*extra, 500.0f, 0.0f));
        s1->SetRotation(Math::Pi);
        SideBlock* s2 = new SideBlock(mOwner->GetGame(), 0);
        s2->SetPosition(Vector3(4000 + 500*extra, -500.0f, 0.0f));
        SideBlock* s3 = new SideBlock(mOwner->GetGame(), 5);
        s3->SetPosition(Vector3(4000 + 500*extra, 0.0f, -500.0f));
        SideBlock* s4 = new SideBlock(mOwner->GetGame(), 6);
        s4->SetPosition(Vector3(4000 + 500*extra, 0.0f, 500.0f));
        x_pos += 500;
    }
}

void PlayerMove::CreateObs(){
    int extra = static_cast<int>(mOwner->GetPosition().x/1000);
    int n;
    if(mOwner->GetPosition().x >= x_pos2 + 1000){
        if(extra + 4 > 20){
            n = Random::GetIntRange(1, 20);
        }else{
            n = extra + 4;
        }
        std::string result = filepath + "/" + std::to_string(n) + ".txt";
        mOwner->GetGame()->LoadBlocks(result.c_str(), extra + 4);
        x_pos2 += 1000;
    }
    
}

void PlayerMove::explode(Block *bl){
    for(size_t i = 0; i < mOwner->GetGame()->bvec.size(); i++){
        if(Vector3::Distance(bl->GetPosition(), mOwner->GetGame()->bvec[i]->GetPosition()) <= 50){
            if(mOwner->GetGame()->bvec[i]->texture == 4){
                CheckExploden(mOwner->GetGame()->bvec[i]);
            }
            mOwner->GetGame()->bvec[i]->SetState(ActorState::Destroy);
        }
    }
    bl->SetState(ActorState::Destroy);
    return;
}

void PlayerMove::CheckExploden(Block *bl){
   for(size_t i = 0; i < mOwner->GetGame()->bvec.size(); i++){
        if(Vector3::Distance(bl->GetPosition(), mOwner->GetGame()->bvec[i]->GetPosition()) <= 50){
            if(mOwner->GetGame()->bvec[i]->texture == 4 && std::count(bv.begin(), bv.end(), mOwner->GetGame()->bvec[i]) == 0){
                bv.push_back(mOwner->GetGame()->bvec[i]);
                CheckExploden(mOwner->GetGame()->bvec[i]);
            }
            mOwner->GetGame()->bvec[i]->SetState(ActorState::Destroy);
        }
    }
    bl->SetState(ActorState::Destroy);
    return;
}
