#include "observer.h"
#include <algorithm>

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

float Observer::collisionDistance(float x1, float x2, float y1, float y2) const {
  float x = x1-x2;
  float y = y1-y2;

  return hypot(x,y);
}

bool Observer::collisionMP(const Drawable* sprite1, const Drawable* sprite2) const {
  int width1 = sprite1->getScaledWidth();
  int width2 = sprite2->getScaledWidth();
  int height1 = sprite1->getScaledHeight();
  int height2 = sprite2->getScaledHeight();

  int COLLISION_DISTANCE = width1/8 + width2/8;

  float x1 = sprite1->getX() + width1/2;
  float y1 = sprite1->getY() + height1/2;
  float x2 = sprite2->getX() + width2/2;
  float y2 = sprite2->getY() + height2/2;

  return collisionDistance(x1, x2 ,y1, y2) < COLLISION_DISTANCE;
}

void Observer::goLeft()  { enemy->currentSprite->setVelocityX( -abs(enemy->currentSprite->getVelocityX()) );  }
void Observer::goRight() { enemy->currentSprite->setVelocityX( fabs(enemy->currentSprite->getVelocityX()) );  }
void Observer::goUp()    { enemy->currentSprite->setVelocityY( -fabs(enemy->currentSprite->getVelocityY()) ); }
void Observer::goDown()  { enemy->currentSprite->setVelocityY( fabs(enemy->currentSprite->getVelocityY()) );  }


Observer::Observer(Enemy* ms):
  enemy(ms),
  playerPos(0),
  playerWidth(0),
  playerHeight(0),
  collision(false),
  collisionDetected(false),
  safeDistance(Gamedata::getInstance().getXmlFloat("world/safeDistance"))
{}

Observer::Observer(const Observer& o) :
  enemy(o.enemy),
  playerPos(o.playerPos),
  playerWidth(o.playerWidth),
  playerHeight(o.playerHeight),
  collision(o.collision),
  collisionDetected(o.collisionDetected),
  safeDistance(o.safeDistance)
{}

void Observer::update( const Vector2f pos, const int w, const int h, const Drawable* sprite1) {
  if(enemy->isDead()) return;
  float x= enemy->currentSprite->getX()+enemy->currentSprite->getImage()->getWidth()/2;
  float y= enemy->currentSprite->getY()+enemy->currentSprite->getImage()->getHeight()/2;
  float ex= pos[0]+w/2;
  float ey= pos[1]+h/2;

  //SDL_Rect rect1 = {(int) enemy->getX(),
  //                  (int) enemy->getY(),
  //                  enemy->getImage()->getWidth(),
  //                  enemy->getImage()->getHeight()};

  //SD`L_Rect rect2 = {(int) pos[0], (int) pos[1], w, h};

  collisionDetected = false;

  if  (collisionMP(enemy->currentSprite, sprite1)) {
      if ( x < ex ) goLeft();
      if ( x > ex ) goRight();
      if ( y < ey ) goUp();
      if ( y > ey ) goDown();

      collisionDetected = true;
  }
}
