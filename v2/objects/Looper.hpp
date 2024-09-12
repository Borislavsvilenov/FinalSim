#pragma once
#include <raylib.h>
#include <vector>
#include <list>

#include "Vec2.hpp"
#include "Particle.hpp"
#include "QT.hpp"
#include "box.hpp"
#include "Cammera.hpp"


class Looper
{
public:
  std::vector<Particle*> particles;

  QT* qt;
  Cammera* cam;

  Looper();
  ~Looper();
  
  void update();
  void addParticle(Particle* p);
};
