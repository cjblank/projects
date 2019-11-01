#include <sstream>
#include "multibullet.h"
#include "gameData.h"
#include "imageFactory.h"
#include "ioMod.h"
//#include "collisionStrategy.h"


MultiBullet::~MultiBullet(){
  std::list<BulletFactory*>::iterator ptr = bullList.begin();
  while (ptr != bullList.end()) {
    if ((*ptr)) {  // Check to see if we should free a chunk
      BulletFactory* oldptr = *ptr;
      ptr = bullList.erase(ptr);
      delete oldptr;
    }   
    else ++ptr;
  }  

  ptr = freeList.begin();
  while (ptr != freeList.end()) {
    if ((*ptr)) {  // Check to see if we should free a chunk
      BulletFactory* oldptr = *ptr;
      ptr = freeList.erase(ptr);
      delete oldptr;
    }   
    else ++ptr;
  }
}

MultiBullet::MultiBullet(const std::string& n) :
  name(n),
  myVelocity(
    Gamedata::getInstance().getXmlInt(name+"/speed/x"),
    Gamedata::getInstance().getXmlInt((name+"/speed/y"))
  ),
  bulletImages( ImageFactory::getInstance().getImages(name) ),
  bullList(),
  freeList()
  //strategy(NULL)
  {
    for(int i = 0; i < (Gamedata::getInstance().getXmlInt(name+"/bulletNum")); i++){
      freeList.emplace_back(new BulletFactory(name, Vector2f(), Vector2f()));
    }
  }

MultiBullet::MultiBullet(const MultiBullet& m) :
  name(m.name),
  myVelocity(m.myVelocity),
  bulletImages(m.bulletImages),
  bullList(m.bullList),
  freeList(m.freeList)
  //strategy(m.strategy)
  {

  }

void MultiBullet::shoot(const Vector2f& pos, const Vector2f& vel) {
  if (!freeList.empty()){
    BulletFactory* b = freeList.front();
    freeList.pop_front();
    b->reset();
    b->setVelocity(vel);
    b->setPosition(pos);
    bullList.emplace_back(b);
  }
}

void MultiBullet::poolHud(bool toggle){
  if (toggle){
    SDL_Rect rectangle;
    rectangle.x = 1000;
    rectangle.y = 100;
    rectangle.w = 200;
    rectangle.h = 200;
    //200,100,100);
    SDL_Renderer* const renderer = IoMod::getInstance().getRenderer();
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xff);
    SDL_RenderFillRect(renderer, &rectangle);

    std::ostringstream bullSize;
    std::ostringstream freeSize;

    bullSize << bulletCount();
    freeSize << freeCount();
  
    std::string hudTxt1 = "BulletList: " + bullSize.str();
    std::string hudTxt2 = "FreeList: " + freeSize.str();

    IoMod::getInstance().writeText(hudTxt1, rectangle.x + 20, rectangle.y + 50);
    IoMod::getInstance().writeText(hudTxt2, rectangle.x + 20, rectangle.y + 110);
  }
}

void MultiBullet::draw() {
  for (const auto& bullet : bullList){
    bullet->draw();
  }
}

void MultiBullet::update(Uint32 ticks) {
  std::list<BulletFactory*>::iterator ptr = bullList.begin();
  while (ptr != bullList.end()) {
    (*ptr)->update(ticks);
    if ((*ptr)->goneTooFar()) {  // Check to see if we should free a chunk
      freeList.emplace_back(*ptr);
      ptr = bullList.erase(ptr);
    }   
    else ++ptr;
  }
}

bool MultiBullet::collided(const Drawable* d) const {
  
  (void) d;

  return false;
}

void MultiBullet::migrate(BulletFactory* bullet){
  std::list<BulletFactory*>::iterator ptr = bullList.begin();
  while (ptr != bullList.end()) {
      if (*ptr == bullet) {
        freeList.emplace_back(*ptr);
        ptr = bullList.erase(ptr);
        break;
      }
    ptr++;
  }   
}
