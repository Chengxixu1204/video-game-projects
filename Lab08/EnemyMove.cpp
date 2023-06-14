//
//  EnemyMove.cpp
//  Lab08
//
//  Created by Chengxi Xu on 3/20/22.
//

#include "EnemyMove.hpp"
#include <fstream>
#include "CSVHelper.h"
#include "HeightMap.hpp"
#include "Math.h"

const float DISTONEXT = 70.0f;
const float FIRSTDOT = 0.92f;
const float SECONDDOT = 0.97f;

EnemyMove::EnemyMove(class Actor* owner)
:VehicleMove(owner)
{
    std::ifstream infile("Assets/HeightMap/Path.csv");
    std::string line;
    int count = 0;
    while (std::getline(infile, line)){
        if(count != 0){
            std::vector<std::string> temp;
            Vector3 Path_point;
            if(line.size() != 0){
                temp = CSVHelper::Split(line);
                Path_point = Vector3(mOwner->GetGame()->Height_map->CellToWorld(std::stoi(temp[1]), std::stoi(temp[2])));
            }
            Path_record.push_back(Path_point);
        }
        count++;
    }
    mOwner->SetPosition(Path_record[0]);
}

void EnemyMove::Update(float deltaTime){
    
    if(Vector3::Distance(mOwner->GetPosition(), Path_record[Next_target]) < DISTONEXT){
        Next_target++;
        if(Next_target == static_cast<int>(Path_record.size())){
            Next_target = 0;
        }
    }
    Vector3 toTar = Vector3(Path_record[Next_target] - mOwner->GetPosition());
    toTar = Vector3::Normalize(toTar);
    float dotresult = Vector3::Dot(mOwner->GetForward(), toTar);
    if(dotresult > FIRSTDOT){
        SetPre(true);
    }else{
        SetPre(false);
    }
    if(dotresult < SECONDDOT){
       Vector3 temp = Vector3::Cross(mOwner->GetForward(), toTar);
       if(temp.z < 0){
            SetTurn(Left);
        }else if(temp.z > 0){
            SetTurn(Right);
        }
    }else{
        SetTurn(None);
    }
    
    VehicleMove::Update(deltaTime);
}
