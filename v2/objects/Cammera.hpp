#pragma once
#include <raylib.h>

#include "Vec2.hpp"
#include "box.hpp"
#include "Particle.hpp"

class Cammera
{
public:
  Vec2* pos;

  Cammera();
  ~Cammera();
  
  void mvCam (Vec2* vel);
  
  void draw (Particle* p);
  void draw (Box* b);
};
