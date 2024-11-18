#include "Looper.hpp"

Looper::Looper()
{
  qt = new QT(0, 0, 800, 800, true);
  tp = new ThreadPool(std::thread::hardware_concurrency());
  cam = new Cammera();
  bounds = new Box(0, 0, 800, 800);
  aroundP = new Box();
  frame = 0;

  paused = false;
  spawn = true;
  multithreaded = false;
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

  if(!paused) {
    qt->clear();
    for (Particle* p : particles) {
      qt->addParticle(p);
    }
    for (Particle* p : particles)
    {
      p->update(new Vec2(0, 0.5f));
      bounds->enforceBounds(p);

      aroundP->pos->x = p->pos->x - (1.5*p->radius);
      aroundP->pos->y = p->pos->y - (1.5*p->radius);
      aroundP->size->x = p->pos->x + (1.5*p->radius);
      aroundP->size->y = p->pos->y + (1.5*p->radius);

      if(multithreaded) {
        qt->fetch(closeP, aroundP, tp, resultMutex, 0);
      } else {
        qt->fetch(closeP, aroundP);
      }

      for (Particle* o : closeP) {
        if (p != o) {
          p->checkCollision(o);
        }
      }

      closeP.clear();

      /* for (Particle* o : particles)
         {
         if (p != o)
         {
         p->checkCollision(o);
         }
         } */
    } 
    if(frame % 5 == 1 && spawn)
    {
      addParticle(new Particle(400, 400, 2, 0, 10, 5, WHITE));
    }
    frame++;
  }

  for(Particle* p: particles) {
    cam->draw(p);
  }

  DrawFPS(0,0);
  DrawText(TextFormat("Particles: %i", particles.size()), 0, 20, 20, WHITE);
  DrawText(TextFormat("Pause: SPACE"), 0, 40, 20, WHITE);

}

void Looper::addParticle(Particle* p)
{
  particles.push_back(p);
  qt->addParticle(p);
}

