#pragma once
#include <raylib.h>
#include <vector>
#include <list>

#include "Vec2.hpp"
#include "Particle.hpp"

class Looper
{
public:
  std::vector<Particle> particles;

  Looper();
  ~Looper();
  
  void update();
  void addParticle(Particle p);
};
