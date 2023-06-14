//
//  Game.cpp
//  Game-mac
//
//  Created by Sanjay Madhav on 5/31/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "Game.h"
#include "Actor.h"
#include "Log.hpp"
#include "Frog.hpp"
#include "Vehicle.hpp"
#include "SpriteComponent.h"
#include <SDL2/SDL_image.h>
#include <algorithm>
#include <fstream>


Game::Game(){
    n = true;
    previous_time = 0;
    speed = 1000;
    velocity = {300, 300};
}
bool Game::Initialize(){
    Random::Init();
    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) == 0){
        window = SDL_CreateWindow(
               "Lab1",                  // window title
               SDL_WINDOWPOS_UNDEFINED,           // initial x position
               SDL_WINDOWPOS_UNDEFINED,           // initial y position
               WINDOW_WIDTH,                               // width, in pixels
               WINDOW_HEIGHT,                               // height, in pixels
               0                 // flags - see below
        );
        
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
        SDL_RenderSetLogicalSize(renderer, WINDOW_WIDTH*2, WINDOW_HEIGHT*2);
        IMG_Init(IMG_INIT_PNG);
        LoadData();
        
        return 1;
    };
    return 0;
}

void Game::RunLoop(){
    while(n){
        ProcessInput();
        UpdateGame();
        GenerateOuput();
    }
}

void Game::ProcessInput(){
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                n = false;
                break;
        }
    }
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_ESCAPE]) {
        n = false;
    }
    std::vector<Actor*> temp = actors;
    for(auto l: temp){
        l->ProcessInput(state);
    }
}
void Game::UpdateGame(){
    while(SDL_GetTicks() <= previous_time + 16){};
    unsigned int current_time = SDL_GetTicks();
    unsigned int delta_time = current_time - previous_time;
    previous_time = current_time;
    float dtime = delta_time/1000.0f;
//    SDL_Log("%f", dtime);
    if(dtime > 0.033f){
        dtime = 0.033f;
    }
    std::vector<Actor*> temp = actors;
    for(auto l: temp){
        l->Update(dtime);
    }
    std::vector<Actor*> destroy;
    for(auto l: temp){
        if(l->GetState() == ActorState::Destroy){
            destroy.push_back(l);
        }
    }
    for(auto l: destroy){
        delete(l);
    }
}

void Game::GenerateOuput(){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    for(auto l: scvec){
        if(l->IsVisible()){
            l->Draw(renderer);
        }
    }
    SDL_RenderPresent(renderer);
}

void Game::Shutdown(){
    UnloadData();
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::UnloadData(){
    while(actors.size() != 0){
        delete (actors.back());
    }
    //std::unordered_map<std::string, SDL_Texture*>::iterator it;
    for(auto l: umap){
        SDL_DestroyTexture(l.second);
    }
    umap.clear();
}
void Game::AddActor(Actor* a){
    actors.push_back(a);
}

void Game::AddVehicle(Vehicle* v){
    vecv.push_back(v);
}
void Game::AddLog(Log* v){
    logv.push_back(v);
}

void Game::SetFrog(Frog* f){
    fg = f;
}

void Game::RemoveActor(Actor* a){
    std::vector<Actor*>::iterator position = std::find(actors.begin(), actors.end(), a);
    if (position != actors.end()) 
        actors.erase(position);
}

void Game::RemoveVehicle(Vehicle* v){
    std::vector<Vehicle*>::iterator position = std::find(vecv.begin(), vecv.end(), v);
    if (position != vecv.end())
        vecv.erase(position);
}

void Game::RemoveLog(Log* v){
    std::vector<Log*>::iterator position = std::find(logv.begin(), logv.end(), v);
    if (position != logv.end())
        logv.erase(position);
}

SDL_Texture* Game::GetTexture(std::string f){
    std::unordered_map<std::string, SDL_Texture*>::iterator it;
    it = umap.find(f);
    if(it != umap.end()){
        return it->second;
    }else{
        SDL_Surface *image;
        image = IMG_Load(f.c_str());
        if(image != nullptr){
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
            SDL_FreeSurface(image);
            umap.insert({f, texture});
            return texture;
        }
        
    }
    return nullptr;
}
void Game::AddSprite(SpriteComponent *sc){
    scvec.push_back(sc);
    std::sort(scvec.begin(), scvec.end(),
        [](SpriteComponent* a, SpriteComponent* b) {
            return a->GetDrawOrder() < b->GetDrawOrder();
    });
}

void Game::RemoveSprite(SpriteComponent *sc){
    std::vector<SpriteComponent*>::iterator position = std::find(scvec.begin(), scvec.end(), sc);
    if (position != scvec.end()) 
        scvec.erase(position);
}

void Game::LoadData(){
    Actor* t = new Actor(this);
    const Vector2 v2(WINDOW_WIDTH, WINDOW_HEIGHT);
    t->SetPosition(v2);
    SpriteComponent* sc1 = new SpriteComponent(t, 80);
    sc1->SetTexture(GetTexture("Assets/Background.png"));
    std::string line;
    unsigned int count = 0;
    std::ifstream infile("Assets/Level.txt");
    while (std::getline(infile, line)) {
        for(unsigned int i = 0; i < line.size(); i++){
           // SDL_Log("%c", line[i]);
            if(line[i] == 'A'){
                Vehicle* v = new Vehicle(this, i, "A");
                const Vector2 h(64+64*(float)i, 160+64*count);
                v->SetPosition(h);
            }else if(line[i] == 'B'){
                Vehicle* v = new Vehicle(this, i, "B");
                const Vector2 h(64+64*(float)i, 160+64*count);
                v->SetPosition(h);
            }else if(line[i] == 'C'){
                Vehicle* v = new Vehicle(this, i, "C");
                const Vector2 h(64+64*(float)i, 160+64*count);
                v->SetPosition(h);
            }else if(line[i] == 'D'){
                Vehicle* v = new Vehicle(this, i, "D");
                const Vector2 h(64+64*(float)i, 160+64*count);
                v->SetPosition(h);
            }else if(line[i] == 'T'){
                Vehicle* v = new Vehicle(this, i, "T");
                const Vector2 h(64+64*(float)i, 160+64*count);
                v->SetPosition(h);
            }else if(line[i] == 'X'){
                Log* v = new Log(this, i, "X");
                const Vector2 h(64+64*(float)i, 160+64*count);
                v->SetPosition(h);
            }else if(line[i] == 'Y'){
                Log* v = new Log(this, i, "Y");
                const Vector2 h(64+64*(float)i, 160+64*count);
                v->SetPosition(h);
            }else if(line[i] == 'Z'){
                Log* v = new Log(this, i, "Z");
                const Vector2 h(64+64*(float)i, 160+64*count);
                v->SetPosition(h);
            }else if(line[i] == 'F'){
                Frog* v = new Frog(this);
                const Vector2 h(64+64*(float)i, 160+64*count);
                v->SetPosition(h);
                SpriteComponent* s = new SpriteComponent(v, 100);
                s->SetTexture(GetTexture("Assets/Frog.png"));
            }else if(line[i] == 'G'){
                Actor* g = new Actor(this);
                goal = g;
                const Vector2 h(64+64*(float)i, 160+64*count);
                g->SetPosition(h);
                CollisionComponent* cc = new CollisionComponent(g);
            }

        }
        count++;
    }
    
}
