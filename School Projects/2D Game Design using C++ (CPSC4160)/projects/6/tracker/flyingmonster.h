#pragma once

#include <string>
#include "gamedata.h"
#include "multisprite.h"

class FlyingMonster{
public:
  FlyingMonster(std::string);
  FlyingMonster(FlyingMonster&);
  ~FlyingMonster();
  FlyingMonster& operator=(const FlyingMonster&) = delete;

  void draw();
  void update(Uint32);
  int randomPos(int);

private:
  MultiSprite* multiSprite;
  float min;
  float max;
  float rate;
};