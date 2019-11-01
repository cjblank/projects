#ifndef SUBJECT_H
#define SUBJECT_H

#include <string>
#include <list>
#include <cmath>
#include "player.h"
#include "observer.h"

class Observer;

class Subject : public Player {
public:
  Subject(const std::string&);
  Subject(const Subject&);
  ~Subject();

  void notify();
  void attach( Observer* o ) { observers.push_back(o); }
  void detach( Observer* o );

protected:
  std::list<Observer*> observers;
  Subject& operator=(const Subject&);
};
#endif
