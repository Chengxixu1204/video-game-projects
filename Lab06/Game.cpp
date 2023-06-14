//
//  Game.cpp
//  Game-mac
//
//  Created by Sanjay Madhav on 5/31/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "Game.h"
#include "Actor.h"
#include "SpriteComponent.h"
#include "Player.hpp"
#include <SDL2/SDL_image.h>
#include <algorithm>
#include <fstream>
#include "TiledBGComponent.hpp"
#include <sstream>
#include <iostream>
#include "Collider.hpp"
#include "Bush.hpp"
#include "Soldier.hpp"
#include "PathFinder.h"


Game::Game(){
    n = true;
    previous_time = 0;
    speed = 1000;
    velocity = {300, 300};
    camera = Vector2(0.0f, 0.0f);
}
bool Game::Initialize(){
    Random::Init();
    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) == 0){
        window = SDL_CreateWindow(
               "Lab1",                  // window title
               SDL_WINDOWPOS_UNDEFINED,           // initial x position
               SDL_WINDOWPOS_UNDEFINED,           // initial y position
               512,                               // width, in pixels
               448,                               // height, in pixels
               0                 // flags - see below
        );
        
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
        IMG_Init(IMG_INIT_PNG);
        //SDL_RenderSetLogicalSize(renderer, 896, 1024);
        Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
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
    for(unsigned int i = 0; i < temp.size(); i++){
        temp[i]->ProcessInput(state);
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
    for(unsigned int i = 0; i < temp.size(); i++){
        temp[i]->Update(dtime);
    }
    std::vector<Actor*> destroy;
    for(unsigned int i = 0; i < temp.size(); i++){
        if(temp[i]->GetState() == ActorState::Destroy){
            destroy.push_back(temp[i]);
        }
    }
    for(unsigned int i = 0; i < destroy.size(); i++){
        delete(destroy[i]);
    }
    if(!Mix_Playing(act)){
        Mix_Chunk *sample;
        sample = this->GetSound("Assets/Sounds/MusicLoop.ogg");
        act = Mix_PlayChannel(-1, sample, -1);
    }
}

void Game::GenerateOuput(){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    for(unsigned int i=0 ; i < scvec.size(); i++){
        if(scvec[i]->IsVisible()){
            scvec[i]->Draw(renderer);
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
    Mix_CloseAudio();
}

void Game::UnloadData(){
    while(actors.size() != 0){
        delete (actors.back());
    }
    std::unordered_map<std::string, SDL_Texture*>::iterator it;
    for(it = umap.begin(); it != umap.end(); it++){
        SDL_DestroyTexture(it->second);
    }
    umap.clear();
    std::unordered_map<std::string, Mix_Chunk*>::iterator is;
    for(is = smap.begin(); is != smap.end(); is++){
        Mix_FreeChunk(is->second);
    }
    smap.clear();
}
void Game::AddActor(Actor* a){
    actors.push_back(a);
}


void Game::RemoveActor(Actor* a){
    std::vector<Actor*>::iterator position = std::find(actors.begin(), actors.end(), a);
    if (position != actors.end()) 
        actors.erase(position);
}

Vector2& Game::GetCameraPos(){
    return camera;
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
void Game::AddEnemy(EnemyComponent *ec){
    evec.push_back(ec);
}

void Game::RemoveEnemy(EnemyComponent *ec){
    std::vector<EnemyComponent*>::iterator position = std::find(evec.begin(), evec.end(), ec);
    if (position != evec.end())
        evec.erase(position);
}

Mix_Chunk* Game::GetSound(const char *filename){
    std::unordered_map<std::string, Mix_Chunk*>::iterator it;
    it = smap.find(filename);
    if(it != smap.end()){
        return it->second;
    }else{
        Mix_Chunk* sample;
        sample = Mix_LoadWAV(filename);
        if(sample != nullptr){
            smap.insert({filename, sample});
            return sample;
        }
        
    }
    return nullptr;
}

void Game::LoadData(){
    Mix_Chunk *sample;
    sample = this->GetSound("Assets/Sounds/MusicStart.ogg");
    act = Mix_PlayChannel(-1, sample, 0);
    
    Actor* t = new Actor(this);
    TiledBGComponent* tb = new TiledBGComponent(t);
    tb->LoadTileCSV("Assets/Map/Tiles.csv", 32, 32);
    tb->SetTexture(GetTexture("Assets/Map/Tiles.png"));
    PathFinder* p = new PathFinder(this);
    pf = p;
    CreatePlayer("Assets/Map/Objects.csv");
    
}

void Game::CreatePlayer(std::string file){
    std::ifstream infile(file);
    std::string line;
    std::string word;
    float pos_x;
    float pos_y;
    while (std::getline(infile, line)){
        std::vector<std::string> row;
        std::istringstream ss(line);
        while (std::getline(ss, word, ',')) {
            row.push_back(word);
        }
        if(row[0] != "Type"){
            pos_x = (std::stof(row[1]) + 0.5f*std::stof(row[3]));
            pos_y = (std::stof(row[2]) + 0.5f*std::stof(row[4]));
        }
        if(row[0] == "Player"){
            Player* p = new Player(this);
            const Vector2 v2(pos_x, pos_y);
            p->SetPosition(v2);
            pl = p;
        }else if(row[0] == "Collider"){
            Collider* c = new Collider(this, std::stof(row[3]), std::stof(row[4]));
            const Vector2 v2(pos_x, pos_y);
            c->SetPosition(v2);
            cvec.push_back(c);
        }else if(row[0] == "Bush"){
            Bush* b = new Bush(this);
            const Vector2 v2(pos_x, pos_y);
            b->SetPosition(v2);
        }else if(row[0] == "Soldier"){
            Soldier* s = new Soldier(this, pf->GetPathNode(static_cast<size_t>(std::stof(row[5])), static_cast<size_t>(std::stof(row[6]))), pf->GetPathNode(static_cast<size_t>(std::stof(row[7])), static_cast<size_t>(std::stof(row[8]))));
            const Vector2 v2(pos_x, pos_y);
            s->SetPosition(v2);
        }
        
    }
}
