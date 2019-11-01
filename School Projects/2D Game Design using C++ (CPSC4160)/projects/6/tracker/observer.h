#ifndef OBSERVER_H
#define OBSERVER_H
#include <string>
#include "enemy.h"
#include "gameData.h"

class Observer {
public:
  Observer(Enemy*);
  Observer(const Observer&);
  virtual ~Observer() { }

  virtual void update(const Vector2f, const int, const int, const Drawable*);
  void setPlayerPos(const Vector2f& p) { playerPos = p; }
  bool rectCollision(SDL_Rect&, SDL_Rect&) const;
  float collisionDistance(float, float, float, float) const;
  bool collisionMP(const Drawable*, const Drawable*) const;

  bool collided() { return collisionDetected; }

  Observer& operator=(const Observer&) = delete;

private:
  Enemy *enemy;
  Vector2f playerPos;
  int playerWidth;
  int playerHeight;
  bool collision;
  bool collisionDetected;
  float safeDistance;

  void goLeft();
  void goRight();
  void goUp();
  void goDown();
};
#endif
