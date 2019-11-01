#ifndef MULTIBULLET_H
#define MULTIBULLET_H

#include <list>
#include <vector>
#include "vector2f.h"
#include "drawable.h"
#include "bulletFactory.h"


class MultiBullet {
public:
  MultiBullet(const std::string&);
  MultiBullet(const MultiBullet&);
  ~MultiBullet();

  void draw();
  void update(Uint32);
  void shoot(const Vector2f&, const Vector2f&);
  void poolHud(bool);
  void migrate(BulletFactory*);

  unsigned int bulletCount() const { return bullList.size(); }
  unsigned int freeCount() const { return freeList.size(); }
  bool bulletsAvail() { return !freeList.empty(); }
  std::list<BulletFactory*>& getBullList() { return bullList; }
  std::list<BulletFactory*>& getFreeList() { return freeList; }

  bool shooting() const { return !bullList.empty(); }
  bool collided(const Drawable*) const;


private:
  std::string name;
  Vector2f myVelocity;
  std::vector<Image*> bulletImages;
  std::list<BulletFactory*> bullList;
  std::list<BulletFactory*> freeList;
  //CollisionStrategy* strategy;
};


#endif