#include "PlayerUI.h"
#include "Texture.h"
#include "Shader.h"
#include "Game.h"
#include "Renderer.h"
#include "Actor.h"
#include "Player.hpp"
#include "VehicleMove.hpp"
#include "PlayerMove.hpp"
#include "Enemy.hpp"
#include "EnemyMove.hpp"

PlayerUI::PlayerUI(Actor* owner)
	:UIComponent(owner)
{
	Renderer* r = owner->GetGame()->GetRenderer();
	mLapTextures = std::vector<Texture*>{
		r->GetTexture("Assets/UI/Lap1.png"),
		r->GetTexture("Assets/UI/Lap2.png"),
		r->GetTexture("Assets/UI/Lap3.png"),
		r->GetTexture("Assets/UI/FinalLap.png"),
	};
	
	mFirstTexture = r->GetTexture("Assets/UI/1st.png");
	mSecondTexture = r->GetTexture("Assets/UI/2nd.png");
	
	mGoTexture = r->GetTexture("Assets/UI/Go.png");
	mReadyTexture = r->GetTexture("Assets/UI/Ready.png");
}

void PlayerUI::Update(float deltaTime)
{
	mGoDisplayTimer -= deltaTime;
	mLapDisplayTimer -= deltaTime;
}

void PlayerUI::Draw(Shader* shader)
{
	if (mGoDisplayTimer > 0.0f)
	{
		if (mOwner->GetState() == ActorState::Paused)
		{
			DrawTexture(shader, mReadyTexture, Vector2(0.0f, 100.0f));
		}
		else if (mOwner->GetState() == ActorState::Active)
		{
			DrawTexture(shader, mGoTexture, Vector2(0.0f, 100.0f));
		}
	}
	
	if (mLapDisplayTimer > 0.0f)
	{
		DrawTexture(shader, mLapTextures[mLapIndex], Vector2(0.0f, 200.0f), 0.75f);
	}
	
	if (mRaceState == Won)
	{
		DrawTexture(shader, mFirstTexture, Vector2(0.0f, 100.0f));
	}
	else if (mRaceState == Lost)
	{
		DrawTexture(shader, mSecondTexture, Vector2(0.0f, 100.0f));
	}
	
	// Figure out what place to show
	if (mOwner->GetState() == ActorState::Active)
	{
		bool inFirst = IsPlayerInFirst();
		if (inFirst)
		{
			DrawTexture(shader, mFirstTexture, Vector2(400.0f, 320.0f), 0.5f);
		}
		else
		{
			DrawTexture(shader, mSecondTexture, Vector2(400.0f, 320.0f), 0.5f);
		}
	}
}

void PlayerUI::OnLapChange(int lapNum)
{
	mLapIndex = lapNum - 1;
	mLapDisplayTimer = 3.0f;
}

bool PlayerUI::IsPlayerInFirst() const
{
    if(mOwner->GetGame()->Getpl()->Player_Mov->Current_lap < mOwner->GetGame()->Enemy_ene->Ene_mov->Current_lap){
        return false;
    }else{
        if(mOwner->GetGame()->Getpl()->Player_Mov->Current_lap > mOwner->GetGame()->Enemy_ene->Ene_mov->Current_lap){
            return true;
        }else{
            if(mOwner->GetGame()->Getpl()->Player_Mov->Last_check < mOwner->GetGame()->Enemy_ene->Ene_mov->Last_check){
                return false;
            }else if(mOwner->GetGame()->Getpl()->Player_Mov->Last_check > mOwner->GetGame()->Enemy_ene->Ene_mov->Last_check){
                return true;
            }else{
                float Play_dis = mOwner->GetGame()->Getpl()->Player_Mov->DisToNext();
                float Ene_dis = mOwner->GetGame()->Enemy_ene->Ene_mov->DisToNext();
                if(Play_dis < Ene_dis){
                    return true;
                }else{
                    return false;
                }
            }
        }
    }
    
}

