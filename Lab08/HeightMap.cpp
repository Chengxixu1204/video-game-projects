//
//  HeightMap.cpp
//  Lab08
//
//  Created by Chengxi Xu on 3/20/22.
//

#include "HeightMap.hpp"
#include <fstream>
#include "CSVHelper.h"

const float CELL_SIZE = 40.55f;
const float GRID_TOP = 1280.0f;
const float GRID_LEFT = -1641.0f;


HeightMap::HeightMap(){
    std::ifstream infile("Assets/HeightMap/HeightMap.csv");
    std::string line;
    while (std::getline(infile, line)){
        std::vector<std::string> temp;
        std::vector<int> trans;
        if(line.size() != 0){
            temp = CSVHelper::Split(line);
            for(size_t i = 0; i < temp.size(); i++){
                trans.push_back(std::stoi(temp[i]));
            }
        }
        Only_map.push_back(trans);
    }
}

bool HeightMap::IsCellOnTrack(int row, int col){
    if(row >= static_cast<int>(Only_map.size()) || col >= static_cast<int>(Only_map[0].size())){
        return false;
    }
    if(Only_map[row][col] == -1){
        return false;
    }
    return true;
}

float HeightMap::GetHeightFromCell(int row, int col){
    int cellvalue = Only_map[row][col];
    return -40.0f + cellvalue * 5.0f;
}

Vector3 HeightMap::CellToWorld(int row, int col){
    if(IsCellOnTrack(row, col)){
        return Vector3(GRID_TOP - CELL_SIZE * row, GRID_LEFT + CELL_SIZE * col, GetHeightFromCell(row, col));
    }else{
        return Vector3::Zero;
    }
}

Vector2 HeightMap::WorldToCell(const Vector2 &pos){
    return Vector2((Math::Abs(pos.x - GRID_TOP) + CELL_SIZE / 2.0f) / CELL_SIZE, (Math::Abs(pos.y - GRID_LEFT) + CELL_SIZE / 2.0f) / CELL_SIZE);
}

bool HeightMap::IsOnTrack(const Vector2 &pos){
    return IsCellOnTrack(static_cast<int>(WorldToCell(pos).x), static_cast<int>(WorldToCell(pos).y));
}

float HeightMap::GetHeight(const Vector2 &pos){
    float height = 0.0f;
    if(IsOnTrack(pos)){
         height = GetHeightFromCell(static_cast<int>(WorldToCell(pos).x), static_cast<int>(WorldToCell(pos).y));
    }
    return height;
}
