#pragma once

// TODO
#include "SDL2/SDL.h"
#include <vector>
#include <unordered_map>
#include <string>
#include "Random.h"
#include "SDL2/SDL_mixer.h"

class Actor;
class SpriteComponent;
class Block;
class Player;
class Goomba;
class Collider;
class PathFinder;
class EnemyComponent;
class Game{
public:
    std::vector<Actor*> actors;
    std::unordered_map<std::string, SDL_Texture*> umap;
    std::unordered_map<std::string, Mix_Chunk*> smap;
    void AddSprite(SpriteComponent* sc);
    void RemoveSprite(SpriteComponent* sc);
    bool n;
    std::vector<Block*> bvec;
    std::vector<Block*> const &getter() const { return bvec; }
    std::vector<Collider*> cvec;
    std::vector<Collider*> const &getterc() const { return cvec; }
    Vector2 camera;
    bool first = true;
    std::vector<EnemyComponent*> evec;
    std::vector<EnemyComponent*> const &gettere() const { return evec; }
    void AddEnemy(EnemyComponent* ec);
    void RemoveEnemy(EnemyComponent* ec);
    Game();
    bool Initialize();
    void Shutdown();
    void RunLoop();
    void AddActor(Actor* a);
    void RemoveActor(Actor* a);
    SDL_Texture* GetTexture(std::string f);
    Mix_Chunk* GetSound(const char* filename);
    Vector2& GetCameraPos();
    void CreatePlayer(std::string file);
    PathFinder* Getpf() { return pf; }
private:
    Player* pl;
    int act;
    std::vector<SpriteComponent*> scvec;
    int speed;
    SDL_Point velocity;
    unsigned int previous_time;
    SDL_Window* window;
    SDL_Renderer* renderer;
    void ProcessInput();
    void UpdateGame();
    void GenerateOuput();
    void LoadData();
    void UnloadData();
    PathFinder* pf;
    
    
};



