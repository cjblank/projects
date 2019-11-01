#ifndef OBSERVER_H
#define OBSERVER_H
#include <string>
#include "multisprite.h"
#include "gameData.h"

class Observer {
public:
  Observer(MultiSprite*);
  Observer(const Observer&);
  virtual ~Observer() { }

  virtual void update(const Vector2f& pos, int w, int h);
  void setPlayerPos(const Vector2f& p) { playerPos = p; }
  bool rectCollision(SDL_Rect&, SDL_Rect&) const;

  Observer& operator=(const Observer&) = delete;

private:
  MultiSprite *multiSprite;
  Vector2f playerPos;
  int playerWidth;
  int playerHeight;
  bool collision;
  float safeDistance;

  void goLeft();
  void goRight();
  void goUp();
  void goDown();
};
#endif
