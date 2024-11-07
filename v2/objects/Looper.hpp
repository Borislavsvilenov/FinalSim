#pragma once
#include <raylib.h>
#include <vector>
#include <mutex>

#include "Particle.hpp"
#include "QT.hpp"
#include "box.hpp"
#include "Cammera.hpp"
#include "ThreadPool.hpp"

class Looper
{
public:
  std::vector<Particle*> particles;
  std::vector<Particle*> closeP;

  QT* qt;
  Cammera* cam;
  Box* bounds;
  Box* aroundP;
  ThreadPool* tp;
  std::mutex resultMutex;

  int frame;

  Looper();
  ~Looper();
  
  void update();
  void addParticle(Particle* p);
};
