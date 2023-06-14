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
class Texture;
class SecurityCamera;
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
    
    Player* pl;
    
    std::string mNextLevel = "";
    
    void LoadNextLevel();
    
    int coinnum = 0;
    
    Texture* mCheckText;
    
    std::vector<SecurityCamera*> allcam;
    
    float counttime = 0.0f;
    
    void setmlevel(std::string l){mNextLevel = l;}
    
    std::queue<Checkpoint*> allcheck;
    
    Player* Getpl() {return pl;}
    
    std::vector<Actor*> bvec;
    
    void AddBlock(Block* blk);
    void RemoveBlock(Block* blk);
    
    void AddCam(SecurityCamera* sc);
    void RemoveCam(SecurityCamera* sc);
    
    void LoadBlocks(const char* filename, int n);
private:
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
};
