#include "Looper.hpp"

Looper::Looper()
{

}

Looper::~Looper()
{

}

void Looper::update()
{
  for (Particle p : particles)
  {
    p.update(new Vec2(0, 0.5f));
    p.draw();
  } 
}

void Looper::addParticle(Particle p)
{
  particles.push_back(p);
}

