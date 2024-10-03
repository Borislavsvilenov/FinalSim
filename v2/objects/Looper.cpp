#include "Looper.hpp"

Looper::Looper()
{
  qt = new QT(0, 0, 800, 800);
  cam = new Cammera();
  bounds = new Box(0, 0, 800, 800);
  frame = 0;
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
  cam->draw(bounds);
  for (Particle* p : particles)
  {
    p->update(new Vec2(0, 0.5f));
    bounds->enforceBounds(p);

    for (Particle* o : particles)
    {
      if (p != o)
      {
        p->checkCollision(o);
      }
    }
    cam->draw(p);
  } 
  if(frame % 10 == 1)
  {
    addParticle(new Particle(400, 400, 2, 0, 5, 5, WHITE));
  }
  frame++;
  DrawFPS(0,0);
  DrawText(TextFormat("Particles: %i", particles.size()), 0, 20, 20, WHITE);

}

void Looper::addParticle(Particle* p)
{
  particles.push_back(p);
  qt->addParticle(p);
}

