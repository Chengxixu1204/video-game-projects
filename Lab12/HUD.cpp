//
//  HUD.cpp
//  Lab12
//
//  Created by Chengxi Xu on 4/17/22.
//

#include "HUD.hpp"
#include "Player.hpp"
#include "Checkpoint.hpp"
#include "Font.h"
#include "Texture.h"
#include <math.h>
#include "Renderer.h"
#include "SecurityCamera.hpp"

HUD::HUD(class Actor* owner)
:UIComponent(owner)
{
    mFont = new Font();
    mFont->Load("Assets/Inconsolata-Regular.ttf");
    mTimerText = mFont->RenderText("00:00.00");
    std::string re = std::to_string(mOwner->GetGame()->coinnum) + "/" + "55";
    mCoinText = mFont->RenderText(re);
    r1 = mOwner->GetGame()->GetRenderer()->GetTexture("Assets/Radar.png");
    r2 = mOwner->GetGame()->GetRenderer()->GetTexture("Assets/RadarArrow.png");
    r3 = mOwner->GetGame()->GetRenderer()->GetTexture("Assets/Blip.png");
}

HUD::~HUD(){
    mFont->Unload();
    delete mFont;
}

void HUD::Draw(class Shader *shader){
    DrawTexture(shader, mTimerText, Vector2(-420.0f, -325.0f));
    DrawTexture(shader, mCoinText, Vector2(-450.0f, -305.0f));
    DrawTexture(shader, mOwner->GetGame()->mCheckText, Vector2::Zero);
    DrawTexture(shader, r1, Vector2(350.0f, -285.0f));
    DrawTexture(shader, r2, Vector2(350.0f, -285.0f));
    bliploc(shader);
//    for(size_t i = 0; i < allblip.size(); i++){
//        DrawTexture(shader, r3, allblip[i]);
//    }
}

void HUD::Update(float deltaTime){
    mOwner->GetGame()->counttime += deltaTime;
    mTimerText->Unload();
    delete mTimerText;
    mTimerText = mFont->RenderText(Gettimestr(mOwner->GetGame()->counttime));
    if(start){
        countdown -= deltaTime;
    }
    if(countdown <= 0.0f){
        mOwner->GetGame()->mCheckText = mFont->RenderText(" ");
        start = false;
        countdown = 5.0f;
    }
    
}

std::string HUD::Gettimestr(float t){
    int result = (int)(t * 100 + .5);
    float re = result/100.0f;
    int part1 = (int)re/(int)60.0f;
    float part2 = re - part1*60.0f;
    std::string pa1 = std::to_string(part1);
    std::string pa2 = std::to_string(part2);
    pa2.pop_back();
    pa2.pop_back();
    pa2.pop_back();
    pa2.pop_back();
    if(pa1.size() == 1){
        pa1 = "0" + pa1;
    }
    if(pa2.size() == 4){
        pa2 = "0" + pa2;
    }
    return (pa1 + ":" + pa2);
}

void HUD::SetCoinText(){
    mOwner->GetGame()->coinnum += 1;
    mCoinText->Unload();
    delete mCoinText;
    std::string re = std::to_string(mOwner->GetGame()->coinnum) + "/" + "55";
    mCoinText = mFont->RenderText(re);
}

void HUD::SetCheckText(std::string t){
    mOwner->GetGame()->mCheckText = mFont->RenderText(t);
    start = true;
}

void HUD::bliploc(class Shader *shader){
    Vector2 forwardpl = Vector2(mOwner->GetForward().x, mOwner->GetForward().y);
    float angle = Math::Atan2(forwardpl.y, forwardpl.x);
    for(size_t i = 0; i < mOwner->GetGame()->allcam.size(); i++){
        Vector2 plpos = Vector2(mOwner->GetWorldPosition().y, mOwner->GetWorldPosition().x);
        Vector2 campos = Vector2(mOwner->GetGame()->allcam[i]->GetWorldPosition().y, mOwner->GetGame()->allcam[i]->GetWorldPosition().x);
        Vector2 tocam = campos - plpos;
        if(tocam.Length() <= 1500.0f){
            tocam = Vector2(tocam.x / 1500.0f * 92, tocam.y / 1500.0f * 92);
            Matrix3 roll = Matrix3::CreateRotation(angle);
            Vector2 re = Vector2::Transform(tocam, roll);
            Vector2 fo = Vector2(mOwner->GetGame()->allcam[i]->GetForward().y, mOwner->GetGame()->allcam[i]->GetForward().x);
            Vector2 r = Vector2::Transform(fo, roll);
            float a = Math::Atan2(r.y, r.x);
            DrawTexture(shader, r3, re + Vector2(350.0f, -285.0f), 1.0f, a);
        }
    }
}
