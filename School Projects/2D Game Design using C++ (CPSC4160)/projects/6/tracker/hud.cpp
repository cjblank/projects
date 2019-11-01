#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <random>
#include <iomanip>
#include <SDL.h>
#include "hud.h"
#include "clock.h"
#include "viewport.h"

HUD::HUD():
    io(IoMod::getInstance()),
    gdata(Gamedata::getInstance()),
    rectPosX(gdata.getXmlInt("view/width")/4),
    rectPosY(gdata.getXmlInt("view/height")/5),
    rectSizeW(gdata.getXmlInt("view/width")/2),
    rectSizeH(gdata.getXmlInt("view/height")/2),
    rectangle({rectPosX,rectPosY,rectSizeW,rectSizeH}),
    fps(0),
    instructions(""),
    stringPos(Vector2f(rectPosX + 50, rectPosY + 110)),
    fpsPos(Vector2f(rectPosX + 50, rectPosY + 50)),
    stringColor()
{
    stringColor.r = (Uint8)gdata.getXmlInt("name/red");
    stringColor.g = (Uint8)gdata.getXmlInt("name/green");
    stringColor.b = (Uint8)gdata.getXmlInt("name/blue");
    stringColor.a = (Uint8)gdata.getXmlInt("name/alpha");
}

void HUD::toggleHUD(bool toggle) const {
    if(toggle == true){
      SDL_Renderer* const renderer = io.getRenderer();
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xff);
      SDL_RenderFillRect(renderer, &rectangle);

      std::ostringstream str1;
      str1 << Clock::getInstance().getFps();

      io.writeText("FPS: " + str1.str(), fpsPos[0], fpsPos[1]);
      IoMod::getInstance().
        writeText("Tracking: "+Viewport::getInstance().getObjectToTrack()->getName(), fpsPos[0], fpsPos[1] + 25);
      io.writeText(gdata.getXmlStr("hud/str/line1"), stringPos[0], stringPos[1],
        stringColor);
      io.writeText(gdata.getXmlStr("hud/str/line2"), stringPos[0], stringPos[1]
        + 30,  stringColor);
      io.writeText(gdata.getXmlStr("hud/str/line3"), stringPos[0], stringPos[1]
        + 60,  stringColor);
      io.writeText(gdata.getXmlStr("hud/str/line4"), stringPos[0], stringPos[1]
        + 90,  stringColor);
      io.writeText(gdata.getXmlStr("hud/str/line5"), stringPos[0], stringPos[1]
        + 120,  stringColor);
      io.writeText(gdata.getXmlStr("hud/str/line6"), stringPos[0], stringPos[1]
        + 150,  stringColor);
      io.writeText(gdata.getXmlStr("hud/str/line7"), stringPos[0], stringPos[1]
        + 180,  stringColor);
    }
}
