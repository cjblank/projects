#include <vector>
#include <SDL.h>
#include "ioMod.h"
#include "renderContext.h"
#include "clock.h"
#include "world.h"
#include "viewport.h"
#include "hud.h"
#include "subject.h"
#include "sound.h"
#include "enemy.h"
#include "multibullet.h"
#include "flyingmonster.h"


//class Player;

class Engine {
public:
  Engine ();
  ~Engine ();
  void play();
  void switchSprite();
  int randomPos(int);
  void bulletCollide();
  void makeEnemies();
  void restart();
  void levelUP();
  float collisionDistance(float x1, float x2, float y1, float y2) 
    { float x = x1-x2; float y = y1-y2; return hypot(x,y); }

  bool collisionMP(const Drawable*, const Drawable*);

  Engine(const Engine&) = delete;
  Engine& operator=(const Engine&) = delete;
private:
  const RenderContext& rc;
  const IoMod& io;
  Clock& clock;

  SDL_Renderer * const renderer;
  World world;
  Viewport& viewport;
  Subject* player;
  HUD hud;

  //MultiBullet bullets;

  std::vector<Enemy*> sprites;
  std::vector<FlyingMonster*> flyingMons;
  int currentSprite;
  int numZombies;
  int numFlyingMons;
  int numZombiesDead;
  int level;

  bool tHud;
  bool makeVideo;
  bool godMode;
  bool gameOver;
  SDL_Rect const rectangle;

  int test;
  SDLSound sound;

  void draw() ;
  void update(Uint32);

  void printScales() const;
  void checkForCollisions();
};
