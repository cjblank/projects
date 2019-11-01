#include <vector>
#include <SDL.h>
#include "ioMod.h"
#include "renderContext.h"
#include "clock.h"
#include "world.h"
#include "viewport.h"
#include "hud.h"
#include "subject.h"


//class Player;

class Engine {
public:
  Engine ();
  ~Engine ();
  void play();
  void switchSprite();

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

  std::vector<Drawable*> sprites;
  int currentSprite;
  int numFlyingMons;

  bool toggle;
  bool makeVideo;

  int test;

  void draw() const;
  void update(Uint32);

  void printScales() const;
  void checkForCollisions();
};
