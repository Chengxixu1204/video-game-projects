//
//  EnemyComponent.hpp
//  Lab06
//
//  Created by Chengxi Xu on 3/2/22.
//

#ifndef EnemyComponent_hpp
#define EnemyComponent_hpp

#include <stdio.h>
#include "Component.h"
#include "Actor.h"
#include "Game.h"
#include <functional>

class CollisionComponent;
class EnemyComponent : public Component{
public:
    EnemyComponent(class Actor* owner);
    ~EnemyComponent();
    CollisionComponent* cc;
    CollisionComponent* GetCollision() {return cc;}
    void SetDam(std::function<void()> a) { OnDamage = a;}
    void SetDea(std::function<void()> b) { OnDeath = b;}
    void Sethit(int n) {hitpoint = n;}
    void TakeDamage();
private:
    int hitpoint;
    int gethit() {return hitpoint;}
    void Update(float deltaTime) override;
    float time = 0.0f;
    std::function<void()> OnDamage;
    std::function<void()> OnDeath;
    
};

#endif /* EnemyComponent_hpp */
