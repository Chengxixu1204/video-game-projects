//
//  VehicleMove.cpp
//  Lab08
//
//  Created by Chengxi Xu on 3/10/22.
//

#include "VehicleMove.hpp"
#include "HeightMap.hpp"
#include <fstream>
#include "CSVHelper.h"
#include "Player.hpp"

VehicleMove::VehicleMove(Actor* owner)
:Component(owner, 50)
{
    std::ifstream infile("Assets/HeightMap/Checkpoints.csv");
    std::string line = "";
    int count = 0;
    while (std::getline(infile, line)){
        if(count != 0){
            std::vector<std::string> Temp_vec;
            std::vector<int> Trans_vec;
            if(line.size() != 0){
                Temp_vec = CSVHelper::Split(line);
                for(size_t i = 1; i < Temp_vec.size(); i++){
                    Trans_vec.push_back(std::stoi(Temp_vec[i]));
                }
            }
            check.push_back(Trans_vec);
        }
        count++;
    }
    Sizeof_path = static_cast<int>(check.size());
}

VehicleMove::~VehicleMove(){
    
}

void VehicleMove::Update(float deltaTime){
    UpdateInfo(deltaTime);
    UpdateCheck();
    if(Last_check == static_cast<int>(check.size())){
        Current_lap += 1;
        Last_check = -1;
        Not_first = true;
    }
    if(Last_check == 0 && Not_first){
       OnLapChange(Current_lap);
    }
    
}

float VehicleMove::DisToNext(){
    return Vector3::Distance(mOwner->GetPosition(), mOwner->GetGame()->Height_map->CellToWorld(check[(Last_check + 1)%Sizeof_path][0], check[(Last_check + 1)%Sizeof_path][2]));
}

void VehicleMove::UpdateInfo(float deltaTime){
    if(Is_pressed){
        Time_track += deltaTime;
        float acc = Math::Lerp(Min_acc, Max_acc, Time_track/Ramp_val);
        Ve_velocity += mOwner->GetForward()*acc*deltaTime;
    }else{
        Time_track = 0.0f;
    }
    mOwner->SetPosition(mOwner->GetPosition() + Ve_velocity*deltaTime);
    Vector2 temp(mOwner->GetPosition().x, mOwner->GetPosition().y);
    if(mOwner->GetGame()->Height_map->IsOnTrack(temp)){
        mOwner->SetPosition(Vector3(temp.x, temp.y, Math::Lerp(mOwner->GetPosition().z,mOwner->GetGame()->Height_map->GetHeight(temp), 0.1f)));
    }
    if(Is_pressed){
        Ve_velocity *= Drag_pre;
    }else{
        Ve_velocity *= Drag_not;
    }
    if(Ve_type != None){
        if(Ve_type == Right){
            Angular_val += Ang_acc*1*deltaTime;
        }else{
            Angular_val += Ang_acc*(-1)*deltaTime;
        }
    }
    mOwner->SetRotation(mOwner->GetRotation() + Angular_val*deltaTime);
    Angular_val *= Ang_drag;
}

void VehicleMove::UpdateCheck(){
    Vector2 Check_point = mOwner->GetGame()->Height_map->WorldToCell(Vector2(mOwner->GetPosition().x, mOwner->GetPosition().y));
    int check_index = static_cast<int>((Last_check + 1)%Sizeof_path);
    int check_x = static_cast<int>(Check_point.x);
    int check_y = static_cast<int>(Check_point.y);
    if((check_x >= check[check_index][0] && check_x <= check[check_index][1]) && (check_y >= check[check_index][2] && check_y <= check[check_index][3])){
        Last_check += 1;
    }
}
