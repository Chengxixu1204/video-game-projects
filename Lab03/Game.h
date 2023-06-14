#pragma once

// TODO
#include "SDL2/SDL.h"
#include <vector>
#include <unordered_map>
#include <string>
#include "Random.h"
#include "Frog.hpp"
#include "Log.hpp"
class Actor;
class SpriteComponent;
class Asteroid;
class Vehicle;
class Frog;
class Log;

const int WINDOW_WIDTH = 448.0f;
const int WINDOW_HEIGHT = 512.0f;
class Game{
public:
    SDL_Texture* GetTexture(std::string f);
    std::vector<SpriteComponent*> scvec;
    void AddSprite(SpriteComponent* sc);
    void RemoveSprite(SpriteComponent* sc);
    std::vector<Asteroid*> asv;
    void AddVehicle(Vehicle* v);
    void RemoveVehicle(Vehicle* v);
    void AddLog(Log* v);
    void RemoveLog(Log* v);
    Frog* fg;
    Actor* goal;
    void SetFrog(Frog* f);
    bool n;
    Game();
    bool Initialize();
    void Shutdown();
    void RunLoop();
    void AddActor(Actor* a);
    void RemoveActor(Actor* a);
    std::vector<Vehicle*> vecv;
    std::vector<Log*> logv;
    std::vector<Vehicle*> const &getterv() const { return vecv; }
    std::vector<Log*> const &getterl() const { return logv; }
private:
    void LoadData();
    void UnloadData();
    void ProcessInput();
    void UpdateGame();
    void GenerateOuput();
    SDL_Window* window;
    SDL_Renderer* renderer;
    int speed;
    SDL_Point velocity;
    unsigned int previous_time;
    std::vector<Actor*> actors;
    std::unordered_map<std::string, SDL_Texture*> umap;
    
};



