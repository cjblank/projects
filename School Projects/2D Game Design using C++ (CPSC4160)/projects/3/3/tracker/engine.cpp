#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <random>
#include <iomanip>
#include "sprite.h"
#include "multisprite.h"
#include "gameData.h"
#include "engine.h"
#include "frameGenerator.h"
#include "twoWayMultiSprite.h"

Engine::~Engine() {
  for(auto& sprite : sprites){
      delete sprite;
  }

  std::cout << "Terminating program" << std::endl;
}

Engine::Engine() :
  rc( RenderContext::getInstance() ),
  io( IoMod::getInstance() ),
  clock( Clock::getInstance() ),
  renderer( rc.getRenderer() ),
  world( ),
  viewport( Viewport::getInstance() ),
  sprites(),
  currentSprite(0),
  numFlyingMons(Gamedata::getInstance().getXmlInt("numFlyingMons")),
  makeVideo( false )
{
  world.addLayer("back1", Gamedata::getInstance().getXmlInt("back1/factor"));
  world.addLayer("back2", Gamedata::getInstance().getXmlInt("back2/factor"));
  world.addLayer("back3", Gamedata::getInstance().getXmlInt("back3/factor"));
  world.addLayer("back4", Gamedata::getInstance().getXmlInt("back4/factor"));
  world.addLayer("back5", Gamedata::getInstance().getXmlInt("back5/factor"));
  world.addLayer("back6", Gamedata::getInstance().getXmlInt("back6/factor"));

  sprites.emplace_back(new TwoWayMultiSprite("PoliceMan"));

  int px = Gamedata::getInstance().getXmlInt("FlyingMonster/startLoc/x");
  int py = Gamedata::getInstance().getXmlInt("FlyingMonster/startLoc/y");
  int vx = Gamedata::getInstance().getXmlInt("FlyingMonster/speedX");
  int vy = Gamedata::getInstance().getXmlInt("FlyingMonster/speedY");

  for(int i = 0; i < numFlyingMons; i++){
      sprites.emplace_back(new MultiSprite("FlyingMonster", MultiSprite::makePosition(px, py), MultiSprite::makeVelocity(vx, vy)));
  }


  //star->setScale(1.5);
  Viewport::getInstance().setObjectToTrack(sprites[0]);
  std::cout << "Loading complete" << std::endl;
}

void Engine::draw() const {
  world.draw();

  //star->draw();
  //policeMan->draw();
  //flyingMonster->draw();

  for(auto& sprite : sprites){
      sprite->draw();
  }

  viewport.draw();
  SDL_RenderPresent(renderer);
}

void Engine::update(Uint32 ticks) {
  //star->update(ticks);
  //policeMan->update(ticks);
  //flyingMonster->update(ticks);

  for(auto& sprite : sprites){
      sprite->update(ticks);
  }

  world.update();
  viewport.update(); // always update viewport last
}

void Engine::switchSprite(){
  ++currentSprite;
  currentSprite = currentSprite % 2;
  if ( currentSprite ) {
    Viewport::getInstance().setObjectToTrack(sprites[0]);
  }
  else {
    Viewport::getInstance().setObjectToTrack(sprites[1]);
  }
}

void Engine::play() {
  SDL_Event event;
  const Uint8* keystate;
  bool done = false;
  Uint32 ticks = clock.getElapsedTicks();
  FrameGenerator frameGen;

  while ( !done ) {
    // The next loop polls for events, guarding against key bounce:
    while ( SDL_PollEvent(&event) ) {
      keystate = SDL_GetKeyboardState(NULL);
      if (event.type ==  SDL_QUIT) { done = true; break; }
      if(event.type == SDL_KEYDOWN) {
        if (keystate[SDL_SCANCODE_ESCAPE] || keystate[SDL_SCANCODE_Q]) {
          done = true;
          break;
        }
        if ( keystate[SDL_SCANCODE_P] ) {
          if ( clock.isPaused() ) clock.unpause();
          else clock.pause();
        }
        if ( keystate[SDL_SCANCODE_T] ) {
          switchSprite();
        }
        if (keystate[SDL_SCANCODE_F4] && !makeVideo) {
          std::cout << "Initiating frame capture" << std::endl;
          makeVideo = true;
        }
        else if (keystate[SDL_SCANCODE_F4] && makeVideo) {
          std::cout << "Terminating frame capture" << std::endl;
          makeVideo = false;
        }
      }
    }

    // In this section of the event loop we allow key bounce:

    ticks = clock.getElapsedTicks();
    if ( ticks > 0 ) {
      clock.incrFrame();
      draw();
      update(ticks);
      if ( makeVideo ) {
        frameGen.makeFrame();
      }
    }
  }
}
