//
//  Game.cpp
//  Game-mac
//
//  Created by Sanjay Madhav on 5/31/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "Game.h"
#include "Actor.h"
#include "Ship.hpp"
#include "Asteroid.hpp"
#include "SpriteComponent.h"
#include <SDL2/SDL_image.h>
#include <algorithm>



Game::Game(){
    rungame = true;
    previous_time = 0;
}
bool Game::Initialize(){
    Random::Init();
    //create window and background
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
        IMG_Init(IMG_INIT_PNG);
        LoadData();
        return 1;
    };
    return 0;
}

void Game::RunLoop(){
    //game loop
    while(rungame){
        ProcessInput();
        UpdateGame();
        GenerateOuput();
    }
}

void Game::ProcessInput(){
    //process input with key state
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                rungame = false;
                break;
        }
    }
    const Uint8 *state = SDL_GetKeyboardState(nullptr);
    if (state[SDL_SCANCODE_ESCAPE]) {
        rungame = false;
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
    //destroy
    std::vector<Actor*> destroy;
    for(unsigned int i = 0; i < temp.size(); i++){
        if(temp[i]->GetState() == ActorState::Destroy){
            destroy.push_back(temp[i]);
        }
    }
    //destroy all
    for(unsigned int i = 0; i < destroy.size(); i++){
        delete(destroy[i]);
    }
}

void Game::GenerateOuput(){
    //draw output
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
    //delete all elements
    UnloadData();
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::UnloadData(){
    //create and upload actor
    while(actors.size() != 0){
        delete (actors.back());
    }
    std::unordered_map<std::string, SDL_Texture*>::iterator it;
    for(it = umap.begin(); it != umap.end(); it++){
        SDL_DestroyTexture(it->second);
    }
    umap.clear();
}
void Game::AddActor(Actor* a){
    actors.push_back(a);
}

void Game::AddAsteroid(Asteroid* as){
    asv.push_back(as);
}


void Game::RemoveActor(Actor* a){
    //remove actor from the vector
    std::vector<Actor*>::iterator position = std::find(actors.begin(), actors.end(), a);
    if (position != actors.end()) 
        actors.erase(position);
}
void Game::RemoveAsteroid(Asteroid* as){
    //remove asteriod
    std::vector<Asteroid*>::iterator position = std::find(asv.begin(), asv.end(), as);
    if (position != asv.end())
        asv.erase(position);
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
    //add sprite component
    scvec.push_back(sc);
    std::sort(scvec.begin(), scvec.end(),
        [](SpriteComponent* a, SpriteComponent* b) {
            return a->GetDrawOrder() < b->GetDrawOrder();
    });
}

void Game::RemoveSprite(SpriteComponent *sc){
    //remove sprite component
    std::vector<SpriteComponent*>::iterator position = std::find(scvec.begin(), scvec.end(), sc);
    if (position != scvec.end()) 
        scvec.erase(position);
}

void Game::LoadData(){
    //create background and asteroid and ship
    Actor* background = new Actor(this);
    const Vector2 v2(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
    background->SetPosition(v2);
    SpriteComponent* sc1 = new SpriteComponent(background, 80);
    sc1->SetTexture(GetTexture("Assets/Stars.png"));
    //create ship
    Ship* sh = new Ship(this);
    const Vector2 v3(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
    sh->SetPosition(v3);
    //create asteroids
    for(int i = 0; i < 10; i++){
        Asteroid* ast = new Asteroid(this);
    }
}
