#include "subject.h"

Subject::~Subject(){
  for(auto& o : observers){
    detach(o);
    delete o;
  }
}

Subject::Subject(const std::string& name):
  Player(name),
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
  Vector2f pos = getPosition();
  int w = getScaledWidth();
  int h = getScaledHeight();

  //std::cout << "-----notify" << std::endl;

  std::list<Observer*>::iterator ptr = observers.begin();
  while ( ptr != observers.end() ) {
      (*ptr)->update(pos, w, h);
      ++ptr;
  }
}
