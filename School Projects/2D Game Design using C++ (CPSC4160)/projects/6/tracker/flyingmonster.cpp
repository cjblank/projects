#include <random>
#include "flyingmonster.h"
#include "gamedata.h"

FlyingMonster::FlyingMonster(std::string name) : 
  multiSprite(new MultiSprite(name)),
  min(Gamedata::getInstance().getXmlFloat(name+"/min")),
  max(Gamedata::getInstance().getXmlFloat(name+"/max")),
  rate(Gamedata::getInstance().getXmlFloat(name+"/rate"))
{
  float x = float (rand() % 10)/10.0;
  float dif = abs(max-min);
  float scale = min+(dif*x);

  multiSprite->setScale(scale);
  multiSprite->setVelocity(Vector2f(Gamedata::getInstance().getXmlInt(name + "/speedX"), Gamedata::getInstance().getXmlInt(name + "/speedY")));
  multiSprite->setPosition(Vector2f(randomPos(Gamedata::getInstance().getXmlInt("world/width")), 
                                    randomPos(Gamedata::getInstance().getXmlInt("world/height")/4)));

  if(rand()%2 == 1){
    rate *= -1;
  }
}

FlyingMonster::FlyingMonster(FlyingMonster& f) :
  multiSprite(f.multiSprite),
  min(f.min),
  max(f.max),
  rate(f.rate)
{

}

FlyingMonster::~FlyingMonster(){}

int FlyingMonster::randomPos (int x){
  std::random_device rd;
  std::mt19937 eng(rd());
  std::uniform_int_distribution<> distr(0, x);
  return distr(eng);
}

void FlyingMonster::draw(){
  multiSprite->draw();
}

void FlyingMonster::update(Uint32 ticks){
  float scale = multiSprite->getScale();
  scale += rate;
  if((scale < min) || (scale > max)){
    rate = -rate;
  }


  multiSprite->setScale(scale);
  multiSprite->update(ticks);
}