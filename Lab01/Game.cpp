//
//  Game.cpp
//  Game-mac
//
//  Created by Sanjay Madhav on 5/31/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "Game.h"
const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;
const int WALL_THICKNESS = 30;
const int PADDLE_HEIGHT = 80;

Game::Game(){
    point = {0, WINDOW_HEIGHT/2};
    center = {WINDOW_WIDTH/2, WINDOW_HEIGHT/2};
    updown = 0;
    status = true;
    previous_time = 0;
    speed = 1000;
    window = NULL;
    renderer = NULL;
    velocity = {320, 320};
}
bool Game::Initialize(){
    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) == 0){
        window = SDL_CreateWindow(
               "Lab1",                  // window title
               SDL_WINDOWPOS_UNDEFINED,           // initial x position
               SDL_WINDOWPOS_UNDEFINED,           // initial y position
               WINDOW_WIDTH,                               // width, in pixels
               WINDOW_HEIGHT,                              // height, in pixels
               0
        );
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
        //check if the initialization is valid
        if((window == NULL)||(renderer == NULL)){
            return false;
        }
        return true;
        
    };
    return false;
}

void Game::RunLoop(){
    //game loop
    while(status){
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
                status = false;
                break;
        }
    }
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    //escape end game
    if (state[SDL_SCANCODE_ESCAPE]) {
        status = false;
    }else if(state[SDL_SCANCODE_UP]){
        updown = 1;           //upward
    }else if(state[SDL_SCANCODE_DOWN]){
        updown = 2;           //downward
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
    //check if paddle move up
    if(updown == 1){
        point.y -= (int)(speed*dtime);
        updown = 0;
        if(point.y < WALL_THICKNESS + PADDLE_HEIGHT/2){
            point.y = WALL_THICKNESS + PADDLE_HEIGHT/2;
        }
    //check if paddle move down
    }else if(updown == 2){
        point.y += (int)(speed*dtime);
        updown = 0;
        if(point.y > WINDOW_HEIGHT - WALL_THICKNESS - PADDLE_HEIGHT/2){
            point.y = WINDOW_HEIGHT - WALL_THICKNESS - PADDLE_HEIGHT/2;
        }
    }
    
    //deal with the bouncing of balls
    center.x += (int)(velocity.x*dtime);
    center.y += (int)(velocity.y*dtime);
    
    //cases for right, up and down walls
    if(center.y <= WALL_THICKNESS){
        center.y = WALL_THICKNESS + 5;
        velocity.y = -velocity.y;
    }else if(center.y >= WINDOW_HEIGHT - WALL_THICKNESS){
        center.y = WINDOW_HEIGHT - WALL_THICKNESS - 5;
        velocity.y = -velocity.y;
    }else if(center.x >= WINDOW_WIDTH - WALL_THICKNESS){
        center.x = WINDOW_WIDTH - WALL_THICKNESS - 5;
        velocity.x = -velocity.x;
    
    }else if(((center.y >= point.y - PADDLE_HEIGHT/2) &&(center.y <= point.y + PADDLE_HEIGHT/2)) && (center.x <=15)){
        velocity.x = -velocity.x;
    }
    if(center.x <= 0){
        status = false;
    }
    
    
    
}

void Game::GenerateOuput(){
    //background setup
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 225, 225, 255, 255);
    
    //create walls
    SDL_Rect rect1;
    SDL_Rect rect2;
    SDL_Rect rect3;
    rect1.x = 0;
    rect1.y = 0;
    rect1.w = WINDOW_WIDTH;
    rect1.h = WALL_THICKNESS;
    
    rect2.x = WINDOW_WIDTH - WALL_THICKNESS;
    rect2.y = 0;
    rect2.w = WALL_THICKNESS;
    rect2.h = WINDOW_HEIGHT;
    
    rect3.x = 0;
    rect3.y = WINDOW_HEIGHT - WALL_THICKNESS;
    rect3.w = WINDOW_WIDTH;
    rect3.h = WALL_THICKNESS;
    //fill the wall
    SDL_RenderFillRect(renderer, &rect1);
    SDL_RenderFillRect(renderer, &rect2);
    SDL_RenderFillRect(renderer, &rect3);
    
    //create paddle
    SDL_Rect paddle;
    paddle.x = 0;
    paddle.y = point.y - PADDLE_HEIGHT/2;
    paddle.w = 20;
    paddle.h = PADDLE_HEIGHT;
    //fill the paddle
    SDL_RenderFillRect(renderer, &paddle);
    
    //create the ball
    SDL_Rect ball;
    ball.x = center.x - 5;
    ball.y = center.y - 5;
    ball.w = 10;
    ball.h = 10;
    
    //fill the ball
    SDL_RenderFillRect(renderer, &ball);
    SDL_RenderPresent(renderer);
}

void Game::Shutdown(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
