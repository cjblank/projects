#include "subject.h"

Subject::~Subject(){
  for(auto& o : observers){
    detach(o);
    delete o;
  }
}

Subject::Subject(const std::string& name1,
                 const std::string& name2,
                 const std::string& name3):
  Player(name1, name2, name3),
  observers()
{}

Subject::Subject(const Subject& s):
  Player(s),
  observers(s.observers)
{}

void Subject::detach(Observer* o){
  std::list<Observer*>::iterator ptr = observers.begin();
    while ( ptr != observers.end() ) {
      if ( *ptr == o ) {
        ptr = observers.erase(ptr);
        return;
      }
      ++ptr;
    }
}

void Subject::notify(){
  //Player::update(ticks);
  Vector2f pos = currentSprite->getPosition();
  int w = currentSprite->getScaledWidth();
  int h = currentSprite->getScaledHeight();


  std::list<Observer*>::iterator ptr = observers.begin();
  while ( ptr != observers.end() ) {
      (*ptr)->update(pos, w, h, currentSprite);
      ++ptr;
  }


  ptr = observers.begin();
  while (ptr != observers.end()){
    if((*ptr)->collided()){
      die();
      break;
    }
    ++ptr;
  }

}
