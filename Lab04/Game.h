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
class Game{
public:
    std::vector<Actor*> actors;
    std::unordered_map<std::string, SDL_Texture*> umap;
    std::unordered_map<std::string, Mix_Chunk*> smap;
    void AddSprite(SpriteComponent* sc);
    void RemoveSprite(SpriteComponent* sc);
    bool n;
    Player* pl;
    std::vector<Block*> bvec;
    std::vector<Goomba*> gvec;
    void AddBlock(Block* blk);
    void RemoveBlock(Block* blk);
    void AddGoomba(Goomba* gm);
    void RemoveGoomba(Goomba* gm);
    std::vector<Block*> const &getter() const { return bvec; }
    Vector2 camera;
    Game();
    bool Initialize();
    void Shutdown();
    void RunLoop();
    void AddActor(Actor* a);
    void RemoveActor(Actor* a);
    int music;
    SDL_Texture* GetTexture(std::string f);
    Mix_Chunk* GetSound(char* filename);
private:
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
    
    
};



