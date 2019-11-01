#ifndef HUD_H
#define HUD_H
#include <vector>
#include <string>
#include <SDL.h>
#include "vector2f.h"
#include "ioMod.h"
#include "gameData.h"

class HUD {
public:
    HUD();
    void toggleHUD(bool) const;
private:

    IoMod& io;
    Gamedata& gdata;

    const int rectPosX;
    const int rectPosY;
    const int rectSizeW;
    const int rectSizeH;
    SDL_Rect const rectangle;
    const int fps;
    std::string instructions;

    Vector2f stringPos;
    Vector2f fpsPos;

    SDL_Color stringColor;
};

#endif
