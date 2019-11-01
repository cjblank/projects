#include "enemy.h"

Enemy::Enemy( const std::string& move, 
                const std::string& attack,
                const std::string& dead) :
  currentSprite(NULL),
  moveName(move),
  attackName(attack),
  deadName(dead),
  moveSprite(NULL),
  attackSprite(NULL),
  deadSprite(NULL),
  //imageLeft(),
  //imageRight(),
  //imageShootLeft(),
  //imageShootRight(),
  //images(),
  px(Gamedata::getInstance().getXmlInt("world/width") - 100),
  py(Gamedata::getInstance().getXmlInt("ZombieWalk/startLoc/y")),
  vx(Gamedata::getInstance().getXmlInt("ZombieWalk/speedX")),
  vy(Gamedata::getInstance().getXmlInt("ZombieWalk/speedY")),
  collision(false),
  lastFrame(0),
  direction(true),
  isdead(false),
  //bulletName("bullet"),
  //bulletInterval(Gamedata::getInstance().getXmlInt(bulletName+"/interval")),
  timeSinceLastShot(0),
  state(MOVING),
  //minBulletSpeed(Gamedata::getInstance().getXmlInt(bulletName+"/speed/x")),
  //bullets(bulletName),
  //isShooting(0),
  initialVelocity(0,0)
{ 
  moveSprite = new MultiSprite(moveName, MultiSprite::makePosition(px, py), MultiSprite::makeVelocity(-vx, vy));
  currentSprite = moveSprite;

  attackSprite = new MultiSprite(attackName, MultiSprite::makePosition(randomPos(px), py), MultiSprite::makeVelocity(vx, vy));
  deadSprite = new MultiSprite(deadName, MultiSprite::makePosition(randomPos(px), py), MultiSprite::makeVelocity(vx, vy));

  initialVelocity = moveSprite->getVelocity();
}

Enemy::Enemy(const Enemy& s) :
  currentSprite(NULL),
  moveName(s.moveName),
  attackName(s.attackName),
  deadName(s.deadName),
  moveSprite(NULL),
  attackSprite(NULL),
  deadSprite(NULL),
  px(s.px),
  py(s.py),
  vx(s.vx),
  vy(s.vy),
  collision(s.collision),
  lastFrame(s.lastFrame),
  direction(true),
  isdead(s.isdead),
  //bulletName(s.bulletName),
  //bulletInterval(s.bulletInterval),
  timeSinceLastShot(0),
  state(s.state),
  //minBulletSpeed(s.minBulletSpeed),
  //bullets(bulletName),
  //isShooting(0),
  initialVelocity(0,0)
  { 
    moveSprite = new MultiSprite(*s.moveSprite);
    currentSprite = moveSprite;

    attackSprite = new MultiSprite(*s.attackSprite);
    deadSprite = new MultiSprite(*s.deadSprite);
    
    initialVelocity = s.moveSprite->getVelocity();
  }

Enemy::~Enemy(){
  delete moveSprite;
  delete deadSprite;
}

Enemy& Enemy::operator=(const Enemy& s) {
  moveSprite = s.moveSprite;
  currentSprite = s.currentSprite;
  collision = s.collision;
  initialVelocity = s.initialVelocity;
  return *this;
}

int Enemy::randomPos (int x){
  std::random_device rd;
  std::mt19937 eng(rd());
  std::uniform_int_distribution<> distr(0, x);
  return distr(eng);
}

void Enemy::draw(){
  if(state != DEAD){  
    currentSprite->draw();
  }
}

void Enemy::die(){
  deadSprite->setVelocity(currentSprite->getVelocity());
  deadSprite->setPosition(currentSprite->getPosition());

  currentSprite = deadSprite;

  lastFrame = 0;
  currentSprite->currentFrame = 0;
  currentSprite->setVelocity(Vector2f(0,0));

  state = DYING;
  //std::cout<<"died"<<std::endl;
}

void Enemy::setDead(bool dead) { 
  isdead = dead; 
}

void Enemy::update(Uint32 ticks) {

  if ( !collision ) currentSprite->update(ticks);
  timeSinceLastShot += ticks;
  //bullets.update(ticks);

if(state == DYING){
  if ( currentSprite->currentFrame < lastFrame){  
    state = DEAD;
  }
}
//  if(isShooting == 0)
  
  if ( currentSprite != moveSprite ) {
    if ( currentSprite->currentFrame < lastFrame){
      moveSprite->setVelocity(currentSprite->getVelocity());
      moveSprite->setPosition(currentSprite->getPosition());
      currentSprite = moveSprite;
    }
  }

  lastFrame = currentSprite->currentFrame;
//  stop();
}
