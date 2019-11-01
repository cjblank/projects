#include "observer.h"

bool Observer::rectCollision(SDL_Rect& rect1, SDL_Rect& rect2) const {
  float left1 = rect1.x;
  float left2 = rect2.x;

  float right1 = left1+rect1.w;
  float right2 = left2+rect2.w;
  if ( right1 < left2 ) return true;
  if ( left1 > right2 ) return true;
  float top1 = rect1.y;
  float top2 = rect2.y;
  float bottom1 = top1+rect1.h;
  float bottom2 = top2+rect2.h;
  if ( bottom1 < top2 ) return true;
  if ( bottom2 < top1 ) return true;
  return false;
}

void Observer::goLeft()  { multiSprite->setVelocityX( -abs(multiSprite->getVelocityX()) );  }
void Observer::goRight() { multiSprite->setVelocityX( fabs(multiSprite->getVelocityX()) );  }
void Observer::goUp()    { multiSprite->setVelocityY( -fabs(multiSprite->getVelocityY()) ); }
void Observer::goDown()  { multiSprite->setVelocityY( fabs(multiSprite->getVelocityY()) );  }


Observer::Observer(MultiSprite* ms):
  multiSprite(ms),
  playerPos(0),
  playerWidth(0),
  playerHeight(0),
  collision(false),
  safeDistance(Gamedata::getInstance().getXmlFloat("world/safeDistance"))
{}

Observer::Observer(const Observer& o) :
  multiSprite(o.multiSprite),
  playerPos(o.playerPos),
  playerWidth(o.playerWidth),
  playerHeight(o.playerHeight),
  collision(o.collision),
  safeDistance(o.safeDistance)
{}

void Observer::update( const Vector2f& pos, int w, int h) {
  float x= multiSprite->getX()+multiSprite->getImage()->getWidth()/2;
  float y= multiSprite->getY()+multiSprite->getImage()->getHeight()/2;
  float ex= pos[0]+w/2;
  float ey= pos[1]+h/2;

  SDL_Rect rect1 = {(int) multiSprite->getX(),
                    (int) multiSprite->getY(),
                    multiSprite->getImage()->getWidth(),
                    multiSprite->getImage()->getHeight()};

  SDL_Rect rect2 = {(int) pos[0], (int) pos[1], w, h};

  if  (collision == rectCollision(rect1, rect2)) {
      if ( x < ex ) goLeft();
      if ( x > ex ) goRight();
      if ( y < ey ) goUp();
      if ( y > ey ) goDown();
  }
}
