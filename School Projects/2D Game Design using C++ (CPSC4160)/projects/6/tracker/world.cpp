#include <iostream>
#include <vector>
#include "world.h"
#include "imageFactory.h"

World::World() :
  images(),
  factors(),
    imageWidths(  ),
    viewXs(), viewYs(),
    view(Viewport::getInstance())
{
  //ImageFactory::getInstance().getImage(name);
}

void World::update() {
  for(unsigned i = 0; i < images.size(); i++){
    viewXs[i] = static_cast<int>(view.getX() / factors[i]) % imageWidths[i];
    viewYs[i] = view.getY();
  }
}

void World::draw() const {
  for(unsigned i = 0; i < images.size(); i++){
    images[i]->draw(0,0,-viewXs[i],-viewYs[i]);
    images[i]->draw(0,0,imageWidths[i]-viewXs[i],-viewYs[i]);
  }
}

void World::addLayer(const string file, const int fact) {
    images.push_back(ImageFactory::getInstance().getImage(file));
    factors.push_back(fact);
    imageWidths.push_back(images.back()->getWidth());
    viewXs.push_back(0.0);
    viewYs.push_back(0.0);
}
