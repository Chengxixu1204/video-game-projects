#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"
#include <unordered_map>
#include <string>
#include <vector>
#include "Math.h"
#include <queue>



class Player;
class Block;
class Enemy;
class Checkpoint;
class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	Mix_Chunk* GetSound(const std::string& fileName);

	class Renderer* GetRenderer() {	return mRenderer; }
    
    const float WINDOW_WIDTH = 1024.0f;
    const float WINDOW_HEIGHT = 768.0f;
    
    void AddBlock(Block* blk);
    void RemoveBlock(Block* blk);
    
    
    
    Player* Getpl() {return pl;}
    
    void setmlevel(std::string l){mNextLevel = l;}
    
    std::queue<Checkpoint*>& getallcheckpoint(){return allcheck;}
    
    std::vector<Actor*>& getallblocks(){return bvec;}
    
    void SetPl(Player* p){pl = p;}
private:
    std::queue<Checkpoint*> allcheck;
    std::vector<Actor*> bvec;
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();

	std::unordered_map<std::string, Mix_Chunk*> mSounds;

	// All the actors in the game
	std::vector<class Actor*> mActors;

	class Renderer* mRenderer = nullptr;

	Uint32 mTicksCount = 0;
    
	bool mIsRunning;
    
    Player* pl;
    
    std::string mNextLevel = "";
    
    void LoadNextLevel();
    

    void LoadBlocks(const char* filename, int n);
};
