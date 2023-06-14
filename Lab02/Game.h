#pragma once


#include "SDL2/SDL.h"
#include <vector>
#include <unordered_map>
#include <string>
#include "Random.h"
const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;
class Actor;
class SpriteComponent;
class Asteroid;
class Game{
public:
    Game();
    bool Initialize();
    void Shutdown();
    void RunLoop();
    void RemoveActor(Actor* a);
    void AddActor(Actor* a);
    std::vector<Asteroid*> asv;
    SDL_Texture* GetTexture(std::string f);
    void AddSprite(SpriteComponent* sc);
    void RemoveSprite(SpriteComponent* sc);
    void AddAsteroid(Asteroid* as);
    void RemoveAsteroid(Asteroid* as);
protected:
    SDL_Window* window;
    SDL_Renderer* renderer;
    unsigned int previous_time;
    std::vector<Actor*> actors;
    std::unordered_map<std::string, SDL_Texture*> umap;
    std::vector<SpriteComponent*> scvec;
    bool rungame;
    void ProcessInput();
    void UpdateGame();
    void GenerateOuput();
    void LoadData();
    void UnloadData();
};



