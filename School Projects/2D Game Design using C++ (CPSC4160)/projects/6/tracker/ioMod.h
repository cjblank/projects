#ifndef IOMOD_H
#define IOMOD_H

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

class IoMod {
public:
  static IoMod& getInstance();
  ~IoMod();
  SDL_Texture* readTexture(const std::string& filename);
  SDL_Surface* readSurface(const std::string& filename);
  void writeText(const std::string&, int, int) const;
  void writeText(const std::string&, int, int, SDL_Color) const;
  SDL_Renderer* getRenderer() const { return renderer; }
private:
  IoMod(const IoMod&) = delete;
  IoMod& operator=(const IoMod&) = delete;

  int init;
  SDL_Renderer* renderer;
  TTF_Font* font;
  SDL_Color textColor;
  IoMod();
};

#endif
