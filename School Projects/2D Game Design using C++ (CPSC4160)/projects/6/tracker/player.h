#ifndef PLAYER__H
#define PLAYER__H
#include "multibullet.h"
#include "gamedata.h"
#include "twoWayMultiSprite.h"

// In this example the player is derived from MultiSprite.
// However, there are many options.
class Player {
public:
  Player(const std::string&, const std::string&, const std::string&);
  Player(const Player&);
  ~Player();

  void draw();
  void update(Uint32 ticks);

  TwoWayMultiSprite* getCurrentSprite() { return currentSprite; }

  void collided() { collision = true; }
  void missed() { collision = false; }
  Player& operator=(const Player&);

  void right();
  void left();
  void up();
  void down();
  void stop();

  void die();
  void shoot();

  bool getGodMode(){ return godMode; }
  void setGodMode(bool g){ godMode = g; }
  bool getPhud() { return pHud; }
  void setPhud(bool p) { pHud = p; }
  MultiBullet& getBullets() { return bullets; }
  int getLives(){ return lives; }
  void setLives(int l) { lives = l; }
  bool isDead(){
    if (state != MOVING) 
      return true;
    else 
      return false; 
  }


  unsigned int bulletCount() { return bullets.bulletCount(); }
  unsigned int freeCount() { return bullets.freeCount(); }

protected:

  std::string moveName;
  std::string attackName;
  std::string deadName;
  TwoWayMultiSprite* moveSprite;
  TwoWayMultiSprite* attackSprite;
  TwoWayMultiSprite* deadSprite;
  TwoWayMultiSprite* currentSprite;

  bool collision;
  unsigned lastFrame;
  bool direction;
  bool pHud;
  bool godMode;

  std::string bulletName;
  float bulletInterval;
  float timeSinceLastShot;
  float minBulletSpeed;
  MultiBullet bullets;
  int isShooting;
  int lives;

  enum STATE {MOVING, DYING, DEAD, INVISIBLE};
  STATE state;

  Vector2f initialVelocity;
  //TwoWayMultiSprite twoWayMultiSprite;
};
#endif
