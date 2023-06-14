//
//  HUD.hpp
//  Lab12
//
//  Created by Chengxi Xu on 4/17/22.
//

#ifndef HUD_hpp
#define HUD_hpp

#include <stdio.h>
#include "Actor.h"
#include "Game.h"
#include "UIComponent.h"

class Font;
class Texture;
class HUD: public UIComponent{
public:
    HUD(class Actor* owner);
    ~HUD();
    void Update(float deltaTime) override;
    void Draw(class Shader* shader) override;
    Font* mFont;
    Texture* mTimerText;
    std::string Gettimestr(float t);
    Texture* mCoinText;
    Texture* r1;
    Texture* r2;
    Texture* r3;
    void SetCoinText();
    void SetCheckText(std::string t);
    bool start = false;
    float countdown = 5.0f;
    void bliploc(class Shader *shader);
    std::vector<Vector2> allblip;
};
#endif /* HUD_hpp */
