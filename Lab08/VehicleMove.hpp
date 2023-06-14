//
//  VehicleMove.hpp
//  Lab08
//
//  Created by Chengxi Xu on 3/10/22.
//

#ifndef VehicleMove_hpp
#define VehicleMove_hpp

#include <stdio.h>
#include "Component.h"
#include "Actor.h"
#include "Game.h"
enum Type
{
    Right,
    Left,
    None
};
class VehicleMove : public Component
{
public:
    VehicleMove(class Actor* owner);
    ~VehicleMove();
    int Current_lap = 0;
    int Last_check = -1;
    float DisToNext();
    void Update(float deltaTime) override;
    void SetPre(bool n){Is_pressed = n;}
    void SetTurn(Type m){Ve_type = m;}
    int GetLap(){return Current_lap;}
private:
    bool Is_pressed = false;
    Type Ve_type = None;
    Vector3 Ve_velocity;
    float Angular_val;
    float Time_track = 0.0f;
    float Min_acc = 1000.0f;
    float Max_acc = 2500.0f;
    float Ramp_val = 2.0f;
    float Ang_acc = 5.0f * Math::Pi;
    float Drag_not = 0.975f;
    float Drag_pre = 0.9f;
    float Ang_drag = 0.9f;  
    std::vector<std::vector<int>> check;
    virtual void OnLapChange(int newLap) { }
    int Sizeof_path;
    bool Not_first = false;
    int GetCheck(){return Last_check;}
    void UpdateInfo(float time);
    void UpdateCheck();
};
#endif /* VehicleMove_hpp */
