#include <iostream>
#include <cmath>
#include "bulletFactory.h"
#include "gamedata.h"
#include "imageFactory.h"

BulletFactory::BulletFactory( const string& name, const Vector2f&  pos,
                          const Vector2f& vel) :
   Sprite(name, pos, vel, ImageFactory::getInstance().getImage(name)),
   distance(0), 
   maxDistance(Gamedata::getInstance().getXmlInt(name+"/distance")), 
   tooFar(false) 
{ }

void BulletFactory::reset() {
  tooFar = false;
  distance = 0;
}

void BulletFactory::update(Uint32 ticks) { 
  Vector2f pos = getPosition();
  Sprite::update(ticks);
  if ( getY()+getScaledHeight() < 0 || getY() > worldHeight ) {
    tooFar = true;
  }
  if ( getX() < 0 || getX() > worldWidth ) {
    tooFar = true;
  }  
  distance += ( hypot(getX()-pos[0], getY()-pos[1]) );
  if (distance > maxDistance) tooFar = true;
}

