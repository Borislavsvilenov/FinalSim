#pragma once
#include <raylib.h>
#include <cmath>

#include "Vec2.hpp"
#include "Particle.hpp"

class Box
{
public:
  Vec2* pos;
  Vec2* size;
  float bounciness = 0.8;

  Box(float x, float y, float w, float h);
  Box();
  ~Box();
  
  bool checkInbounds(Particle* p);
  bool intersects(Box* b);
  void enforceBounds(Particle* p);
  void draw();
};
