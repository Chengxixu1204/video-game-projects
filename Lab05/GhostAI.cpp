#include "GhostAI.h"
#include "Actor.h"
#include "Game.h"
#include "CollisionComponent.h"
#include "Game.h"
#include "PathNode.h"
#include "AnimatedSprite.h"
#include <SDL2/SDL.h>
#include <unordered_map>
#include "Ghost.h"
#include "PacMan.h"
#include "Random.h"
#include <limits>

const float MIN = Math::Infinity;

GhostAI::GhostAI(class Actor* owner)
:Component(owner, 50)
{
	mGhost = static_cast<Ghost*>(owner);
}

void GhostAI::Update(float deltaTime)
{
    timestamp += deltaTime;
    int speed = 0;
    if(mState == Scatter || mState == Chase){
        speed = 90;
    }else if(mState == Frightened){
        speed = 65;
        if(timestamp <= 5.0f){
            mGhost->GetComponent<AnimatedSprite>()->SetAnimation("scared0");
        }else{
            mGhost->GetComponent<AnimatedSprite>()->SetAnimation("scared1");
        }
    }else{
        speed = 125;
    }
    mGhost->SetPosition(mGhost->GetPosition() + speed*deltaTime*curdirect);
	if(mGhost->GetComponent<CollisionComponent>()->Intersect(mNextNode->GetComponent<CollisionComponent>())){
            mGhost->SetPosition(mNextNode->GetPosition());
        ChangeState();
        UpdateState();
        UpdateNode();
        UpdateDir();
        UpdateAnimation();
    }
       
}


void GhostAI::Frighten()
{
	
    if(mState != Dead){
        timestamp = 0.0f;
        if(mState != Frightened){
            mState = Frightened;
            PathNode* temp = mPrevNode;
            mPrevNode = mNextNode;
            mNextNode = temp;
            UpdateDir();
            mTargetNode = nullptr;
        }
    }
}

void GhostAI::Start(PathNode* startNode)
{
	
    mGhost->SetPosition(startNode->GetPosition());
    mState = Scatter;
    mPrevNode = nullptr;
    mNextNode = startNode;
    timestamp = 0.0f;
}

void GhostAI::Die()
{
	
    timestamp = 0.0f;
    mState = Dead;
    UpdateDir();
}

void GhostAI::DebugDrawPath(SDL_Renderer* render)
{
	// Draw a rectangle at the target node
	if (mTargetNode != nullptr)
	{
		const int SIZE = 16;
		SDL_Rect r;
		r.x = static_cast<int>(mTargetNode->GetPosition().x) - SIZE / 2;
		r.y = static_cast<int>(mTargetNode->GetPosition().y) - SIZE / 2;
		r.w = SIZE;
		r.h = SIZE;
		SDL_RenderDrawRect(render, &r);
	}
	
	// Line from ghost to next node
	if (mNextNode != nullptr)
	{
		SDL_RenderDrawLine(render,
			static_cast<int>(mOwner->GetPosition().x),
			static_cast<int>(mOwner->GetPosition().y),
			static_cast<int>(mNextNode->GetPosition().x),
			static_cast<int>(mNextNode->GetPosition().y));
	}
}

void GhostAI::UpdateState(){
    if(mState == Scatter){
        mTargetNode = mGhost->GetScatterNode();
    }else if(mState == Frightened){
        std::vector<PathNode*> list1;
        std::vector<PathNode*> list2;
        std::vector<PathNode*> list3;
        for(unsigned int i = 0; i < mNextNode->mAdjacent.size(); i++){
            if((mNextNode->mAdjacent[i] != mPrevNode) && (mNextNode->mAdjacent[i]->GetType() != PathNode::Ghost) && (mNextNode->mAdjacent[i]->GetType() != PathNode::Tunnel)){
                list1.push_back(mNextNode->mAdjacent[i]);
            }
        }
        if(list1.size() != 0){
            int index = Random::GetIntRange(0, list1.size()-1);
            mTargetNode = list1[index];
        }else{
            for(unsigned int i = 0; i < mNextNode->mAdjacent.size(); i++){
                if((mNextNode->mAdjacent[i] != mPrevNode) && (mNextNode->mAdjacent[i]->GetType() != PathNode::Tunnel)){
                    list2.push_back(mNextNode->mAdjacent[i]);
                }
            }
            if(list2.size() != 0){
                int index = Random::GetIntRange(0, list2.size()-1);
                mTargetNode = list2[index];
            }else{
                for(unsigned int i = 0; i < mNextNode->mAdjacent.size(); i++){
                    list1.push_back(mNextNode->mAdjacent[i]);
                }
                int index = Random::GetIntRange(0, list3.size()-1);
                mTargetNode = list3[index];
            }
        }
    }else if(mState == Dead){
        mTargetNode = mGhost->GetGame()->mGhostPen;
        
    }else if(mState == Chase){
        if(mGhost->GetType() == Ghost::Blinky){
            if(mGhost->GetGame()->mPlayer->GetPrevNode()->GetType() != PathNode::Tunnel){
                mTargetNode = mGhost->GetGame()->mPlayer->GetPrevNode();
            }else{
                mTargetNode = FindShortest(mGhost->GetGame()->mPlayer->GetPosition());
            }
        }else if(mGhost->GetType() == Ghost::Pinky){
            Vector2 postion = mGhost->GetGame()->mPlayer->GetPointInFrontOf(80);
            mTargetNode = FindShortest(postion);
        }else if(mGhost->GetType() == Ghost::Inky){
            Vector2 postion = mGhost->GetGame()->mPlayer->GetPointInFrontOf(40);
            Vector2 tep = findvector(postion, mGhost->GetGame()->mGhosts[0]->GetPosition());
            Vector2 posQ = mGhost->GetGame()->mGhosts[0]->GetPosition() + 2*tep;
            mTargetNode = FindShortest(posQ);
        }else if(mGhost->GetType() == Ghost::Clyde){
            float dis = Posdistance(mGhost->GetPosition(), mGhost->GetGame()->mPlayer->GetPosition());
            if(dis > 150.0f){
                if(mGhost->GetGame()->mPlayer->GetPrevNode()->GetType() != PathNode::Tunnel){
                    mTargetNode = mGhost->GetGame()->mPlayer->GetPrevNode();
                }else{
                    mTargetNode = FindShortest(mGhost->GetGame()->mPlayer->GetPosition());
                }
            }else{
                mTargetNode = mGhost->GetSpawnNode();
            }
        }
    }
}

void GhostAI::UpdateNode(){
    float mindis = MIN;
    PathNode* nnode = nullptr;
    for(unsigned int i = 0; i < mNextNode->mAdjacent.size(); i++){
        if(((mNextNode->mAdjacent[i] != mPrevNode) && (mNextNode->mAdjacent[i]->GetType() != PathNode::Ghost) && (mNextNode->mAdjacent[i]->GetType() != PathNode::Tunnel)) || ((mState == Dead) && (mNextNode->mAdjacent[i] != mPrevNode) && (mNextNode->mAdjacent[i]->GetType() != PathNode::Tunnel))){
            float temp = Caldistance(mNextNode->mAdjacent[i], mTargetNode);
            if(temp < mindis){
                mindis = temp;
                nnode = mNextNode->mAdjacent[i];
            }
        }
    }
    if(nnode == nullptr){
        mindis = MIN;
        for(unsigned int i = 0; i < mNextNode->mAdjacent.size(); i++){
            if((mNextNode->mAdjacent[i] != mPrevNode) && (mNextNode->mAdjacent[i]->GetType() != PathNode::Tunnel)){
                float temp = Caldistance(mNextNode->mAdjacent[i], mTargetNode);
                if(temp < mindis){
                    mindis = temp;
                    nnode = mNextNode->mAdjacent[i];
                }
            }
        }
    }else{
       mPrevNode = mNextNode;
       mNextNode = nnode;
        return;
    }
    if(nnode == nullptr){
        mindis = MIN;
        for(unsigned int i = 0; i < mNextNode->mAdjacent.size(); i++){
            if( (mNextNode->mAdjacent[i]->GetType() != PathNode::Tunnel)){
                float temp = Caldistance(mNextNode->mAdjacent[i], mTargetNode);
                if(temp < mindis){
                    mindis = temp;
                    nnode = mNextNode->mAdjacent[i];
                }
            }
        }
    }else{
        mNextNode = nnode;
    }
    mPrevNode = mNextNode;
    return;
    
}

float GhostAI::Caldistance(PathNode *a, PathNode *b){
    return(Vector2::Distance(a->GetPosition(), b->GetPosition()));
}

float GhostAI::Posdistance(Vector2 a, Vector2 b){
    return(Vector2::Distance(a, b));
}

void GhostAI::UpdateDir(){
     curdirect = Vector2((mNextNode->GetPosition().x - mPrevNode->GetPosition().x), (mNextNode->GetPosition().y - mPrevNode->GetPosition().y));
     curdirect = Vector2(curdirect.x/Caldistance(mNextNode, mPrevNode), curdirect.y/Caldistance(mNextNode, mPrevNode));
    
}

void GhostAI::ChangeState(){
    if(mState == Frightened && timestamp >= 7.0f){
        mState = Scatter;
        timestamp = 0.0f;
    }else if(mState == Dead && ((mGhost->GetPosition().x == mGhost->GetGame()->mGhostPen->GetPosition().x) && (mGhost->GetPosition().y == mGhost->GetGame()->mGhostPen->GetPosition().y))){
        mState = Scatter;
        timestamp = 0.0f;
    }else if(mState == Scatter && timestamp >= 5.0f){
        mState = Chase;
        timestamp = 0.0f;
    }else if(mState == Chase && timestamp >= 20.0f ){
        mState = Scatter;
        timestamp = 0.0f;
    }
}
Vector2 GhostAI::findvector(Vector2 a, Vector2 b){
    return(Vector2(a.x-b.x, a.y-b.y));
}

void GhostAI::UpdateAnimation(){
    AnimatedSprite* as = mGhost->GetComponent<AnimatedSprite>();
    if(mState == Scatter || mState == Chase){
        if(curdirect.x == 1.0f && curdirect.y == 0.0f){
            as->SetAnimation("right");
        }else if(curdirect.x == -1.0f && curdirect.y == 0.0f){
            as->SetAnimation("left");
        }else if(curdirect.x == 0.0f && curdirect.y == 1.0f){
            as->SetAnimation("down");
        }else if(curdirect.x == 0.0f && curdirect.y == -1.0f){
            as->SetAnimation("up");
        }
    }else if(mState == Dead){
        if(curdirect.x == 1.0f && curdirect.y == 0.0f){
            as->SetAnimation("deadright");
        }else if(curdirect.x == -1.0f && curdirect.y == 0.0f){
            as->SetAnimation("deadleft");
        }else if(curdirect.x == 0.0f && curdirect.y == 1.0f){
            as->SetAnimation("deaddown");
        }else if(curdirect.x == 0.0f && curdirect.y == -1.0f){
            as->SetAnimation("deadup");
        }
    }
}

PathNode* GhostAI::FindShortest(const Vector2 ve){
    float mindis = MIN;
    PathNode* nnode = nullptr;
    for(unsigned int i = 0; i < mGhost->GetGame()->mPathNodes.size(); i++){
        if(mGhost->GetGame()->mPathNodes[i]->GetType() == PathNode::Default){
            float temp = Posdistance(ve, mGhost->GetGame()->mPathNodes[i]->GetPosition());
            if(temp < mindis){
                mindis = temp;
                nnode = mGhost->GetGame()->mPathNodes[i];
            }
        }
    }
    return nnode;
}
