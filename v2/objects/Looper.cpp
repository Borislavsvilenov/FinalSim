#include "Looper.hpp"

Looper::Looper()
{
  qt = new QT(0, 0, 800, 800);
  cam = new Cammera();
  bounds = new Box(0, 0, 800, 800);
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
    for (Particle* o : particles)
    {
      if (p != o)
      {
        p->checkCollision(o);
      }
    }
    p->update(new Vec2(0, 0.5f));
    cam->drawParticle(p);
    bounds->enforceBounds(p);
  } 
}

void Looper::addParticle(Particle* p)
{
  particles.push_back(p);
  qt->addParticle(p);
}

