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
#include <algorithm>
#include "MeshComponent.h"
#include "HeightMap.hpp"
#include "Enemy.hpp"

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
    Game_start -= deltaTime;
    if(First_time && Game_start <= 0){
        Start_time = Mix_PlayChannel(-1, GetSound("Assets/Sounds/Music.ogg"), -1);
        Player_pl->SetState(ActorState::Active);
        Enemy_ene->SetState(ActorState::Active);
        First_time = false;
    }
}

void Game::GenerateOutput()
{
	// TODO: tell renderer to draw
    mRenderer->Draw();
}

void Game::LoadData()
{
    Matrix4 projection = Matrix4::CreatePerspectiveFOV(1.22f, WINDOW_WIDTH, WINDOW_HEIGHT, 10.0f, 10000.0f);
    mRenderer->SetProjectionMatrix(projection);
    Matrix4 view = Matrix4::CreateLookAt(Vector3(-300, 0, 0), Vector3(20, 0, 0), Vector3::UnitZ);
    mRenderer->SetViewMatrix(view);
    HeightMap* h = new HeightMap();
    Height_map = h;
    Player* p = new Player(this);
    Player_pl = p;
    Actor* a = new Actor(this);
    a->SetRotation(Math::Pi);
    MeshComponent* mc = new MeshComponent(a);
    mc->SetMesh(GetRenderer()->GetMesh("Assets/Track.gpmesh"));
    Enemy* e = new Enemy(this);
    Enemy_ene = e;
    Player_pl->SetState(ActorState::Paused);
    Enemy_ene->SetState(ActorState::Paused);
    GetSound("Assets/Sounds/RaceStart.wav");
    GetSound("Assets/Sounds/Music.ogg");
    GetSound("Assets/Sounds/FinalLap.wav");
    GetSound("Assets/Sounds/MusicFast.ogg");
    GetSound("Assets/Sounds/Won.wav");
    GetSound("Assets/Sounds/Lost.wav");
    Mix_PlayChannel(-1, GetSound("Assets/Sounds/RaceStart.wav"), 0);
    Start_time = Mix_PlayChannel(-1, GetSound("Assets/Sounds/Music.ogg"), -1);
    Mix_HaltChannel(Start_time);
    
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
