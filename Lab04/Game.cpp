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
#include "Block.hpp"
#include "Player.hpp"
#include "Spawner.hpp"
#include <SDL2/SDL_image.h>
#include <algorithm>
#include <fstream>

// TODO
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
               600,                               // width, in pixels
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

void Game::AddBlock(Block* b){
    bvec.push_back(b);
}


void Game::RemoveBlock(Block* b){
    std::vector<Block*>::iterator position = std::find(bvec.begin(), bvec.end(), b);
    if (position != bvec.end())
        bvec.erase(position);
}
void Game::AddGoomba(Goomba* gm){
    gvec.push_back(gm);
}


void Game::RemoveGoomba(Goomba* gm){
    std::vector<Goomba*>::iterator position = std::find(gvec.begin(), gvec.end(), gm);
    if (position != gvec.end())
        gvec.erase(position);
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
    Mix_Chunk *sample;
    sample = Mix_LoadWAV("Assets/Sounds/Music.ogg");
    music = Mix_PlayChannel(-1, sample, -1);
    Actor* t = new Actor(this);
    const Vector2 v2(3392.0f, 224.0f);
    t->SetPosition(v2);
    SpriteComponent* sc1 = new SpriteComponent(t, 80);
    sc1->SetTexture(GetTexture("Assets/Background.png"));
    std::string line;
    unsigned int count = 0;
    std::ifstream infile("Assets/Level1.txt");
    while (std::getline(infile, line)) {
        for(unsigned int i = 0; i < line.size(); i++){
            if((line[i] == 'A') || (line[i] == 'B') || (line[i] == 'C') ||
                (line[i] == 'D') || (line[i] == 'E') || (line[i] == 'F') ||
               (line[i] == 'G') || (line[i] == 'H') || (line[i] == 'I')){
                Block* blk = new Block(this, line[i]);
                const Vector2 h(16+32*i, 16+32*count);
                blk->SetPosition(h);
            }else if(line[i] == 'P'){
                Player* p = new Player(this);
                const Vector2 h(16+32*i, 16+32*count);
                p->SetPosition(h);
                pl = p;
            }else if(line[i] == 'Y'){
                Spawner* sp = new Spawner(this);
                const Vector2 h(16+32*i, 16+32*count);
                sp->SetPosition(h);
            }
        }
        count++;
    }
}

Mix_Chunk* Game::GetSound(char *filename){
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
