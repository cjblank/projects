#include <string>
#include <vector>
#include "image.h"
#include "viewport.h"

class World {
public:
  World();
  ~World() { } // The image will be deleted by the FrameFactory
  void update();
  void draw() const;
  void addLayer(const string, const int);
  World(const World&) = delete;
  World& operator=(const World&) = delete;
private:
  //Image* const image;
  std::vector<Image*> images;
  std::vector<int> factors;
  std::vector<unsigned int> imageWidths;
  std::vector<float> viewXs;
  std::vector<float> viewYs;
  const Viewport & view;
};
