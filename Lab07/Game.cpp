//
//  Game.cpp
//  Game-mac
//
//  Created by Sanjay Madhav on 5/31/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "Game.h"
#include <algorithm>
#include "Actor.h"
#include <fstream>
#include "Renderer.h"
#include "Random.h"
#include "Player.hpp"
#include "SideBlock.hpp"
#include "Block.hpp"
#include <algorithm>

Game::Game()
:mIsRunning(true)
{
	
}

bool Game::Initialize()
{
	Random::Init();

	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	// TODO: Create renderer
    Renderer* r = new Renderer(this);
    mRenderer = r;
    if(!mRenderer->Initialize(WINDOW_WIDTH, WINDOW_HEIGHT)){
        SDL_Log("false initialization");
        return false;
    }

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	LoadData();

	mTicksCount = SDL_GetTicks();
	
	return true;
}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				mIsRunning = false;
				break;
		}
	}
	
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}

	for (auto actor : mActors)
	{
		actor->ProcessInput(state);
	}
}

void Game::AddBlock(Block* b){
    bvec.push_back(b);
}


void Game::RemoveBlock(Block* b){
    std::vector<Block*>::iterator position = std::find(bvec.begin(), bvec.end(), b);
    if (position != bvec.end())
        bvec.erase(position);
}

void Game::UpdateGame()
{
	// Compute delta time
	// Wait until 16ms has elapsed since last frame
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
		;

	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	if (deltaTime > 0.01667f)
	{
		deltaTime = 0.01667f;
	}
	mTicksCount = SDL_GetTicks();
	
	// Make copy of actor vector
	// (iterate over this in case new actors are created)
	std::vector<Actor*> copy = mActors;
	// Update all actors
	for (auto actor : copy)
	{
		actor->Update(deltaTime);
	}

	// Add any actors to destroy to a temp vector
	std::vector<Actor*> destroyActors;
	for (auto actor : mActors)
	{
		if (actor->GetState() == ActorState::Destroy)
		{
			destroyActors.emplace_back(actor);
		}
	}

	// Delete the destroyed actors (which will
	// remove them from mActors)
	for (auto actor : destroyActors)
	{
		delete actor;
	}
    if(pl->GetState() == ActorState::Paused){
        Mix_HaltChannel(live);
    }
    if(fff){
        if(pl->slevel > 1 || pl->GetState() == ActorState::Paused){
           Mix_HaltChannel(alert);
            fff = false;
        }
        
    }
    

}

void Game::GenerateOutput()
{
	// TODO: tell renderer to draw
    mRenderer->Draw();
}

void Game::LoadData()
{

    always = Mix_PlayChannel(-1, this->GetSound("Assets/Sounds/Music.ogg"), -1);
    live = Mix_PlayChannel(-1, this->GetSound("Assets/Sounds/ShipLoop.ogg"), -1);
    alert = Mix_PlayChannel(-1, GetSound("Assets/Sounds/DamageAlert.ogg"), -1);
    Mix_HaltChannel(alert);
    Player* p = new Player(this);
    pl = p;
    Matrix4 projection = Matrix4::CreatePerspectiveFOV(1.22f, WINDOW_WIDTH, WINDOW_HEIGHT, 10.0f, 10000.0f);
    mRenderer->SetProjectionMatrix(projection);
    Matrix4 view = Matrix4::CreateLookAt(Vector3(-300, 0, 0), Vector3(20, 0, 0), Vector3::UnitZ);
    mRenderer->SetViewMatrix(view);
    
}

void Game::LoadBlocks(const char *filename, int n){
        std::string line;
        unsigned int count = 0;
        std::ifstream infile(filename);
        while (std::getline(infile, line)) {
            for(size_t i = 0; i < line.size(); i++){
                if(line[i] == 'A'){
                    Block* bl = new Block(this, 3);
                    bl->SetPosition(Vector3(n*1000, -237.5f + 25.0f*i, 237.5f - 25.0f*count));
                }else if(line[i] == 'B'){
                    Block* bl = new Block(this, 4);
                    bl->SetPosition(Vector3(n*1000, -237.5f + 25.0f*i, 237.5f - 25.0f*count));
                }
            }
            count++;
        }
    
}

void Game::UnloadData()
{
	// Delete actors
	// Because ~Actor calls RemoveActor, have to use a different style loop
	while (!mActors.empty())
	{
		delete mActors.back();
	}

	// Destroy sounds
	for (auto s : mSounds)
	{
		Mix_FreeChunk(s.second);
	}
	mSounds.clear();
}

Mix_Chunk* Game::GetSound(const std::string& fileName)
{
	Mix_Chunk* chunk = nullptr;
	auto iter = mSounds.find(fileName);
	if (iter != mSounds.end())
	{
		chunk = iter->second;
	}
	else
	{
		chunk = Mix_LoadWAV(fileName.c_str());
		if (!chunk)
		{
			SDL_Log("Failed to load sound file %s", fileName.c_str());
			return nullptr;
		}

		mSounds.emplace(fileName, chunk);
	}
	return chunk;
}

void Game::Shutdown()
{
	UnloadData();
	Mix_CloseAudio();
	// TODO: Delete renderer
    mRenderer->Shutdown();
    delete mRenderer;
	SDL_Quit();
}

void Game::AddActor(Actor* actor)
{
	mActors.emplace_back(actor);
}

void Game::RemoveActor(Actor* actor)
{
	auto iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		// Swap to end of vector and pop off (avoid erase copies)
		auto iter2 = mActors.end() - 1;
		std::iter_swap(iter, iter2);
		mActors.pop_back();
	}
}
