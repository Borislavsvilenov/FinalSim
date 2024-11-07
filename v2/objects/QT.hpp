#pragma once
#include <raylib.h>
#include <vector>
#include <list>

#include "Vec2.hpp"
#include "ThreadPool.hpp"
#include "Particle.hpp"
#include "box.hpp"
#include "Cammera.hpp"

class QT
{
public:
  Box* box;
  std::list<Particle*> particles;
  int size = 10;
  bool MainTree;
    
  bool subdivided = false;
  QT* topLeft = {};
  QT* topRight = {};
  QT* bottomLeft = {};
  QT* bottomRight = {};

  QT(float x, float y, float w, float h, bool mt);
  ~QT();

  void fetch(std::vector<Particle*>& l, Box* area, ThreadPool* tp, std::mutex& resultMutex, int depth);
  
  void subdivide();
  void addParticle(Particle* p);
  void clear();
  void draw(Cammera* cam);

};
  
