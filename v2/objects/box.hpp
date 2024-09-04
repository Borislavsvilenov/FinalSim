#pragma once
#include <raylib.h>

#include "Vec2.hpp"
#include "Particle.hpp"

class Box
{
public:
  Vec2* pos;
  Vec2* size;

  Box(float x, float y, float w, float h);
  ~Box();
  
  bool checkInbounds(Particle* p);
  void draw();
};
