#include "SoldierAI.h"
#include "Actor.h"
#include "Game.h"
#include "PathFinder.h"
#include "PathNode.h"
#include "AnimatedSprite.h"
#include <algorithm>

SoldierAI::SoldierAI(Actor* owner)
:SpriteComponent(owner)
{
	SetIsVisible(false); // Uncomment to hide debug paths
}

void SoldierAI::Setup(PathNode* start, PathNode* end)
{
	// TODO: Implement
    mPatrolStart = start;
    mPatrolEnd = end;
    mOwner->GetGame()->Getpf()->CalculatePath(mPatrolStart, mPatrolEnd, mPath);
    mTarget = end;
    mPrev = start;
    mNext = mPath.back();
    mPath.pop_back();
    mNext = mPath.back();
    mPath.pop_back();
    getDir();
}

void SoldierAI::Update(float deltaTime)
{
	// TODO: Implement
    t += deltaTime;
    if(!isstunned){
        mOwner->SetPosition(mOwner->GetPosition() + curdirect*deltaTime*SOLDIER_SPEED);
        if(Vector2::Distance(mOwner->GetPosition(), mNext->GetPosition()) <= 1.0f){
            mOwner->SetPosition(mNext->GetPosition());
            if(mPath.size() != 0){
                mPrev = mNext;
                mNext = mPath.back();
                mPath.pop_back();
                getDir();
            }else{
                Setup(mPatrolEnd, mPatrolStart);
            }
        }
        updateAni();
    }
    if(isstunned && t > STUN_DURATION){
        isstunned = false;
    }
}

// This helper is to just debug draw the soldier's path to visualize it
// (only called if this component is set to visible)
void SoldierAI::Draw(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	Vector2 cameraPos = mOwner->GetGame()->GetCameraPos();
	
	// Draw from current position to next
	SDL_RenderDrawLine(renderer,
					   static_cast<int>(mOwner->GetPosition().x - cameraPos.x),
					   static_cast<int>(mOwner->GetPosition().y - cameraPos.y),
					   static_cast<int>(mNext->GetPosition().x - cameraPos.x),
					   static_cast<int>(mNext->GetPosition().y - cameraPos.y));

	// Draw from next to first node on path
	if (!mPath.empty())
	{
		// Draw from current position to next
		SDL_RenderDrawLine(renderer,
						   static_cast<int>(mNext->GetPosition().x - cameraPos.x),
						   static_cast<int>(mNext->GetPosition().y - cameraPos.y),
						   static_cast<int>(mPath.back()->GetPosition().x - cameraPos.x),
						   static_cast<int>(mPath.back()->GetPosition().y - cameraPos.y));
	}
	
	// Draw each node on the path
	if (mPath.size() > 1)
	{
		for (size_t i = 0; i < mPath.size() - 1; i++)
		{
			SDL_RenderDrawLine(renderer,
							   static_cast<int>(mPath[i]->GetPosition().x - cameraPos.x),
							   static_cast<int>(mPath[i]->GetPosition().y - cameraPos.y),
							   static_cast<int>(mPath[i + 1]->GetPosition().x - cameraPos.x),
							   static_cast<int>(mPath[i + 1]->GetPosition().y - cameraPos.y));
		}
	}
}

void SoldierAI::getDir(){
    curdirect = Vector2((mNext->GetPosition().x - mPrev->GetPosition().x), (mNext->GetPosition().y - mPrev->GetPosition().y));
    curdirect = Vector2(curdirect.x/Vector2::Distance(mNext->GetPosition(), mPrev->GetPosition()), curdirect.y/Vector2::Distance(mNext->GetPosition(), mPrev->GetPosition()));
}

void SoldierAI::updateAni(){
    if(curdirect.x == 1.0f && curdirect.y == 0.0f){
       mOwner->GetComponent<AnimatedSprite>()->SetAnimation("WalkRight");
    }else if(curdirect.x == -1.0f && curdirect.y == 0.0f){
        mOwner->GetComponent<AnimatedSprite>()->SetAnimation("WalkLeft");
    }else if(curdirect.x == 0.0f && curdirect.y == 1.0f){
        mOwner->GetComponent<AnimatedSprite>()->SetAnimation("WalkDown");
    }else if(curdirect.x == 0.0f && curdirect.y == -1.0f){
        mOwner->GetComponent<AnimatedSprite>()->SetAnimation("WalkUp");
    }
}

void SoldierAI::stunned(){

    t = 0.0f;
    isstunned = true;
}
