#include <sstream>
#include "viewport.h"
#include "ioMod.h"
#include "clock.h"
#include <sstream>
#include <string>

Viewport& Viewport::getInstance() {
  static Viewport viewport;
  return viewport;
}

Viewport::Viewport() :
  gdata(Gamedata::getInstance()),
  viewPos(0, 0),
  msgPos(
    Vector2f( gdata.getXmlInt("view/loc/x"), gdata.getXmlInt("view/loc/y") )
  ),
  fpsPos(
    Vector2f(gdata.getXmlInt("fps/loc/x"), gdata.getXmlInt("fps/loc/y"))
  ),
  namePos(
    Vector2f(gdata.getXmlInt("name/loc/x"), gdata.getXmlInt("name/loc/y"))
  ),
  name(
    gdata.getXmlStr("name/str/author")
  ),
  nameColor(),
  worldWidth(gdata.getXmlInt("world/width")),
  worldHeight(gdata.getXmlInt("world/height")),
  viewWidth(gdata.getXmlInt("view/width")),
  viewHeight(gdata.getXmlInt("view/height")),
  objWidth(0), objHeight(0),
  objectToTrack(NULL)
{
    nameColor.r = (Uint8)gdata.getXmlInt("name/red");
    nameColor.g = (Uint8)gdata.getXmlInt("name/green");
    nameColor.b = (Uint8)gdata.getXmlInt("name/blue");
    nameColor.a = (Uint8)gdata.getXmlInt("name/alpha");
}

void Viewport::setObjectToTrack(const Drawable *obj) {
  objectToTrack = obj;
  objWidth = objectToTrack->getScaledWidth();
  objHeight = objectToTrack->getScaledHeight();
}

void Viewport::draw() const {
  //IoMod::getInstance().
  //  writeText("Tracking: "+objectToTrack->getName(), msgPos[0], msgPos[1]);

  std::ostringstream str1;
  str1 << Clock::getInstance().getFps();

  //IoMod::getInstance().
  //    writeText("FPS: " + str1.str(), fpsPos[0], fpsPos[1]);

  IoMod::getInstance().
      writeText(name, namePos[0], namePos[1], nameColor);
}

void Viewport::update() {
  const float x = objectToTrack->getX();
  const float y = objectToTrack->getY();

  viewPos[0] = (x + objWidth/2) - viewWidth/2;
  viewPos[1] = (y + objHeight/2) - viewHeight/2;
  if (viewPos[0] < 0) viewPos[0] = 0;
  if (viewPos[1] < 0) viewPos[1] = 0;
  if (viewPos[0] > (worldWidth - viewWidth)) {
    viewPos[0] = worldWidth-viewWidth;
  }
  if (viewPos[1] > (worldHeight - viewHeight)) {
    viewPos[1] = worldHeight-viewHeight;
  }
}
