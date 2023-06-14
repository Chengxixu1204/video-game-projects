#pragma once


#include "SDL2/SDL.h"
class Game{
    public:
    Game();
    bool Initialize();
    void Shutdown();
    void RunLoop();
    
    private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Point point;
    SDL_Point center;
    int speed;
    SDL_Point velocity;
    unsigned int updown;
    unsigned int previous_time;
    bool status;
    void ProcessInput();
    void UpdateGame();
    void GenerateOuput();
};



