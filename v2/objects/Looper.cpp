#include "Looper.hpp"

Looper::Looper()
{
  qt = new QT(0, 0, 800, 800);
}

Looper::~Looper()
{ 
  delete qt;
  for (Particle* p : particles)
  {
    delete p;
  }
}

void Looper::update()
{
  for (Particle* p : particles)
  {
    p->update(new Vec2(0, 0.5f));
    p->draw();
  } 
}

void Looper::addParticle(Particle* p)
{
  particles.push_back(p);
  qt->addParticle(p);
}

