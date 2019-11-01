#include "player.h"

Player::Player( const std::string& move, 
                const std::string& attack,
                const std::string& dead) :
  moveName(move),
  attackName(attack),
  deadName(dead),
  moveSprite(NULL),
  attackSprite(NULL),
  deadSprite(NULL),
  currentSprite(NULL),
  //imageLeft(),
  //imageRight(),
  //imageShootLeft(),
  //imageShootRight(),
  //images(),
  collision(false),
  lastFrame(0),
  direction(true),
  pHud(false),
  godMode(false),
  bulletName("bullet"),
  bulletInterval(Gamedata::getInstance().getXmlInt(bulletName+"/interval")),
  timeSinceLastShot(0),
  minBulletSpeed(Gamedata::getInstance().getXmlInt(bulletName+"/speed/x")),
  bullets(bulletName),
  isShooting(0),
  lives(3),
  state(MOVING),
  initialVelocity(0,0)
{ 
  moveSprite = new TwoWayMultiSprite(moveName);
  currentSprite = moveSprite;

  attackSprite = new TwoWayMultiSprite(attackName);
  deadSprite = new TwoWayMultiSprite(deadName);

  initialVelocity = moveSprite->getVelocity();
}

Player::Player(const Player& s) :
  moveName(s.moveName),
  attackName(s.attackName),
  deadName(s.deadName),
  moveSprite(NULL),
  attackSprite(NULL),
  deadSprite(NULL),
  currentSprite(NULL),
  collision(s.collision),
  lastFrame(s.lastFrame),
  direction(s.direction),
  pHud(s.pHud),
  godMode(s.godMode),
  bulletName(s.bulletName),
  bulletInterval(s.bulletInterval),
  timeSinceLastShot(0),
  minBulletSpeed(s.minBulletSpeed),
  bullets(bulletName),
  isShooting(0),
  lives(s.lives),
  state(s.state),
  initialVelocity(0,0)
  { 
    moveSprite = new TwoWayMultiSprite(*s.moveSprite);
    currentSprite = moveSprite;

    attackSprite = new TwoWayMultiSprite(*s.attackSprite);
    deadSprite = new TwoWayMultiSprite(*s.deadSprite);
    
    initialVelocity = s.moveSprite->getVelocity();
  }

Player::~Player(){
  delete moveSprite;
}

Player& Player::operator=(const Player& s) {
  moveSprite = s.moveSprite;
  currentSprite = s.currentSprite;
  collision = s.collision;
  initialVelocity = s.initialVelocity;
  return *this;
}

void Player::draw(){
  if(state != INVISIBLE)
    currentSprite->draw();
  bullets.draw();
  bullets.poolHud(pHud);
}

void Player::die(){
  if (!getGodMode() && (state != INVISIBLE)){
    deadSprite->setVelocity(currentSprite->getVelocity());
    deadSprite->setPosition(currentSprite->getPosition());
  
    currentSprite = deadSprite;
    currentSprite->setDirection(); 
  
    lastFrame = 0;
  
    state = DEAD;

    isShooting = 0;
    //lives--;
  }
}

void Player::shoot(){
  //if(!isDead){}
  if(bullets.bulletsAvail() == true){
    attackSprite->setVelocity(currentSprite->getVelocity());
    attackSprite->setPosition(currentSprite->getPosition());
    //if(attackSprite->getVelocity() > 0) { direction == true; }
  //  else if(attackSprite->getVelocity() < 0) { direction == false; }
  
    currentSprite = attackSprite;
    currentSprite->setDirection();
    
  
    if(isShooting > 0){
      currentSprite->currentFrame = (unsigned)Gamedata::getInstance().getXmlInt(attackName+"/shotStart");
    }
    else{
      currentSprite->currentFrame = 0;
    }
  
    if (isShooting < Gamedata::getInstance().getXmlInt(bulletName+"/bulletNum")){
      isShooting++;
    }
    lastFrame = 0;
  
    //if(attackSprite->getVelocity() > 0) { }
  }

}

void Player::stop() {
  //setVelocity( Vector2f(0, 0) );
  currentSprite->setVelocityX( 0.5*currentSprite->getVelocityX() );
  currentSprite->setVelocityY(0);
}

void Player::right() {
  if ( currentSprite->getX() < currentSprite->worldWidth-currentSprite->getScaledWidth()) {
    currentSprite->setVelocityX(initialVelocity[0]);
    currentSprite->setDirection();
  }
}
void Player::left()  {
  if ( currentSprite->getX() > 0) {
    currentSprite->setVelocityX(-initialVelocity[0]);
    currentSprite->setDirection();
  }
}
void Player::up()    {
  if ( currentSprite->getY() > 0) {
    currentSprite->setVelocityY( -initialVelocity[1] );
  }
}
void Player::down()  {
  if ( currentSprite->getY() < currentSprite->worldHeight-currentSprite->getScaledHeight()) {
    currentSprite->setVelocityY( initialVelocity[1] );
  }
}

void Player::update(Uint32 ticks) {
  if ( !collision ) currentSprite->update(ticks);
  timeSinceLastShot += ticks;
  bullets.update(ticks);

  if(isShooting == 0){
    if ( (currentSprite != moveSprite) || (state != DEAD) ) {
      if ( currentSprite->currentFrame < lastFrame){
        if(state == DEAD){
          state = INVISIBLE;
          lives--;
        }
        else {
          moveSprite->setVelocity(currentSprite->getVelocity());
          moveSprite->setPosition(currentSprite->getPosition());
    
          currentSprite = moveSprite;
          state = MOVING;
        }
      }
    }
  }



  if(timeSinceLastShot > bulletInterval){
    Vector2f vel = currentSprite->getVelocity();
    float x;
    float y = currentSprite->getY() + currentSprite->getScaledHeight()/2 - 10;
    if (vel[0] > 0){
      x = currentSprite->getX() + currentSprite->getScaledHeight() - 115;
      vel[0] += minBulletSpeed;
    }
    else if (vel[0] < 0){
      x = currentSprite->getX() + 115;
      vel[0] -= minBulletSpeed;
    }
    else if (currentSprite->facing == TwoWayMultiSprite::RIGHT){
      x = currentSprite->getX() + currentSprite->getScaledHeight() - 115;
      vel[0] += minBulletSpeed;
    }
    else if (currentSprite->facing == TwoWayMultiSprite::LEFT){
      x = currentSprite->getX() + 115;
      vel[0] -= minBulletSpeed;
    }


    if(!isDead()){
      if( isShooting && ( currentSprite->currentFrame == (unsigned)Gamedata::getInstance().getXmlInt(attackName+"/shootFrame"))){
        bullets.shoot(Vector2f(x,y), vel);
        isShooting--;
        if(isShooting){
          currentSprite->currentFrame = (unsigned)Gamedata::getInstance().getXmlInt(attackName+"/shootFrame");
        }
      }
      if (isShooting)
        timeSinceLastShot = bulletInterval - ticks;
      else
        timeSinceLastShot = 0;
    }
  }

  lastFrame = currentSprite->currentFrame;
  stop();
}
