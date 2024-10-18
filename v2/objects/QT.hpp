#pragma once
#include <raylib.h>
#include <vector>
#include <list>

#include "Vec2.hpp"
#include "Particle.hpp"
#include "box.hpp"
#include "Cammera.hpp"

class QT
{
public:
  Box* box;
  std::list<Particle*> particles;
  int size = 5;
    
  bool subdivided = false;
  QT* topLeft = {};
  QT* topRight = {};
  QT* bottomLeft = {};
  QT* bottomRight = {};

  QT(float x, float y, float w, float h);
  ~QT();
  
  void fetch(std::vector<Particle*>& l, Box* area);
  
  void subdivide();
  void addParticle(Particle* p);
  void clear();
  void draw(Cammera* cam);

};
  
