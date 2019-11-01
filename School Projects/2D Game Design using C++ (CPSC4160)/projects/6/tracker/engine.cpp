#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <random>
#include <iomanip>
#include "ioMod.h"
#include "engine.h"
#include "sprite.h"
#include "multisprite.h"
#include "gameData.h"
#include "frameGenerator.h"
#include "twoWayMultiSprite.h"
#include "hud.h"
#include "subject.h"
#include "observer.h"
#include "bulletFactory.h"



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
  player(NULL),
  hud(),
  //bullets(),
  sprites(),
  flyingMons(),
  currentSprite(0),
  numZombies(Gamedata::getInstance().getXmlInt("numZombies")),
  numFlyingMons(Gamedata::getInstance().getXmlInt("numFlyingMons")),
  numZombiesDead(0),
  level(1),
  tHud(false),
  //pHud(false),
  makeVideo( false ),
  godMode( false ),
  gameOver( false ),
  rectangle({550,270,200,85}),
  test(0),
  sound()
{
  world.addLayer("back1", Gamedata::getInstance().getXmlInt("back1/factor"));
  world.addLayer("back2", Gamedata::getInstance().getXmlInt("back2/factor"));
  world.addLayer("back3", Gamedata::getInstance().getXmlInt("back3/factor"));
  world.addLayer("back4", Gamedata::getInstance().getXmlInt("back4/factor"));
  world.addLayer("back5", Gamedata::getInstance().getXmlInt("back5/factor"));
  world.addLayer("back6", Gamedata::getInstance().getXmlInt("back6/factor"));

  player = new Subject("PoliceManMove", "PoliceManAttack", "PoliceManDead");

  makeEnemies();

  for (int i = 0; i < numFlyingMons; i++){
    FlyingMonster* fm = new FlyingMonster("FlyingMonster");
    flyingMons.emplace_back(fm);
  }

  //star->setScale(1.5);
  Viewport::getInstance().setObjectToTrack(player->getCurrentSprite());
  std::cout << "Loading complete" << std::endl;
}

void Engine::draw()  {
  player->notify();

  world.draw();


  std::ostringstream lifeCt;
  std::ostringstream lvlCt;

  lifeCt << player->getLives(); 
  lvlCt << level;

  std::string gmTxt;
  if(godMode) gmTxt = "ON"; else gmTxt = "OFF";

  std::string lifeTxt = "Lives:" + lifeCt.str();
  std::string lvlTxt = "Level:" + lvlCt.str();
  gmTxt = "God Mode:" + gmTxt;

  IoMod::getInstance().writeText(Gamedata::getInstance().getXmlStr("hud/str/line9"), 
                                 Gamedata::getInstance().getXmlInt("hud/loc1/x"), 
                                 Gamedata::getInstance().getXmlInt("hud/loc1/y"));
  
  IoMod::getInstance().writeText( lifeTxt , 1150 , 20 );
  IoMod::getInstance().writeText( lvlTxt , 1150 , 60 );
  IoMod::getInstance().writeText( gmTxt , 950 , 20 );
  //star->draw();
  //policeMan->draw();
  //flyingMonster->draw();

  numZombiesDead = 0;

  for(auto& sprite : sprites){
      sprite->draw();
      if(sprite->isTotallyDead()){
        numZombiesDead++;
      }
  }

  for(auto& fm : flyingMons){
    fm->draw();
  }

  player->draw();

  viewport.draw();
  hud.toggleHUD(tHud);
  bulletCollide();
  //player->setPhud(pHud);
  
  if (player->getLives() == 0){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xff);
    SDL_RenderFillRect(renderer, &rectangle);
    IoMod::getInstance().writeText( "Game Over" , 590 , 300 );
    clock.pause();
    gameOver = true;
  }

  if(numZombiesDead == numZombies*level){
    levelUP();
  }

  if(level > 5){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xff);
    SDL_RenderFillRect(renderer, &rectangle);
    IoMod::getInstance().writeText( "You won!" , 600 , 300 );
    clock.pause();
  }

  SDL_RenderPresent(renderer);
}

void Engine::makeEnemies(){

  for(auto& s : sprites){
    delete s;
  }
  sprites.clear();

  for(auto& o : player->observers){
    delete o;
  }
  player->observers.clear();

  for(int i = 0; i < numZombies * level; i++){
    Enemy* ms = new Enemy("ZombieWalk", "ZombieAttack", "ZombieDead");
    sprites.emplace_back(ms);
    player->attach(new Observer(ms));
  }

}

void Engine::restart(){
  makeEnemies();

  player->setLives(3);

  level = 1;

  clock.unpause();
}

void Engine::levelUP(){
  level++;
  makeEnemies();

  player->setLives(3);

}

void Engine::bulletCollide(){
  std::list<BulletFactory*> bullets = player->getBullets().getBullList();

  for(auto e : sprites){
    for (auto b : bullets){
      if(!e->isDead()){
        if(collisionMP(e->currentSprite,b)){
          e->die();
          player->getBullets().migrate(b);
          numZombiesDead++;
        }
      }
    }
  }
}

bool Engine::collisionMP(const Drawable* sprite1, const Drawable* sprite2) {
  int width1 = sprite1->getScaledWidth();
  int width2 = sprite2->getScaledWidth();
  int height1 = sprite1->getScaledHeight();
  int height2 = sprite2->getScaledHeight();

  int COLLISION_DISTANCE = width1/2 + width2/2;

  float x1 = sprite1->getX() + width1/2;
  float y1 = sprite1->getY() + height1/2;
  float x2 = sprite2->getX() + width2/2;
  float y2 = sprite2->getY() + height2/2;

  return collisionDistance(x1, x2 ,y1, y2) < COLLISION_DISTANCE;
}

void Engine::update(Uint32 ticks) {
  //star->update(ticks);
  //policeMan->update(ticks);
  //flyingMonster->update(ticks);


  for(auto& sprite : sprites){
      sprite->update(ticks);
  }

  for(auto& fm : flyingMons){
    fm->update(ticks);
  }

  player->update(ticks);

  Viewport::getInstance().setObjectToTrack(player->getCurrentSprite());
  world.update();
  viewport.update(); // always update viewport last
}

void Engine::switchSprite(){
  ++currentSprite;
  currentSprite = currentSprite % 2;
  if ( currentSprite ) {
 //   Viewport::getInstance().setObjectToTrack(sprites[0]);
  }
  else {
   // Viewport::getInstance().setObjectToTrack(sprites[1]);
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

        if ( keystate[SDL_SCANCODE_R] ) {
          restart();
        }

        if ( keystate[SDL_SCANCODE_G] ) {
          godMode = !godMode;
          player->setGodMode(godMode);
        }

        if( keystate[SDL_SCANCODE_F1])
        {
          tHud = !tHud;
        }

        if( keystate[SDL_SCANCODE_F2])
        {
          player->setPhud(!player->getPhud());
        }

        if (keystate[SDL_SCANCODE_F4] && !makeVideo) {
          std::cout << "Initiating frame capture" << std::endl;
          makeVideo = true;
        }
        if(keystate[SDL_SCANCODE_SPACE]){
          if(!player->isDead()){
            sound[0];
            player->shoot();
          }
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
      if( keystate[SDL_SCANCODE_D]) {
        if(!player->isDead())
          player->right();
      }

      if( keystate[SDL_SCANCODE_A]) {
        if(!player->isDead())
          player->left();
      }

      update(ticks);
      if ( makeVideo ) {
        frameGen.makeFrame();
      }
    }
  }
}
