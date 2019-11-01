#ifndef MULTISPRITE__H
#define MULTISPRITE__H
#include <string>
#include <vector>
#include <cmath>
#include "drawable.h"

class MultiSprite : public Drawable {
public: 
  MultiSprite(const std::string& n, const Vector2f& pos, const Vector2f& vel);
  MultiSprite(const std::string&);
  MultiSprite(const MultiSprite&);
  MultiSprite& operator=(const MultiSprite&) = delete;

  virtual void draw() const;
  virtual void update(Uint32 ticks);
  static Vector2f makeVelocity(int, int);
  static Vector2f makePosition(int, int);

  virtual const Image* getImage() const {
    return images[currentFrame];
  }
  int getScaledWidth()  const {
    return getScale()*images[currentFrame]->getWidth();
  }
  int getScaledHeight()  const {
    return getScale()*images[currentFrame]->getHeight();
  }
  virtual const SDL_Surface* getSurface() const {
    return images[currentFrame]->getSurface();
  }

protected:
  std::vector<Image *> images;

public:
  unsigned currentFrame;

protected:
  unsigned numberOfFrames;
  unsigned frameInterval;
  float timeSinceLastFrame;
  int worldWidth;
  int worldHeight;

  void advanceFrame(Uint32 ticks);
};
#endif