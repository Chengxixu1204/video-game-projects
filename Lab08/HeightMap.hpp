//
//  HeightMap.hpp
//  Lab08
//
//  Created by Chengxi Xu on 3/20/22.
//

#ifndef HeightMap_hpp
#define HeightMap_hpp

#include <stdio.h>
#include <vector>
#include "Actor.h"
#include "Game.h"

class HeightMap{
public:
    HeightMap();
    Vector3 CellToWorld(int row, int col);
    Vector2 WorldToCell(const Vector2& pos);
    bool IsOnTrack(const Vector2& pos);
    float GetHeight(const Vector2& pos);
private:
    std::vector<std::vector<int>> Only_map;
    bool IsCellOnTrack(int row, int col);
    float GetHeightFromCell(int row, int col);
};

#endif /* HeightMap_hpp */
