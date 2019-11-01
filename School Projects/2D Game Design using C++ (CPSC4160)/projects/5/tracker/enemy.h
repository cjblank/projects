#ifndef ENEMY__H
#define ENEMY__H
#include <random>
#include <algorithm>
#include "multibullet.h"
#include "gamedata.h"
#include "multiSprite.h"

// In this example the player is derived from MultiSprite.
// However, there are many options.
class Enemy {
public:
  Enemy(const std::string&, const std::string&, const std::string&);
  Enemy(const Enemy&);
  ~Enemy();

  void draw();
  void update(Uint32 ticks);

  MultiSprite* getCurrentSprite() { return currentSprite; }

  void collided() { collision = true; }
  void missed() { collision = false; }
  Enemy& operator=(const Enemy&);
  int randomPos(int);

  //void right();
  //void left();
  //void up();
  //void down();
  //void stop();

  void die();
  bool isTotallyDead(){ return state == DEAD; }
  bool isDead() { 
    if ((state == DEAD) || (state == DYING)) 
      return true;
    else 
      return false; 
  }
  void setDead(bool);
  
  //void shot();
  //unsigned int bulletCount() { return bullets.bulletCount(); }
  //unsigned int freeCount() { return bullets.freeCount(); }

  MultiSprite* currentSprite;

protected:

  std::string moveName;
  std::string attackName;
  std::string deadName;
  MultiSprite* moveSprite;
  MultiSprite* attackSprite;
  MultiSprite* deadSprite;

  //const std::vector<Image*> imageLeft;
  //const std::vector<Image*> imageRight;
  //const std::vector<Image*> imageShootLeft;
  //const std::vector<Image*> imageShootRight;
  //      std::vector<Image*> images;

  int px;
  int py;
  int vx;
  int vy;

  bool collision;
  unsigned lastFrame;
  bool direction;
  bool isdead;

  //std::string bulletName;
  //float bulletInterval;
  float timeSinceLastShot;
  //float minBulletSpeed;
  //MultiBullet bullets;
  //int isShooting;
  enum STATE {MOVING, DYING, DEAD};
  STATE state;

  Vector2f initialVelocity;
  //MultiSprite multiSprite;
};
#endif
