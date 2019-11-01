#include "multisprite.h"
#include "gameData.h"
#include "imageFactory.h"
#include <algorithm>

void MultiSprite::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
    currentFrame = (currentFrame+1) % numberOfFrames;
		timeSinceLastFrame = 0;
	}
}

Vector2f MultiSprite::makeVelocity(int vx, int vy) {
  float newvx = vx;
  float newvy = vy;

  if(vx!=0){
    newvx = Gamedata::getInstance().getRandFloat(vx-150,vx+150);;
    newvx *= [](){ if(rand()%2) return -1; else return 1; }();
  }
  if(vy!=0){
    newvy = Gamedata::getInstance().getRandFloat(vy-150,vy+150);;
    newvy *= [](){ if(rand()%2) return -1; else return 1; }();
  }

  return Vector2f(newvx, newvy);
}

Vector2f MultiSprite::makePosition(int px, int py) {
  float newpx = Gamedata::getInstance().getRandFloat(px-150,px+150);;
  float newpy = Gamedata::getInstance().getRandFloat(py-150,py+150);;

  newpx = std::max(newpx,30.0f);
  newpx = std::min(newpx,0.8f * ((float)Gamedata::getInstance().getXmlInt("world/width")));
  newpy = std::max(newpx,30.0f);
  newpy = std::min(newpx, ((float)Gamedata::getInstance().getXmlInt("world/height"))/2.0f);

  return Vector2f(newpx, newpy);
}

MultiSprite::MultiSprite(const string& n, const Vector2f& pos, const Vector2f& vel):
  Drawable(n, pos, vel),
  images(ImageFactory::getInstance().getImages(n)),
  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(n+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(n+"/frameInterval")),
  timeSinceLastFrame( 0 ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height"))
{ }

MultiSprite::MultiSprite( const std::string& name) :
  Drawable(name,
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"),
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")),
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"),
                    Gamedata::getInstance().getXmlInt(name+"/speedY"))
           ),
  images( ImageFactory::getInstance().getImages(name) ),
  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval")),
  timeSinceLastFrame( 0 ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height"))
{ }

void MultiSprite::draw() const {
  images[currentFrame]->draw(getX(), getY(), getScale());
}

void MultiSprite::update(Uint32 ticks) {
  advanceFrame(ticks);

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  //Vector2f incr2 = makeVelocity() * static_cast<float>(ticks) * 0.001;

  setPosition(getPosition() + incr);
  //setPosition(getPosition() + incr2);

  if ( getY() < 0) {
    setVelocityY( fabs( getVelocityY() ) );
  }
  if ( getY() + getScaledHeight() > worldHeight) {
    setVelocityY( -fabs( getVelocityY() ) );
  }

  if ( getX() < 0) {
    setVelocityX( fabs( getVelocityX() ) );
  }
  if ( getX() + getScaledWidth() > worldWidth) {
    setVelocityX( -fabs( getVelocityX() ) );
  }

}
